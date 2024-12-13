#include "mainwindow.h"
#include "ui_mainwindow.h"

// Функция подгоняет изображение под нужный размер окна.
QPixmap ResizeImgToFit(const QPixmap &src, int window_width, int window_height) {
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) / window_width;
    double h_ratio = double(img_h) / window_height;

    if ( w_ratio < h_ratio ) {
        return src.scaledToWidth(window_width);
    } else {
        return src.scaledToHeight(window_height);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cur_file_index_(0) {

    ui->setupUi(this);

    SetFolder(":/cats/images/");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::FitImage() {
    Q_ASSERT(!active_pixmap.isNull());

    auto img = ResizeImgToFit(active_pixmap, width(), height());
    lbl_new_.setPixmap(img);
    lbl_new_.setFixedSize(img.size());
    lbl_new_.move((width() - img.width()) / 2,
                  (height() - img.height()) / 2);
}

void MainWindow::resizeEvent(QResizeEvent*) {
    FitImage();
}

void MainWindow::on_btn_left_clicked() {
    cur_file_index_--;
    SetPixmap(GetCurrentFile());
}


void MainWindow::on_btn_right_clicked() {
    cur_file_index_++;
    SetPixmap(GetCurrentFile());
}

QString MainWindow::GetCurrentFile() {
    QDir dir(current_folder_);
    QStringList list_files = dir.entryList();
    int total = int(list_files.size());

    int file_index = std::min(cur_file_index_, total - 1);
    file_index = std::max(0, file_index);
    return dir.filePath(list_files[file_index]);
}

void MainWindow::SetFolder(const QString &d) {
    cur_file_index_ = 0;
    current_folder_ = d;
    SetPixmap(GetCurrentFile());
}

void MainWindow::UpdateEnabled() {
    int max_images = QDir(current_folder_).entryList().size();

    QDir dir(current_folder_);
    QStringList list_files = dir.entryList();
    ui->btn_left->setEnabled(cur_file_index_ > 0);
    ui->btn_right->setEnabled(cur_file_index_ < max_images - 1);
}

void MainWindow::SetPixmap(const QString path) {
    active_pixmap = QPixmap(path);
    lbl_new_.setPixmap(active_pixmap);
    FitImage();
    UpdateEnabled();
}
