#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Reset();
    ShowQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Reset() {
    a_ = 1;
    b_ = 101;
}

void MainWindow::ShowQuestion() {
    if (b_ - a_ <= 1) {
        ui->lbl_question->setText(QString("Ваше число %1!").arg(a_));
    } else {
        m_ = (a_ + b_) / 2;
        ui->lbl_question->setText(QString("Ваше число меньше %1?").arg(m_));
    }
}

void MainWindow::on_btn_yes_clicked()
{
    if (b_ - a_ <= 1) {
        QMessageBox::information(this, "Число угадано", "Прекрасно! Давайте ещё раз.");
        Reset();
    } else {
        b_ = m_;
    }
    ShowQuestion();
}

void MainWindow::on_btn_no_clicked()
{
    if (b_ - a_ <= 1) {
        QMessageBox::information(this, "Число не угадано", "В следующий раз повезёт больше.");
        Reset();
    } else {
        a_ = m_;
    }
    ShowQuestion();
}
