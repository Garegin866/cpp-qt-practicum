#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_add_clicked() {
    auto movie = GetMovie();
    if (movie.name.isEmpty()) {
        return;
    }

    auto it = std::find(movies_.begin(), movies_.end(), movie);

    if (it != movies_.end()) {
        *it = movie;
    } else {
        movies_.push_back(movie);
    }

    ApplyModel(movie);
    ApplyMovie(movie);
}

void MainWindow::ApplyModel(const Movie &selection) {
    QStringList done;
    QStringList wait;

    for (const auto& movie : movies_) {
        if (movie.is_watched) {
            done.push_back(ToString(movie));
        } else {
            wait.push_back(ToString(movie));
        }
    }

    ui->cb_list_done->clear();
    ui->cb_list_done->addItems(done);

    ui->cb_list_wait->clear();
    ui->cb_list_wait->addItems(wait);

    int index = -1;
    if (selection.is_watched) {
        index = done.indexOf(ToString(selection));
        ui->cb_list_done->setCurrentIndex(index);
    } else {
        index = wait.indexOf(ToString(selection));
        ui->cb_list_wait->setCurrentIndex(index);
    }

    if (index == -1) {
        ui->cb_list_done->setCurrentIndex(-1);
        ui->cb_list_wait->setCurrentIndex(-1);
    }
}

QString MainWindow::ToString(const Movie &movie) {
    QString str_genre = "";
    switch(movie.genre) {
    case Genre::kComedy : str_genre = "Комедия"; break;
    case Genre::kAction : str_genre = "Боевик"; break;
    case Genre::kDrama : str_genre = "Драма"; break;
    case Genre::kFairyTale : str_genre = "Сказка"; break;
    case Genre::kAnimation : str_genre = "Мультфильм"; break;
    case Genre::kHorror : str_genre = "Ужасы"; break;
    }
    return str_genre + " '" + movie.name + "' рейтинг: " + QString::number(movie.rating);
}

QStringList MainWindow::ToString(const QList<Movie> &movies) {
    QStringList result;
    for (const auto& movie : movies) {
        result.push_back(ToString(movie));
    }
    return result;
}

Movie MainWindow::GetMovie() const {
  return Movie{.name = ui->le_name->text(),
    .genre = static_cast<Genre>(ui->cb_genre->currentIndex()),
    .rating = ui->dsb_rating->value(),
    .is_watched = ui->chb_is_done->isChecked()};
}

void MainWindow::ApplyMovie(const Movie &movie) {
    ui->le_name->setText(movie.name);
    ui->cb_genre->setCurrentIndex(static_cast<int>(movie.genre));
    ui->dsb_rating->setValue(movie.rating);
    ui->chb_is_done->setCheckState(movie.is_watched ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void MainWindow::on_cb_list_wait_currentIndexChanged(int index) {
    if (index < 0) {
        return;
    }

    auto movie = movies_[index];
    ApplyMovie(movie);
}

void MainWindow::on_cb_list_done_currentIndexChanged(int index) {
    if (index < 0) {
        return;
    }

    auto movie = movies_[index];
    ApplyMovie(movie);
}
