#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QLabel>
#include <QDir>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetFolder(const QString &d);
    QString GetCurrentFile();

private slots:
    void on_btn_left_clicked();
    void on_btn_right_clicked();

private:
    void resizeEvent(QResizeEvent *event) override;

private:
    void SetPixmap(const QString path);
    void FitImage();
    void UpdateEnabled();

private:
    Ui::MainWindow *ui;
    QPixmap active_pixmap;
    QLabel lbl_new_{this};
    int cur_file_index_;
    QString current_folder_;
};
#endif // MAINWINDOW_H
