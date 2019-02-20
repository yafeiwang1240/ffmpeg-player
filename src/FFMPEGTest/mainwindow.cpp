#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    av_register_all();

    ui->pushButton->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->pushButton_5->setEnabled(false);

    qDebug() << avcodec_configuration();

    unsigned version = avcodec_version();

    QString ch = QString::number(version, 10);

    ui->horizontalSlider->setMaximum(100);

    qDebug() << "version:" << ch;
}

MainWindow::~MainWindow()
{
    if(m_player){
        m_player->close();
        m_player->deleteLater();
        m_player = NULL;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(false);

    AVFormatContext *pFormatCtx = avformat_alloc_context();

    // 打开文件
    int res = avformat_open_input(&pFormatCtx, "d:/ffmpeg/t1.mp4", NULL, NULL);

    if(res != 0){

        QMessageBox::warning(this, "提示", "打开失败");
        return;
    }

    // 查询流信息
    if(avformat_find_stream_info(pFormatCtx, NULL) < 0){

        QMessageBox::warning(this, "提示", "查询流失败");
        return;

    }

    // 获取总时间
    pFormatCtx->duration;

    // 找到视频流
    AVCodecContext* pCodecCtx;
    int videoStream = -1;

    for(unsigned int i = 0; i < pFormatCtx->nb_streams; i++){

        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){

            videoStream = i;
            break;
        }
    }


    if(videoStream == -1){

        QMessageBox::warning(this, "提示", "没有视频流");
        return;

    }

    // 获取编码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    AVCodec* pCodec;

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    if(pCodec == NULL){
        QMessageBox::warning(this, "提示", "获取编码器失败");
        return;
    }


    // 打开编码器
    if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0){
        QMessageBox::warning(this, "提示", "打开编码器失败");
        return;
    }

    // 分配原始帧
    AVFrame* pFrame = av_frame_alloc();

    if(pFrame == NULL){
        QMessageBox::warning(this, "提示", "分配原始帧失败");
        return;
    }

    // 分配YUV帧
//    AVFrame* pFrameYUV = av_frame_alloc();

//    if(pFrameYUV == NULL){
//        QMessageBox::warning(this, "提示", "分配YUV帧失败");
//        return;
//    }

//    // 根据一帧画面大小分配内存，病填充YUV数据
//    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV440P, pCodecCtx->width, pCodecCtx->height, 1);

//    uint8_t* buffer = (uint8_t*)av_mallocz(numBytes * sizeof(uint8_t));

//    if(buffer == NULL){
//        QMessageBox::warning(this, "提示", "分配内存失败");
//        return;
//    }

//    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

//    // 获取YUV格式转换器上下文
//    SwsContext* img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

//    if(img_convert_ctx){

//        QMessageBox::warning(this, "提示", "获取YUV格式转换器上下文失败");
//        return;
//    }

    // 初始化SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO)){
        QMessageBox::warning(this, "提示", "SDL初始化失败");
        return;
    }


    // 建立窗口
    SDL_Window* gWindow = SDL_CreateWindowFrom((const void*)this->ui->widget->winId());

    if(gWindow == NULL){

        QMessageBox::warning(this, "提示", "建立窗口失败");
        return;
    }

    // 建立渲染器
    SDL_Renderer* sdlRender = SDL_CreateRenderer(gWindow, -1, 0);

    if(sdlRender == NULL){
        QMessageBox::warning(this, "提示", "建立渲染窗口失败");
        return;
    }

    // 建立纹理
    SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRender, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, pCodecCtx->width, pCodecCtx->height);

    if(sdlTexture == NULL){
        QMessageBox::warning(this, "提示", "建立纹理失败");
        return;
    }

    SDL_Rect sdlRect;
    SDL_Rect sdlRectWnd;
    AVPacket packet;
    int frameFinished = 0;

    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = pCodecCtx->width;
    sdlRect.h = pCodecCtx->height;

    sdlRectWnd.x = 0;
    sdlRectWnd.y = 0;
    sdlRectWnd.w = this->ui->widget->width();
    sdlRectWnd.h = this->ui->widget->height();

    // 开始读取
    while(av_read_frame(pFormatCtx, &packet) >= 0){

        // 判断视频流
        if(packet.stream_index == videoStream){

            // 获取解码后的帧
            if(avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet) < 0){

                qDebug() << "解码失败";
            }

            // 帧已完整
            if(frameFinished){
                //sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);

                //SDL_UpdateYUVTexture(sdlTexture, &sdlRect, pFrameYUV->data[0], pFrameYUV->linesize[0], pFrameYUV->data[1], pFrameYUV->linesize[1], pFrameYUV->data[2], pFrameYUV->linesize[2]);

                SDL_UpdateYUVTexture(sdlTexture, &sdlRect, pFrame->data[0], pFrame->linesize[0], pFrame->data[1], pFrame->linesize[1], pFrame->data[2], pFrame->linesize[2]);

                SDL_RenderClear(sdlRender);
                SDL_RenderCopy(sdlRender, sdlTexture, NULL, &sdlRectWnd);
                SDL_RenderPresent(sdlRender);

                // 获取当前流
                AVStream* stream = pFormatCtx->streams[packet.stream_index];

                // 获取当前时钟

                double x1 = pFrame->pts;
                double x2 = av_q2d(stream->time_base);
                int sec = pFrame->pts * av_q2d(stream->time_base);


                SDL_Delay(40); // 延时

                qApp->processEvents();
            }
        }

        // 释放包
        av_free_packet(&packet);
    }


    // 播放结束，回收资源
    //sws_freeContext(img_convert_ctx);
    SDL_Quit();
    //av_free(buffer);
    av_free(pFrame);
    //av_free(pFrameYUV);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

}

void MainWindow::on_pushButton_2_clicked()
{

    // 多次播放报错有问题，不报错，但不显示图像，还未解决
    if(m_player){
        m_player->close();
        m_player->deleteLater();
        m_player = NULL;
    }

    long long sec  = 0;
    m_player = new H265ViedoPlayer();
    m_player->init("d:/ffmpeg/t1.mp4", this->ui->widget, &sec);
    totalSec = sec;
    connect(m_player, SIGNAL(currentTimes(long long)), this, SLOT(on_currentTimes(long long)));
    m_player->start();

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    bool change = false;

    int value = ui->horizontalSlider->value();
    double pos = 1.0 * value / 100;

    if(!m_player->getStop()){
        change = true;
        m_player->setStop(true);
    }
    m_player->seek(pos < 0.9 ? pos + 0.1 : 0.99);
    m_player->setStop(false);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(m_player->getStop()){
        m_player->setStop(false);
    }else{
        m_player->setStop(true);
    }
}

void MainWindow::on_currentTimes(long long pos){
    int position = 100* (double)pos/((double)totalSec/AV_TIME_BASE);
    ui->horizontalSlider->setSliderPosition(position);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    double pos = 1.0 * value / 100;

    bool change = false;

    if(!m_player->getStop()){
        change = true;
        m_player->setStop(true);
    }
    m_player->seek(pos);
    m_player->setStop(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    bool change = false;

    int value = ui->horizontalSlider->value();
    double pos = 1.0 * value / 100;

    if(!m_player->getStop()){
        change = true;
        m_player->setStop(true);
    }
    m_player->seek(pos > 0.1 ? pos - 0.1 : 0.0);
    m_player->setStop(false);
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    m_player->setStop(true);
}

void MainWindow::on_pushButton_5_pressed()
{
    m_player->setStop(true);
}

void MainWindow::on_pushButton_3_pressed()
{
    m_player->setStop(true);
}
