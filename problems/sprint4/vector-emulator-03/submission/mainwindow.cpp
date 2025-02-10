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
    auto preserve_iter = vector_model_.iterator; // Preserve the iterator

    QStringList items;
    for (size_t i = 0; i < vector_model_.items.size(); ++i) {
        items.append(QString::number(i) + ": " + QString::fromStdString(vector_model_.items[i]));
    }
    items.append("end");

    ui->list_widget->clear();
    ui->list_widget->addItems(items);

    ui->txt_size->setText(QString::number(vector_model_.items.size()));
    ui->txt_capacity->setText(QString::number(vector_model_.items.capacity()));
    ui->pb_pop_back->setDisabled(vector_model_.items.empty());

    vector_model_.iterator = preserve_iter; // Restore the iterator

    ApplyIterator();
}
\
void MainWindow::ApplyIterator() {
    int iterator_offset = std::distance(vector_model_.items.begin(), vector_model_.iterator);
    ui->list_widget->setCurrentRow(iterator_offset);

    bool is_end = vector_model_.iterator == vector_model_.items.end();
    ui->pb_edit->setDisabled(is_end);
    ui->pb_erase->setDisabled(is_end);
    ui->pb_increment->setDisabled(is_end);

    bool is_begin = vector_model_.iterator == vector_model_.items.begin();
    ui->pb_decrement->setDisabled(is_begin);

    ui->txt_elem_content->setText(is_end ? "" : QString::fromStdString(*vector_model_.iterator));
}

void MainWindow::on_pb_pop_back_clicked() {
    if (!vector_model_.items.empty()) {
        vector_model_.items.pop_back();
        vector_model_.iterator = vector_model_.items.begin();

        ApplyModel();
    }
}

void MainWindow::on_pb_push_back_clicked() {
    QString new_item = ui->txt_elem_content->text();
    vector_model_.items.push_back(new_item.toStdString());
    vector_model_.iterator = vector_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_clear_clicked() {
    vector_model_.items.clear();
    vector_model_.iterator = vector_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_weekdays_clicked() {
    vector_model_.items = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
    vector_model_.iterator = vector_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_months_clicked() {
    vector_model_.items = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
    vector_model_.iterator = vector_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_erase_clicked() {
    if (vector_model_.iterator != vector_model_.items.end()) {
        vector_model_.items.erase(vector_model_.iterator);
        vector_model_.iterator = vector_model_.items.begin();

        ApplyModel();
    }
}

void MainWindow::on_pb_insert_clicked() {
    QString new_item = ui->txt_elem_content->text();
    vector_model_.items.insert(vector_model_.iterator, new_item.toStdString());
    vector_model_.iterator = vector_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_increment_clicked() {
    if (vector_model_.iterator != vector_model_.items.end()) {
        ++vector_model_.iterator;

        ApplyIterator();
    }
}

void MainWindow::on_pb_decrement_clicked() {
    if (vector_model_.iterator != vector_model_.items.begin()) {
        --vector_model_.iterator;

        ApplyIterator();
    }
}

void MainWindow::on_pb_begin_clicked() {
    vector_model_.iterator = vector_model_.items.begin();

    ApplyIterator();
}

void MainWindow::on_pb_end_clicked() {
    vector_model_.iterator = vector_model_.items.end();

    ApplyIterator();
}

void MainWindow::on_pb_edit_clicked() {
    if (vector_model_.iterator != vector_model_.items.end()) {
        QString new_item = ui->txt_elem_content->text();
        *vector_model_.iterator = new_item.toStdString();

        ApplyModel();
    }
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow >= 0 && currentRow <= vector_model_.items.size()) {
        vector_model_.iterator = vector_model_.items.begin() + currentRow;

        ApplyIterator();
    }
}

void MainWindow::on_btn_resize_clicked() {
    int new_size = ui->txt_size->text().toInt();
    vector_model_.items.resize(new_size);

    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_reserve_clicked() {
    int new_capacity = ui->txt_capacity->text().toInt();
    vector_model_.items.reserve(new_capacity);

    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}
