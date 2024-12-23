#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime now = prac::QTime::currentTime();
    ui->lbl_now->setText(now.toString());
    timer_one_sec_.setInterval(1000 - now.msec());
    timer_one_sec_.setSingleShot(true);
    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::on_timer_one_sec_timeout);
    timer_one_sec_.start();

    player_.setAudioOutput(new QAudioOutput(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_one_sec_timeout()
{
    QTime now = prac::QTime::currentTime();

    ui->lbl_now->setText(now.toString());
    timer_one_sec_.start(1000 - now.msec());

    if (!is_alarm_on_ || is_playing_) {
        return;
    }

    prac::QDateTime current_time = prac::QDateTime::currentDateTime();
    int seconds = ((alarm_time_ - current_time).count() + 500) / 1000;

    if (seconds <= 0) {
        player_.play();
        is_playing_ = true;

        ui->lbl_timeout->setText("Пора вставать!");
        return;
    } else {
        QTime time(0, 0, 0);
        time = time.addSecs(seconds);
        ui->lbl_timeout->setText(time.toString("hh:mm:ss"));
    }
}

void MainWindow::on_action_load_file_triggered()
{
    QString file_name = prac::QFileDialog::getOpenFileName(this,
                                                           QString::fromUtf8("Открыть файл"),
                                                           QDir::currentPath(),
                                                           QString::fromUtf8("Музыка (*.wav;*.mp3)"));

    if (!file_name.isEmpty()) {
        QFileInfo file_info(file_name);
        ui->lbl_melody->setText(file_info.fileName());
        player_.setSource(QUrl::fromLocalFile(file_name));
    }
}

void MainWindow::set_alarm_time()
{
    auto now = prac::QDateTime::currentDateTime();

    alarm_time_ = now;
    alarm_time_.setTime(QTime(
        ui->sb_hour->text().toInt(),
        ui->sb_min->text().toInt(),
        ui->sb_sec->text().toInt()
        ));
    if (alarm_time_ < now) {
        alarm_time_ = alarm_time_.addDays(1);
    }
}

void MainWindow::on_pb_start_stop_clicked()
{
    if (player_.source().isEmpty()) {
        return;
    }

    if (is_alarm_on_) {
        timer_one_sec_.stop();
        if (is_playing_) {
            player_.stop();
            is_playing_ = false;
        }
        ui->lbl_timeout->setText("Установите будильник");
        is_alarm_on_ = false;
        ui->pb_start_stop->setText("Старт");
    } else {
        set_alarm_time();
        is_alarm_on_ = true;
        ui->pb_start_stop->setText("Стоп");
    }
}

