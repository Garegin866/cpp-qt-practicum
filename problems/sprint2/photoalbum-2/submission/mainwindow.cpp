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
{
    ui->setupUi(this);
    SetPixmap(":/cats/images/cat1.jpg");
    FitImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FitImage()
{
    Q_ASSERT(!active_pixmap.isNull());

    auto img = ResizeImgToFit(active_pixmap, width(), height());
    ui->lbl_img->setPixmap(img);
    ui->lbl_img->setFixedSize(img.size());
    ui->lbl_img->move((width() - img.width()) / 2, (height() - img.height()) / 2);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}
