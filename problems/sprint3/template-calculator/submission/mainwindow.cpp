#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->cmb_controller->addItems(kControllerTypeToString.values());
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index) {
    Q_UNUSED(index);

    if (!controller_cb_) {
        return;
    }

    QString text = ui->cmb_controller->currentText();
    switch (kControllerTypeToString.key(text)) {
    case ControllerType::DOUBLE:
        controller_cb_(ControllerType::DOUBLE);
        break;
    case ControllerType::FLOAT:
        controller_cb_(ControllerType::FLOAT);
        break;
    case ControllerType::UINT8_T:
        controller_cb_(ControllerType::UINT8_T);
        break;
    case ControllerType::INT:
        controller_cb_(ControllerType::INT);
        break;
    case ControllerType::INT64_T:
        controller_cb_(ControllerType::INT64_T);
        break;
    case ControllerType::SIZE_T:
        controller_cb_(ControllerType::SIZE_T);
        break;
    case ControllerType::RATIONAL:
        controller_cb_(ControllerType::RATIONAL);
        break;
    }
}
