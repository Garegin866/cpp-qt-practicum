#include "mainwindow.h"
#include "algo.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , random_gen_(std::random_device()()){
    ui->setupUi(this);

    ui->lbl_count->setText("0");

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetRandomGen(const std::mt19937 &random_gen) {
    random_gen_ = random_gen;
}

void MainWindow::ApplyModel() {
    auto preserve_iter = deque_model_.iterator; // Preserve the iterator

    QStringList items;
    for (size_t i = 0; i < deque_model_.items.size(); ++i) {
        items.append(QString::number(i) + ": " + QString::fromStdString(deque_model_.items[i]));
    }
    items.append("end");

    ui->list_widget->clear();
    ui->list_widget->addItems(items);

    ui->txt_size->setText(QString::number(deque_model_.items.size()));
    ui->btn_pop_back->setDisabled(deque_model_.items.empty());
    ui->btn_pop_front->setDisabled(deque_model_.items.empty());

    deque_model_.iterator = preserve_iter; // Restore the iterator

    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    int iterator_offset = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    ui->list_widget->setCurrentRow(iterator_offset);

    bool is_end = deque_model_.iterator == deque_model_.items.end();
    ui->btn_edit->setDisabled(is_end);
    ui->btn_erase->setDisabled(is_end);
    ui->btn_inc_iterator->setDisabled(is_end);

    bool is_begin = deque_model_.iterator == deque_model_.items.begin();
    ui->btn_dec_iterator->setDisabled(is_begin);

    ui->txt_elem_content->setText(is_end ? "" : QString::fromStdString(*deque_model_.iterator));
}

void MainWindow::on_btn_pop_back_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_back();
        deque_model_.iterator = deque_model_.items.begin();

        ApplyModel();
    }
}

void MainWindow::on_btn_push_back_clicked() {
    QString new_item = ui->txt_elem_content->text();
    deque_model_.items.push_back(new_item.toStdString());
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();

    ApplyIterator();
}

void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_erase_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();

        ApplyModel();
    }
}

void MainWindow::on_btn_insert_clicked() {
    QString new_item = ui->txt_elem_content->text();
    deque_model_.items.insert(deque_model_.iterator, new_item.toStdString());
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_inc_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        ++deque_model_.iterator;

        ApplyIterator();
    }
}

void MainWindow::on_btn_dec_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.begin()) {
        --deque_model_.iterator;

        ApplyIterator();
    }
}

void MainWindow::on_btn_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();

    ApplyIterator();
}

void MainWindow::on_btn_edit_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        QString new_item = ui->txt_elem_content->text();
        *deque_model_.iterator = new_item.toStdString();

        ApplyModel();
    }
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow >= 0 && currentRow <= deque_model_.items.size()) {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;

        ApplyIterator();
    }
}

void MainWindow::on_btn_resize_clicked() {
    int new_size = ui->txt_size->text().toInt();
    deque_model_.items.resize(new_size);

    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_find_clicked() {
    auto search_item = ui->txt_elem_content->text().toStdString();
    auto found = std::find(deque_model_.items.begin(), deque_model_.items.end(), search_item);

    deque_model_.iterator = found;
    ApplyIterator();
}

void MainWindow::on_btn_min_element_clicked() {
    auto min_element = std::min_element(deque_model_.items.begin(), deque_model_.items.end());

    deque_model_.iterator = min_element;
    ApplyIterator();
}

void MainWindow::on_btn_max_element_clicked() {
    auto max_element = std::max_element(deque_model_.items.begin(), deque_model_.items.end());

    deque_model_.iterator = max_element;
    ApplyIterator();
}

void MainWindow::on_btn_count_clicked() {
    auto count_text = ui->le_count->text();
    int count = 0;
    if (!count_text.isEmpty()) {
        count = std::count(deque_model_.items.begin(), deque_model_.items.end(), count_text.toStdString());
    }

    ui->lbl_count->setText(QString::number(count));
}

void MainWindow::on_btn_unique_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto new_end = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(new_end, deque_model_.items.end());

        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_btn_sort_clicked() {
    deque_model_.items = MergeSort(deque_model_.items, std::less<std::string>());
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_sort_2_clicked() {
    deque_model_.items = MergeSort(deque_model_.items, [](const std::string& lhs, const std::string& rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](char a, char b) {
            return std::tolower(a) < std::tolower(b);
        });
    });
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_reverse_clicked() {
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}

void MainWindow::on_btn_shuffle_clicked() {
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    ApplyModel();
}

void MainWindow::on_btn_pop_front_clicked() {
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_push_front_clicked() {
    QString new_item = ui->txt_elem_content->text();
    deque_model_.items.push_front(new_item.toStdString());
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_tea_clicked() {
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_cakes_clicked() {
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_btn_lower_bound_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto lower_bound = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        deque_model_.iterator = lower_bound;

        ApplyIterator();
    }
}

void MainWindow::on_btn_upper_bound_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto upper_bound = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        deque_model_.iterator = upper_bound;

        ApplyIterator();
    }
}
