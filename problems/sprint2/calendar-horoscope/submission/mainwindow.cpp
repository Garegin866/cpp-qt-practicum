#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include "magic_horoscope.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIntValidator* year_validator = new QIntValidator(1, 9999, this);
    ui->le_year->setValidator(year_validator);

    ui->lbl_calendar->setText(kEmptyYear);
    this->SetHoroscopeFieldsEnabled(false);
    ui->lbl_horoscope->setText(kDataInputDisabled);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rb_eastern_clicked()
{
    UpdateCalendarLabelText();
}

void MainWindow::on_rb_tibetan_clicked()
{
    UpdateCalendarLabelText();
}

void MainWindow::on_rb_zoroastrian_clicked()
{
    UpdateCalendarLabelText();
}

void MainWindow::on_rb_zodiac_clicked()
{
    UpdateHoroscopeLabelText();
}

void MainWindow::on_rb_druid_clicked()
{
    UpdateHoroscopeLabelText();
}

void MainWindow::on_cb_is_date_clicked()
{
    bool enabled = ui->cb_is_date->isChecked();
    this->SetHoroscopeFieldsEnabled(enabled);

    if (!enabled) {
        ui->lbl_horoscope->setText(kDataInputDisabled);
    } else {
        if (ui->le_year->text().isEmpty()) {
            ui->lbl_horoscope->setText(kInvalidDate);
        } else {
            UpdateHoroscopeLabelText();
        }
    }
}

void MainWindow::on_le_year_textChanged(const QString &arg)
{
    UpdateCalendarLabelText();
    UpdateHoroscopeLabelText();
}

void MainWindow::SetHoroscopeFieldsEnabled(bool enabled) {
    ui->gb_horoscope->setEnabled(enabled);
    ui->lbl_day->setEnabled(enabled);
    ui->lbl_month->setEnabled(enabled);

    ui->sb_day->setEnabled(enabled);
    ui->cb_month->setEnabled(enabled);
}

void MainWindow::UpdateCalendarLabelText() {
    QString year_text = ui->le_year->text();
    if (year_text.isEmpty()) {
        ui->lbl_calendar->setText(kEmptyYear);
    } else {
        int year = year_text.toInt();
        QString lbl_calendar_text;
        if (ui->rb_eastern->isChecked()) {
            QString animal = GetAnimalForEasternCalendar(year);
            QString element = GetElementForEasternCalendar(year);
            lbl_calendar_text = kEasternLabelFormat
                                    .arg(year)
                                    .arg(animal)
                                    .arg(element);
        } else if (ui->rb_tibetan->isChecked()) {
            QString animal = GetAnimalForTibetanCalendar(year);
            lbl_calendar_text = kTibeZoroLabelFormat
                                    .arg(year)
                                    .arg(animal);
        } else if (ui->rb_zoroastrian->isChecked()) {
            QString animal = GetAnimalForZoroastrianCalendar(year);
            lbl_calendar_text = kTibeZoroLabelFormat
                                    .arg(year)
                                    .arg(animal);
        }

        ui->lbl_calendar->setText(lbl_calendar_text);
    }
}

void MainWindow::UpdateHoroscopeLabelText() {
    QString lbl_horoscope_text;

    int day = ui->sb_day->value();
    int month = ui->cb_month->currentIndex();
    int year = ui->le_year->text().toInt();
    if (ui->rb_zodiac->isChecked()) {
        QString zodiac = GetZodiac(day, month, year);
        if (zodiac.isEmpty()) {
            lbl_horoscope_text = kInvalidDate;
        } else {
            lbl_horoscope_text = kZodiacLabelFormat
                                     .arg(day, 2, 10, QChar('0'))
                                     .arg(month + 1, 2, 10, QChar('0'))
                                     .arg(zodiac);
        }
    } else if (ui->rb_druid->isChecked()) {
        QString tree = GetTree(day, month, year);
        if (tree.isEmpty()) {
            lbl_horoscope_text = kInvalidDate;
        } else {
            lbl_horoscope_text = kDruidLabelFormat
                                     .arg(day, 2, 10, QChar('0'))
                                     .arg(month + 1, 2, 10, QChar('0'))
                                     .arg(GetTree(day, month, year));
        }
    }

    ui->lbl_horoscope->setText(lbl_horoscope_text);
}


void MainWindow::on_sb_day_valueChanged(int arg1)
{
    UpdateHoroscopeLabelText();
}


void MainWindow::on_cb_month_currentIndexChanged(int index)
{
    UpdateHoroscopeLabelText();
}

