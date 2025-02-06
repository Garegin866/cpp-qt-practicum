#pragma once

#include "calculator.h"
#include "enums.h"
#include "ui_mainwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

inline const QString kMemoryText = "M";
inline const QString kDot = ".";

namespace styles {
inline const QString kError = "color: red;";
inline const QString kDefault = "";
}

inline const QHash<ControllerType, QString> kControllerTypeToString = {
    {ControllerType::DOUBLE, "double"},
    {ControllerType::FLOAT, "float"},
    {ControllerType::UINT8_T, "uint8_t"},
    {ControllerType::INT, "int"},
    {ControllerType::INT64_T, "int64_t"},
    {ControllerType::SIZE_T, "size_t"},
    {ControllerType::RATIONAL, "Rational"}
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() {};

    void SetInputText(const std::string &text);
    void SetErrorText(const std::string &text);
    void SetFormulaText(const std::string &text);
    void SetMemText(const std::string &text);
    void SetExtraKey(const std::optional<std::string> &key);

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:
    void on_btn_add_clicked();
    void on_btn_div_clicked();
    void on_btn_mul_clicked();
    void on_btn_sub_clicked();
    void on_btn_pow_clicked();
    void on_btn_res_clicked();

    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();

    void on_btn_ms_clicked();
    void on_btn_mr_clicked();
    void on_btn_mc_clicked();

    void on_btn_c_clicked();
    void on_btn_plus_minus_clicked();
    void on_btn_del_clicked();
    void on_tb_extra_clicked();

    void on_cmb_controller_currentIndexChanged(int index);

private:
    Ui::MainWindow* ui;

    std::function<void(int key)> digit_key_cb_;
    std::function<void(Operation key)> operation_key_cb_;
    std::function<void(ControlKey key)> control_key_cb_;
    std::function<void(ControllerType controller)> controller_cb_;
};

inline void MainWindow::SetInputText(const std::string &text) {
    ui->l_result->setStyleSheet(styles::kDefault);
    ui->l_result->setText(QString::fromStdString(text));
}

inline void MainWindow::SetErrorText(const std::string &text) {
    ui->l_result->setStyleSheet(styles::kError);
    ui->l_result->setText(QString::fromStdString(text));
}

inline void MainWindow::SetFormulaText(const std::string &text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

inline void MainWindow::SetMemText(const std::string &text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

inline void MainWindow::SetExtraKey(const std::optional<std::string> &key) {
    if (key.has_value()) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}

inline void MainWindow::SetDigitKeyCallback(std::function<void (int)> cb) {
    digit_key_cb_ = cb;
}

inline void MainWindow::SetProcessOperationKeyCallback(std::function<void (Operation)> cb) {
    operation_key_cb_ = cb;
}

inline void MainWindow::SetProcessControlKeyCallback(std::function<void (ControlKey)> cb) {
    control_key_cb_ = cb;
}

inline void MainWindow::SetControllerCallback(std::function<void (ControllerType)> cb) {
    controller_cb_ = cb;
}

inline void MainWindow::on_btn_add_clicked() {
    if (operation_key_cb_) {
        operation_key_cb_(Operation::ADDITION);
    }
}

inline void MainWindow::on_btn_div_clicked() {
    if (operation_key_cb_) {
        operation_key_cb_(Operation::DIVISION);
    }
}

inline void MainWindow::on_btn_mul_clicked() {
    if (operation_key_cb_) {
        operation_key_cb_(Operation::MULTIPLICATION);
    }
}

inline void MainWindow::on_btn_sub_clicked() {
    if (operation_key_cb_) {
        operation_key_cb_(Operation::SUBTRACTION);
    }
}

inline void MainWindow::on_btn_pow_clicked() {
    if (operation_key_cb_) {
        operation_key_cb_(Operation::POWER);
    }
}

inline void MainWindow::on_btn_res_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::EQUALS);
    }
}

inline void MainWindow::on_btn_0_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(0);
    }
}

inline void MainWindow::on_btn_1_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(1);
    }
}

inline void MainWindow::on_btn_2_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(2);
    }
}

inline void MainWindow::on_btn_3_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(3);
    }
}

inline void MainWindow::on_btn_4_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(4);
    }
}

inline void MainWindow::on_btn_5_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(5);
    }
}

inline void MainWindow::on_btn_6_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(6);
    }
}

inline void MainWindow::on_btn_7_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(7);
    }
}

inline void MainWindow::on_btn_8_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(8);
    }
}

inline void MainWindow::on_btn_9_clicked() {
    if (digit_key_cb_) {
        digit_key_cb_(9);
    }
}

inline void MainWindow::on_btn_ms_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::MEM_SAVE);
    }
}

inline void MainWindow::on_btn_mr_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::MEM_LOAD);
    }
}

inline void MainWindow::on_btn_mc_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::MEM_CLEAR);
    }
}

inline void MainWindow::on_btn_c_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::CLEAR);
    }
}

inline void MainWindow::on_btn_plus_minus_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::PLUS_MINUS);
    }
}

inline void MainWindow::on_btn_del_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::BACKSPACE);
    }
}

inline void MainWindow::on_tb_extra_clicked() {
    if (control_key_cb_) {
        control_key_cb_(ControlKey::EXTRA_KEY);
    }
}
