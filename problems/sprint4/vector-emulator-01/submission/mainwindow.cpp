#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    QStringList items;
    for (size_t i = 0; i < vector_model_.items.size(); ++i) {
        items.append(QString::number(i) + ": " + QString::fromStdString(vector_model_.items[i]));
    }

    ui->list_widget->clear();
    ui->list_widget->addItems(items);

    ui->txt_size->setText(QString::number(vector_model_.items.size()));

    ui->pb_pop_back->setDisabled(vector_model_.items.empty());
}

void MainWindow::on_pb_pop_back_clicked() {
    vector_model_.items.pop_back();
    ApplyModel();
}

void MainWindow::on_pb_push_back_clicked() {
    QString new_item = ui->txt_elem_content->text();
    vector_model_.items.push_back(new_item.toStdString());
    ApplyModel();
}

void MainWindow::on_pb_clear_clicked() {
    vector_model_.items.clear();
    ApplyModel();
}

void MainWindow::on_pb_weekdays_clicked() {
    vector_model_.items = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
    ApplyModel();
}

void MainWindow::on_pb_months_clicked() {
    vector_model_.items = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
    ApplyModel();
}
