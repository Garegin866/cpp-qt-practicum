#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_submit_clicked() {
    auto text = ui->le_text->text();
    QString reversedText;
    for (int i = text.size() - 1; i >= 0; --i) {
        reversedText += text[i];
    }
    ui->le_text->setText(reversedText);
}

