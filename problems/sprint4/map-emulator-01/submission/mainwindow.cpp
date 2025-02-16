#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    auto preserve_iter = map_model_.iterator; // Preserve the iterator

    QStringList items;
    for (const auto& [key, value] : map_model_.items) {
        items.append(QString::fromStdString(key) + ": " + QString::fromStdString(value));
    }
    items.append("end");

    ui->list_widget->clear();
    ui->list_widget->addItems(items);

    ui->txt_size->setText(QString::number(map_model_.items.size()));

    map_model_.iterator = preserve_iter; // Restore the iterator

    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    int iterator_offset = std::distance(map_model_.items.begin(), map_model_.iterator);
    ui->list_widget->setCurrentRow(iterator_offset);

    bool is_end = map_model_.iterator == map_model_.items.end();
    ui->btn_inc_iterator->setDisabled(is_end);
    ui->btn_erase->setDisabled(is_end);

    bool is_begin = map_model_.iterator == map_model_.items.begin();
    ui->btn_dec_iterator->setDisabled(is_begin);

}

void MainWindow::on_btn_set_by_key_clicked() {
    QString key = ui->txt_elem_key->text();
    QString value = ui->txt_elem_value->text();

    map_model_.items[key.toStdString()] = value.toStdString();
\
    ApplyModel();
}

void MainWindow::on_btn_erase_clicked() {
    if (map_model_.iterator != map_model_.items.end()) {
        map_model_.iterator = map_model_.items.erase(map_model_.iterator);
        map_model_.iterator = map_model_.items.begin();

        ApplyModel();
    }
}

void MainWindow::on_btn_clear_clicked() {
    map_model_.items.clear();
    map_model_.iterator = map_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_find_clicked() {
    QString key = ui->txt_elem_key->text();
    map_model_.iterator = map_model_.items.find(key.toStdString());
    ApplyIterator();
}

void MainWindow::on_btn_dec_iterator_clicked() {
    if (map_model_.iterator != map_model_.items.begin()) {
        map_model_.iterator = std::prev(map_model_.iterator);
        ApplyIterator();
    }
}

void MainWindow::on_btn_inc_iterator_clicked() {
    if (map_model_.iterator != map_model_.items.end()) {
        map_model_.iterator = std::next(map_model_.iterator);
        ApplyIterator();
    }
}

void MainWindow::on_btn_begin_clicked() {
    map_model_.iterator = map_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_end_clicked() {
    map_model_.iterator = map_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_books_clicked() {
    map_model_.items = authors_and_books;
    map_model_.iterator = map_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_words_clicked() {
    map_model_.items = words;
    map_model_.iterator = map_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_list_widget_currentItemChanged(QListWidgetItem *current,
                                                   QListWidgetItem *previous) {
    if (current) {
        int index = ui->list_widget->row(current);
        map_model_.iterator = std::next(map_model_.items.begin(), index);
        ApplyIterator();
    }
}
