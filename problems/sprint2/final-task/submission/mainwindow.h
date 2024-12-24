#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

inline const QString kMemoryText = "M";
inline const QString kDot = ".";

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

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
    void on_btn_dot_clicked();

private:
    void Calculate();
    void ProcessNumber(Number n);
    void ProcessOperation(Operation operation);

    static QString GetOperationSymbol(Operation operation);

private:
    Ui::MainWindow* ui;
    Operation current_operation_ = Operation::NO_OPERATION;
    Calculator calculator_;
    QString input_number_;
    Number active_number_{0.0};
    Number memory_cell_{0.0};
    bool memory_saved_{false};
};
