#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Calendar {
    kEastern,
    kTibetan,
    kZoroastrian
};

enum class Horoscope {
    kZodiac,
    kDruid
};

// Error messages
inline const QString kEmptyYear = "Введите год";
inline const QString kDataInputDisabled = "Ввод даты отключён";
inline const QString kInvalidDate = "Такой даты не существует";

// Formats
inline const QString kEasternLabelFormat = "%1 — это год %2. Стихия/цвет — %3";
inline const QString kTibeZoroLabelFormat = "%1 — это год %2";
inline const QString kZodiacLabelFormat = "%1.%2 — ваш знак зодиака %3 по зодиакальному гороскопу";
inline const QString kDruidLabelFormat = "%1.%2 — ваше тотемное дерево %3 по гороскопу друидов";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rb_eastern_clicked();
    void on_rb_tibetan_clicked();
    void on_rb_zoroastrian_clicked();

    void on_rb_zodiac_clicked();
    void on_rb_druid_clicked();

    void on_le_year_textChanged(const QString &arg);
    void on_cb_is_date_clicked();
    void on_sb_day_valueChanged(int arg1);
    void on_cb_month_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Calendar calendar_ = Calendar::kEastern;
    Horoscope horoscope_ = Horoscope::kZodiac;

    void SetHoroscopeFieldsEnabled(bool enabled);
    void UpdateCalendarLabelText();
    void UpdateHoroscopeLabelText();
};
#endif // MAINWINDOW_H
