#pragma once

#include <QListWidgetItem>
#include <QMainWindow>
#include <QStringListModel>

#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetRandomGen(const std::mt19937& random_gen);
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

    void on_pb_find_clicked();
    void on_pb_min_element_clicked();
    void on_pb_max_element_clicked();
    void on_pb_count_clicked();

    void on_pb_unique_clicked();
    void on_pb_sort_clicked();
    void on_pb_sort_2_clicked();
    void on_pb_reverse_clicked();
    void on_pb_shuffle_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model vector_model_;
    Ui::MainWindow *ui;

    std::mt19937 random_gen_;
};
