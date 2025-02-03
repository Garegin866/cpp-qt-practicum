#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_add_clicked()
{
    ProcessOperation(Operation::ADDITION);
}

void MainWindow::on_btn_sub_clicked()
{
    ProcessOperation(Operation::SUBTRACTION);
}

void MainWindow::on_btn_div_clicked()
{
    ProcessOperation(Operation::DIVISION);
}

void MainWindow::on_btn_mul_clicked()
{
    ProcessOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_pow_clicked()
{
    ProcessOperation(Operation::POWER);
}

void MainWindow::on_btn_res_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    ui->l_formula->setText(QString::number(calculator_.GetNumber())
                           + " " + GetOperationSymbol(current_operation_) + " "
                           + QString::number(active_number_)
                           + " =");
    Calculate();
    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_ = "";
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::on_btn_0_clicked()
{
    ProcessNumber(0);
}

void MainWindow::on_btn_1_clicked()
{
    ProcessNumber(1);
}

void MainWindow::on_btn_2_clicked()
{
    ProcessNumber(2);
}

void MainWindow::on_btn_3_clicked()
{
    ProcessNumber(3);
}

void MainWindow::on_btn_4_clicked()
{
    ProcessNumber(4);
}

void MainWindow::on_btn_5_clicked()
{
    ProcessNumber(5);
}

void MainWindow::on_btn_6_clicked()
{
    ProcessNumber(6);
}

void MainWindow::on_btn_7_clicked()
{
    ProcessNumber(7);
}

void MainWindow::on_btn_8_clicked()
{
    ProcessNumber(8);
}

void MainWindow::on_btn_9_clicked()
{
    ProcessNumber(9);
}

void MainWindow::on_btn_ms_clicked()
{
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui->l_memory->setText(kMemoryText);
}

void MainWindow::on_btn_mr_clicked()
{
    if (memory_saved_) {
        input_number_ = "";
        active_number_ = memory_cell_;
        ui->l_result->setText(QString::number(memory_cell_));
    }
}

void MainWindow::on_btn_mc_clicked()
{
    memory_cell_ = 0;
    memory_saved_ = false;
    ui->l_memory->setText("");
}

void MainWindow::on_btn_c_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    calculator_.Set(0);
    input_number_ = "";
    active_number_ = 0;
    ui->l_result->setText("0");
    ui->l_formula->setText("");
}

void MainWindow::on_btn_plus_minus_clicked()
{
    if (input_number_.isEmpty() && current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    active_number_ *= -1;
    input_number_ = QString::number(active_number_);
    ui->l_result->setText(input_number_);
}

void MainWindow::on_btn_del_clicked()
{
    if (!input_number_.isEmpty())  {
        input_number_ = input_number_.left(input_number_.length() - 1);
        active_number_ = input_number_.toDouble();
        ui->l_result->setText(input_number_);
    }
}

void MainWindow::on_btn_dot_clicked()
{
    if (input_number_.isEmpty()) {
        if (current_operation_ != Operation::NO_OPERATION) {
            return;
        }
        input_number_ = "0";
        ui->l_result->setText(input_number_);
        ui->l_formula->setText("");
    }

    if (!input_number_.contains(kDot)) {
        input_number_ += kDot;
        ui->l_result->setText(input_number_);
    }
}

void MainWindow::ProcessNumber(Number n) {
    if (current_operation_ == Operation::NO_OPERATION) {
        ui->l_formula->setText("");
    }

    input_number_ += QString::number(n);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::Calculate() {
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    default:
        calculator_.Set(active_number_);
        break;
    }
}

void MainWindow::ProcessOperation(Operation operation) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = operation;
    ui->l_formula->setText(QString::number(active_number_) + " " + GetOperationSymbol(operation) + " ");
    input_number_ = "";
}

QString MainWindow::GetOperationSymbol(Operation operation) {
    switch (operation) {
    case Operation::ADDITION:
        return "+";
    case Operation::SUBTRACTION:
        return "−";
    case Operation::MULTIPLICATION:
        return "×";
    case Operation::DIVISION:
        return "÷";
    case Operation::POWER:
        return "^";
    default:
        return "";
    }
}

