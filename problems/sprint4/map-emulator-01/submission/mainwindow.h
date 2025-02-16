#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static inline const std::map<std::string, std::string> words {
                                                {"Book", "Книга"},
                                                {"Cinnamon", "Корица"},
                                                {"Cup", "Чашка"},
                                                {"Kettle", "Чайник"},
                                                {"Saucer", "Блюдце"},
                                                {"Sugar", "Сахар"},
                                                {"Tea", "Чай"},
                                                {"Teaspoon", "Чайная ложка"},
                                                };

static inline const std::map<std::string, std::string> authors_and_books {
                                                            {"Т. Пратчетт", "Плоский мир"},
                                                            {"Р. Брэдбери", "Лёд и пламя"},
                                                            {"Д. Адамс", "В основном безвредна"},
                                                            {"Ф. Дик", "Солнечная лотерея"},
                                                            {"А. и Б. Стругацкие", "Жук в муравейнике"},
                                                            {"Ф. Кафка", "Превращение"},
                                                            };

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_set_by_key_clicked();
    void on_btn_erase_clicked();
    void on_btn_clear_clicked();
    void on_btn_find_clicked();

    void on_btn_dec_iterator_clicked();
    void on_btn_inc_iterator_clicked();
    void on_btn_begin_clicked();
    void on_btn_end_clicked();

    void on_btn_books_clicked();
    void on_btn_words_clicked();

    void on_list_widget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model map_model_;
    Ui::MainWindow *ui;
};
