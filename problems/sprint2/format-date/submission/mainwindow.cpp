#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

int DaysPerMonth(int month, int year)
{
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29; // February in a leap year.
        } else {
            return 28; // February in a non-leap year.
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30; // April, June, September, November have 30 days.
    } else {
        return 31; // All other months have 31 days.
    }
}

int MainWindow::CalculateDaysFromStartYear(int day, int month, int year)
{
    if(month == 0) {
        return 0;
    }
    int num_days = 0;
    for(size_t num_month = 1; num_month < static_cast<size_t>(month); ++num_month) {
        num_days += DaysPerMonth(num_month, year);
    }
    num_days += day;
    return num_days;
}

QString MainWindow::GetFormatType1(int day, int month, int year)
{
    return QString("%1.%2.%3").arg(day, 2, 10, QChar('0'))
                              .arg(month, 2, 10, QChar('0'))
                              .arg(year);
}

QString MainWindow::GetFormatType2(int day, int month, int year)
{
    return QString("%1/%2/%3").arg(month, 2, 10, QChar('0'))
                              .arg(day, 2, 10, QChar('0'))
                              .arg(year);
}

QString MainWindow::GetFormatType3(int day, int month, int year)
{
    return QString("%1 %2 %3 года").arg(day, 2, 10, QChar('0'))
                                  .arg(GetMonthStr(month))
                                  .arg(year);
}

QString MainWindow::GetStrNumDays(int num_days, int year) {
    return QString("Это %1 день в %2 году")
        .arg(num_days)
        .arg(year);
}

QString MainWindow::GetMonthStr(int month)
{
    switch (month) {
        case 1:
            return "января";
        case 2:
            return "февраля";
        case 3:
            return "марта";
        case 4:
            return "апреля";
        case 5:
            return "мая";
        case 6:
            return "июня";
        case 7:
            return "июля";
        case 8:
            return "августа";
        case 9:
            return "сентября";
        case 10:
            return "октября";
        case 11:
            return "ноября";
        case 12:
            return "декабря";
        default:
            return "неверный месяц";
        }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_day->setValidator(new QIntValidator(1, 31, this));
    ui->le_month->setValidator(new QIntValidator(1, 12, this));
    ui->le_year->setValidator(new QIntValidator(1, 9999, this));


    SetError(kErrorInvalidInput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowFormattedDate()
{
    if(!ui->le_day->hasAcceptableInput() ||
        !ui->le_month->hasAcceptableInput() ||
        !ui->le_year->hasAcceptableInput() ) {
        SetError(kErrorInvalidInput);

        return;
    }

    auto day = ui->le_day->text().toInt();
    auto month = ui->le_month->text().toInt();
    auto year = ui->le_year->text().toInt();

    if (day > DaysPerMonth(month, year)) {
        SetError(kErrorInvalidDate);
        return;
    }

    if (!editing_now_) {
        editing_now_ = true;
        ui->le_date->setText(GetFormatType1(day, month, year));
        editing_now_ = false;
    }

    ui->lbl_format_type1->setText(GetFormatType1(day, month, year));
    ui->lbl_format_type2->setText(GetFormatType2(day, month, year));
    ui->lbl_format_type3->setText(GetFormatType3(day, month, year));

    auto num_days = CalculateDaysFromStartYear(day, month, year);
    ui->lbl_message->setText(GetStrNumDays(num_days, year));
}

void MainWindow::SetError(const QString& err_text)
{
    ui->lbl_format_type1->clear();
    ui->lbl_format_type2->clear();
    ui->lbl_format_type3->clear();
    ui->lbl_message->setText(err_text);
}

void MainWindow::on_le_date_textChanged(const QString&)
{
    if (editing_now_) {
        return;
    }

    auto date = ui->le_date->text();
    auto date_parts = date.split(QRegularExpression("[/. ]"));
    if (date_parts.size() != 3) {
        SetError(kErrorInvalidInput);
        return;
    }

    editing_now_ = true;

    ui->le_day->setText(date_parts[0]);
    ui->le_month->setText(date_parts[1]);
    ui->le_year->setText(date_parts[2]);

    editing_now_ = false;
}

void MainWindow::on_le_day_textChanged(const QString&)
{
    ShowFormattedDate();
}

void MainWindow::on_le_month_textChanged(const QString&)
{
    ShowFormattedDate();
}

void MainWindow::on_le_year_textChanged(const QString&)
{
    ShowFormattedDate();
}
