#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "h265viedoplayer.h"
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_currentTimes(long long pos);

    void on_horizontalSlider_sliderReleased();

    void on_pushButton_5_clicked();

    void on_horizontalSlider_sliderPressed();

    void on_pushButton_5_pressed();

    void on_pushButton_3_pressed();

private:
    Ui::MainWindow *ui;

    H265ViedoPlayer* m_player = NULL;

    long long totalSec;
};

#endif // MAINWINDOW_H
