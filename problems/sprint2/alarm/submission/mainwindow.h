#pragma once

#include <QMainWindow>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <prac/QDateTime>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_timer_one_sec_timeout();
    void on_action_load_file_triggered();
    void on_pb_start_stop_clicked();

private:
    void set_alarm_time();

private:
    Ui::MainWindow *ui;
    prac::QTimer timer_one_sec_{this};
    prac::QMediaPlayer player_;
    prac::QDateTime alarm_time_;
    bool is_alarm_on_{false};
    bool is_playing_{false};
};
