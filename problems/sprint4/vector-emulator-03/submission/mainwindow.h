#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_pop_back_clicked();
    void on_pb_push_back_clicked();
    void on_pb_clear_clicked();
    void on_pb_weekdays_clicked();
    void on_pb_months_clicked();
    void on_pb_erase_clicked();
    void on_pb_insert_clicked();
    void on_pb_increment_clicked();
    void on_pb_decrement_clicked();
    void on_pb_begin_clicked();
    void on_pb_end_clicked();
    void on_pb_edit_clicked();

    void on_list_widget_currentRowChanged(int currentRow);
    void on_btn_resize_clicked();
    void on_btn_reserve_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model vector_model_;
    Ui::MainWindow *ui;
};
