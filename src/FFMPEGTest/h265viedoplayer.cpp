#include "h265viedoplayer.h"

#include <QDebug>


H265ViedoPlayer::H265ViedoPlayer(QObject *parent) : QThread(parent)
{

}

H265ViedoPlayer::~H265ViedoPlayer()
{
}


void H265ViedoPlayer::run()
{

    if(!m_inited){

        qDebug() << "未初始化";
        return;
    }

    m_playing = true;

    SDL_Rect sdlRect;
    SDL_Rect sdlRectWnd;
    AVPacket packet;
    int frameFinished = 0;

    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = m_pCodecCtx->width;
    sdlRect.h = m_pCodecCtx->height;

    sdlRectWnd.x = 0;
    sdlRectWnd.y = 0;
    sdlRectWnd.w = this->m_pWnd->width();
    sdlRectWnd.h = this->m_pWnd->height();

    while(true){

        if(stop){
            continue;
        }
        // 开始读取
        if(av_read_frame(m_pFormatCtx, &packet) >= 0 && m_playing){

            // 判断视频流
            if(packet.stream_index == m_videoStream){


                // 获取解码后的帧
                if(avcodec_decode_video2(m_pCodecCtx, m_pFrame, &frameFinished, &packet) < 0){

                    qDebug() << "解码失败";
                }

                // 帧已完整
                if(frameFinished){
                    //sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);

                    //SDL_UpdateYUVTexture(sdlTexture, &sdlRect, pFrameYUV->data[0], pFrameYUV->linesize[0], pFrameYUV->data[1], pFrameYUV->linesize[1], pFrameYUV->data[2], pFrameYUV->linesize[2]);

                    SDL_UpdateYUVTexture(m_sdlTexture, &sdlRect, m_pFrame->data[0], m_pFrame->linesize[0], m_pFrame->data[1], m_pFrame->linesize[1], m_pFrame->data[2], m_pFrame->linesize[2]);

                    SDL_RenderClear(m_sdlRender);
                    SDL_RenderCopy(m_sdlRender, m_sdlTexture, NULL, &sdlRectWnd);
                    SDL_RenderPresent(m_sdlRender);

                    // 获取当前流
                    AVStream* stream = m_pFormatCtx->streams[packet.stream_index];


                    // 获取当前时钟
                    double test1 = av_q2d(stream->time_base);
                    int sd = m_pFrame->pts;
                    int sec = m_pFrame->pts * av_q2d(stream->time_base);


                    emit currentTimes(sec);

                    SDL_Delay(40); // 延时

                }
            }

            // 释放包
            av_free_packet(&packet);
        }else {
            break;
        }
    }
}

bool H265ViedoPlayer::init(QString filename, QWidget *pWnd, long long* pTotalTime)
{

    static int reg = 0;

    if(reg == 0){
        av_register_all();
        reg = 1;
    }


    this->m_filename = filename;
    this->m_pWnd = pWnd;

    m_pFormatCtx = avformat_alloc_context();

    // 打开文件
    int res = avformat_open_input(&m_pFormatCtx, m_filename.toStdString().c_str(), NULL, NULL);

    if(res != 0){

        qDebug() << "打开失败";
        return false;
    }

    // 查询流信息
    if(avformat_find_stream_info(m_pFormatCtx, NULL) < 0){

        //QMessageBox::warning(NULL, "提示", "查询流失败");
        qDebug() << "查询流失败";
        return false;

    }


    // 获取总时间
    *pTotalTime = m_pFormatCtx->duration;

    // 找到视频流
    for(unsigned int i = 0; i < m_pFormatCtx->nb_streams; i++){

        if(m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){

            m_videoStream = i;
            break;
        }
    }


    if(m_videoStream == -1){

        //QMessageBox::warning(NULL, "提示", "没有视频流");
        qDebug() << "没有视频流";
        return false;

    }

    // 获取编码器
    m_pCodecCtx = m_pFormatCtx->streams[m_videoStream]->codec;

    AVCodec* pCodec;

    pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);

    if(pCodec == NULL){
        //QMessageBox::warning(NULL, "提示", "获取编码器失败");
        qDebug() << "获取编码器失败";
        return false;
    }


    // 打开编码器
    if(avcodec_open2(m_pCodecCtx, pCodec, NULL) < 0){
        //QMessageBox::warning(NULL, "提示", "打开编码器失败");
        qDebug() << "打开编码器失败";
        return false;
    }

    // 分配原始帧
    m_pFrame = av_frame_alloc();

    if(m_pFrame == NULL){
        //QMessageBox::warning(NULL, "提示", "分配原始帧失败");
        qDebug() << "分配原始帧失败";
        return false;
    }

    // 初始化SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO)){
        //QMessageBox::warning(NULL, "提示", "SDL初始化失败");
        qDebug() << "SDL初始化失败";
        return false;
    }


    // 建立窗口
    m_gWindow = SDL_CreateWindowFrom((const void*)this->m_pWnd->winId());

    if(m_gWindow == NULL){

        //QMessageBox::warning(NULL, "提示", "建立窗口失败");
        qDebug() << "建立窗口失败: " + QString(SDL_GetError());
        return false;
    }

    // 建立渲染器
    m_sdlRender = SDL_CreateRenderer(m_gWindow, -1, 0);

    if(m_sdlRender == NULL){
        //QMessageBox::warning(NULL, "提示", "建立渲染窗口失败");
        qDebug() << "建立渲染窗口失败: " + QString(SDL_GetError());
        return false;
    }

    // 建立纹理
    m_sdlTexture = SDL_CreateTexture(m_sdlRender, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_pCodecCtx->width, m_pCodecCtx->height);

    if(m_sdlTexture == NULL){
        //QMessageBox::warning(NULL, "提示", "建立纹理失败");
        qDebug() << "建立纹理失败: " + QString(SDL_GetError());
        return false;
    }

    m_inited = true;

    return true;
}

bool H265ViedoPlayer::seek(double pos)
{
    double q2d = av_q2d(m_pFormatCtx->streams[this->m_videoStream]->time_base);
    double sec = this->m_pFormatCtx->duration * pos / AV_TIME_BASE;
    int64_t xx = (int64_t)sec / q2d;
    int x = av_seek_frame(this->m_pFormatCtx, m_videoStream, xx, AVSEEK_FLAG_BACKWARD);

    return true;
}

bool H265ViedoPlayer::getStop(){
    return this->stop;
}

void H265ViedoPlayer::setStop(bool s){
    this->stop = s;
}

bool H265ViedoPlayer::close()
{
    m_playing = false;

    while(this->isRunning()){

        this->msleep(1000);
    }

    // 播放结束，回收资源
    SDL_Quit();
    av_free(m_pFrame);
    avcodec_close(m_pCodecCtx);
    avformat_close_input(&m_pFormatCtx);

    return true;
}

