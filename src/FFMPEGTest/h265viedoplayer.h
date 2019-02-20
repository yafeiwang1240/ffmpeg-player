#ifndef H265VIEDOPLAYER_H
#define H265VIEDOPLAYER_H

#include <QThread>
#include <QSlider>
#include <qlabel.h>

using namespace std;

#define SDL_MAIN_HANDLED

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/version.h>
    #include <libavutil/time.h>
    #include <libavutil/mathematics.h>
    #include <libavutil/imgutils.h>

    #include <SDL.h>
}

class H265ViedoPlayer : public QThread
{
    Q_OBJECT
public:
    explicit H265ViedoPlayer(QObject *parent = nullptr);

    void run();

    bool init(QString filename, QWidget* pWnd, long long *pTotalTime);

    bool seek(double pos);

    bool getStop();

    void setStop(bool s);

    bool close();
    ~H265ViedoPlayer();

signals:

    void currentTimes(long long sec);
public slots:

private:
    bool m_inited = false;

    bool m_playing = false;

    bool stop = false;

    QString m_filename;
    QWidget* m_pWnd;
    QSlider* m_pSlider;
    QLabel* m_pCurrentLable;
    QLabel* m_pTotalLable;
    SDL_Window* m_gWindow = NULL;
    SDL_Renderer* m_sdlRender = NULL;
    SDL_Texture* m_sdlTexture = NULL;
    AVCodecContext* m_pCodecCtx = NULL;
    AVFormatContext* m_pFormatCtx = NULL;
    AVFrame* m_pFrame = NULL;

    int m_videoStream = -1;
};

#endif // H265VIEDOPLAYER_H
