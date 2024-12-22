#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QResizeEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QActionGroup>

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

    InitContextMenu();
    SetFolder(kDefaultFolder);

    timer_ = new prac::QTimer(this);
    timer_->setSingleShot(false);
    connect(timer_, &prac::QTimer::timeout, [this] {
        NextImage();
    });
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (context_menu_->isVisible()) {
            context_menu_->hide();
        } else {
            context_menu_->exec(event->globalPosition().toPoint());
        }
    }
}

void MainWindow::on_btn_left_clicked() {
    Q_ASSERT(!action_group_->actions().isEmpty());
    action_group_->actions().first()->setChecked(true);
    timer_->stop();

    cur_file_index_--;
    SetPixmap(GetCurrentFile());
}


void MainWindow::on_btn_right_clicked() {
    Q_ASSERT(!action_group_->actions().isEmpty());
    action_group_->actions().first()->setChecked(true);
    timer_->stop();

    NextImage();
}

QString MainWindow::GetCurrentFile() {
    QDir dir(current_folder_);
    dir.setNameFilters(kDefaultFilter);
    QStringList list_files = dir.entryList();
    int total = int(list_files.size());

    if (total == 0) {
        return "";
    }

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
    QDir dir(current_folder_);
    dir.setNameFilters(kDefaultFilter);
    int max_images = dir.entryList().size();

    ui->btn_left->setEnabled(cur_file_index_ > 0);
    ui->btn_right->setEnabled(cur_file_index_ < max_images - 1);
}

void MainWindow::InitContextMenu() {
    context_menu_ = new QMenu(this);

    QAction* action_up_windows = context_menu_->addAction("Поверх всех окон", [this] {
        is_always_on_top_ = !is_always_on_top_;
        setWindowFlags(windowFlags().setFlag(Qt::WindowStaysOnTopHint, is_always_on_top_));
        show();
    });
    action_up_windows->setCheckable(true);

    context_menu_->addAction("Фото из файла ресурсов", [this] {
        SetFolder(kDefaultFolder);
    });

    context_menu_->addAction("Фото из выбранной папки", [this] {
        QString folder = prac::QFileDialog::getExistingDirectory(this, tr("Выберите папку"));
        QDir dir(folder);
        dir.setNameFilters(kDefaultFilter);
        if (!dir.entryList().isEmpty()) {
            SetFolder(folder);
        } else {
            SetFolder("");
        }
    });
    QMenu* period_menu = context_menu_->addMenu("Период переключения");
    QAction* action_0sec = period_menu->addAction("Отключить", [this] {
        timer_->stop();
    });
    QAction* action_1sec = period_menu->addAction("1 секунда", [this] {
        timer_->start(1000);
    });
    QAction* action_5sec = period_menu->addAction("5 секунд", [this] {
        timer_->start(5000);
    });
    QAction* action_10sec = period_menu->addAction("10 секунд", [this] {
        timer_->start(10000);
    });
    action_0sec->setCheckable(true);
    action_1sec->setCheckable(true);
    action_5sec->setCheckable(true);
    action_10sec->setCheckable(true);
    action_0sec->setChecked(true);

    action_group_ = new QActionGroup(this);
    action_group_->addAction(action_0sec);
    action_group_->addAction(action_1sec);
    action_group_->addAction(action_5sec);
    action_group_->addAction(action_10sec);


    context_menu_->addSeparator();

    context_menu_->addAction("Закрыть программу", [this] {
        close();
    });
}

void MainWindow::NextImage()
{
    cur_file_index_++;
    SetPixmap(GetCurrentFile());
}

void MainWindow::SetPixmap(const QString path) {
    active_pixmap = QPixmap(path);
    if (active_pixmap.isNull()) {
        lbl_new_.clear();
        UpdateEnabled();
    } else {
        lbl_new_.setPixmap(active_pixmap);
        FitImage();
        UpdateEnabled();
    }
}
