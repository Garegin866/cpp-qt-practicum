#include <QtTest>
#include <QCoreApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

#include <mainwindow.h>

#include <iostream>
using namespace std;


namespace {

template<class Widget>
Widget* FindElementByName(QMainWindow* window, const QString& name) {
    auto elements = window->findChildren<Widget*>();

    auto iter = std::find_if(elements.begin(), elements.end(), [&](Widget* elem){
        return elem->objectName() == name;
    });

    return iter == elements.end() ? nullptr : *iter;
}

}

QLabel* FindElementByText(QMainWindow* window, const QString& text) {
    auto elements = window->findChildren<QLabel*>();

    auto iter = std::find_if(elements.begin(), elements.end(), [&](QLabel* elem){
        return elem->text().contains(text);
    });

    return iter == elements.end() ? nullptr : *iter;
}



class TestYourApp : public QObject
{
    Q_OBJECT

    template<class T>
    T* findElementByText(const QString& label) {
        for (T* button : window->findChildren<T*>())
        {
            if (button->text() == label)
            {
                return button;
            }
        }
        return nullptr;
    }

public:
    TestYourApp()=default;
    ~TestYourApp()=default;


private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void TestDefault();
    void TestResize1();
    void TestResize2();
    void TestWidth1();
    void TestWidth2();
    void TestHeight1();
    void TestHeight2();
    void TestExtremeRatio1();
    void TestExtremeRatio2();

private:
    void check_alignment();

    MainWindow* window;
    QLabel* lbl_year;
    QLabel* lbl_q1;
    QLabel* lbl_q2;
    QLabel* lbl_q3;
    QLabel* lbl_q4;
};


void TestYourApp::initTestCase()
{

}

void TestYourApp::init()
{
    window = new MainWindow();
    QVERIFY2(window != nullptr, "Окно приложения не создано");
    window->show();
    QVERIFY2(window->isVisible(), "Окно приложения не активируется");

    lbl_year = FindElementByText(window, "2024");
    QVERIFY2(lbl_year, "Надпись, содержащая год, не найдена.");

    lbl_q1 = FindElementByText(window, "Квартал 1");
    QVERIFY2(lbl_q1, "Надпись, содержащая \"Квартал 1\", не найдена.");

    lbl_q2 = FindElementByText(window, "Квартал 2");
    QVERIFY2(lbl_q2, "Надпись, содержащая \"Квартал 2\", не найдена.");

    lbl_q3 = FindElementByText(window, "Квартал 3");
    QVERIFY2(lbl_q3, "Надпись, содержащая \"Квартал 3\", не найдена.");

    lbl_q4 = FindElementByText(window, "Квартал 4");
    QVERIFY2(lbl_q4, "Надпись, содержащая \"Квартал 4\", не найдена.");

}


QPoint get_center_position(QWidget* widget){

    int half_x = widget->width() / 2;
    int half_y = widget->height() / 2;

    QPoint location = widget->pos();
    location.setX(location.x() + half_x);
    location.setY(location.y() + half_y);

    return location;
}

bool check_tolerance(int expected, int actual, double a_tol = 0, double r_tol = 0.05)
{

    auto diff = std::abs(actual - expected);
    bool in_tol;
    if (a_tol == 0)
    {
        a_tol = double(expected) * r_tol;
    }
    in_tol = double(diff) < a_tol;
    return in_tol;
}


void TestYourApp::check_alignment()
{
    QPoint year_center = get_center_position(lbl_year);

    bool year_in_tol_x = check_tolerance(window->width() / 2, year_center.x(), window->width() / 6);
    bool year_in_tol_y = check_tolerance(window->height() / 2, year_center.y(), window->height() / 6);
    QVERIFY2(year_in_tol_x, "Надпись 2024 не находится в центральной трети по горизонтали");
    QVERIFY2(year_in_tol_y, "Надпись 2024 не находится в центральной трети по вертикали");

    QPoint q1_center = get_center_position(lbl_q1);

    bool q1_in_tol_x = check_tolerance(window->width() / 4, q1_center.x(), window->width() / 4);
    bool q1_in_tol_y = check_tolerance(window->height() / 8, q1_center.y(), window->height() / 8);

    QVERIFY2(q1_in_tol_x, "Надпись \"Квартал 1\" не находится в левой половине");
    QVERIFY2(q1_in_tol_y, "Надпись \"Квартал 1\" не находится в верхней четверти");

    QPoint q2_center = get_center_position(lbl_q1);
    bool q2_in_tol_x = check_tolerance(window->width() / 4, q2_center.x(), window->width() / 4);
    QVERIFY2(q2_in_tol_x, "Надпись \"Квартал 2\" не находится в левой половине");

    QPoint q3_center = get_center_position(lbl_q1);
    bool q3_in_tol_x = check_tolerance(window->width() / 4, q3_center.x(), window->width() / 4);
    QVERIFY2(q3_in_tol_x, "Надпись \"Квартал 3\" не находится в левой половине");

    QPoint q4_center = get_center_position(lbl_q4);

    bool q4_in_tol_x = check_tolerance(window->width() / 4, q4_center.x(), window->width() / 4);
    bool q4_in_tol_y = check_tolerance(window->height() * 7 / 8, q4_center.y(), window->height() / 8);

    QVERIFY2(q4_in_tol_x, "Надпись \"Квартал 4\" не находится в левой половине");
    QVERIFY2(q4_in_tol_y, "Надпись \"Квартал 4\" не находится в нижней четверти");

}


void TestYourApp::TestDefault()
{
    check_alignment();
}


void TestYourApp::TestResize1()
{
    window->resize(window->size() * 0.57);
    check_alignment();
}

void TestYourApp::TestResize2()
{
    window->resize(window->size() * 1.65);
    check_alignment();
}


void TestYourApp::TestWidth1()
{
    window->resize(window->width() * 0.75, window->height());
    check_alignment();
}

void TestYourApp::TestWidth2()
{
    window->resize(window->width() * 1.36, window->height());
    check_alignment();
}

void TestYourApp::TestHeight1()
{
    window->resize(window->width(), window->height() * 0.75);
    check_alignment();
}

void TestYourApp::TestHeight2()
{
    window->resize(window->width(), window->height() * 1.36);
    check_alignment();
}


void TestYourApp::TestExtremeRatio1()
{
    window->resize(window->width() * 0.1, window->height() * 10);
    check_alignment();
}

void TestYourApp::TestExtremeRatio2()
{
    window->resize(window->width() * 12, window->height() * 0.05);
    check_alignment();
}

void TestYourApp::cleanupTestCase()
{
}

void TestYourApp::cleanup()
{
    delete window;
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
