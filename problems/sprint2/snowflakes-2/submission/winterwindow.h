#ifndef WINTERWINDOW_H
#define WINTERWINDOW_H

#include <QMainWindow>
#include <prac/QPainter>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui {
class WinterWindow;
}
QT_END_NAMESPACE

struct Vector2D {
    double x;
    double y;
};

struct Point2D {
    double x;
    double y;
};

inline Vector2D RotateVector(Vector2D src, double angle) {
    double a_rad = angle / 180. * M_PI;
    double sin_v = std::sin(a_rad);
    double cos_v = std::cos(a_rad);
    return Vector2D{
        src.x * cos_v + src.y * sin_v, - src.x * sin_v + src.y * cos_v
    };
}

inline Vector2D Add(Vector2D l, Vector2D r) {
    return Vector2D{l.x + r.x, l.y + r.y};
}

inline Point2D Add(Point2D l, Vector2D r) {
    return Point2D{l.x + r.x, l.y + r.y};
}

struct SnowFlakeParams {
    Point2D center;
    QColor color;
    double size;
    double line_width;
    double rotation;
    int depth;
    double scale_factor;
};

class SnowFlake {
public:
    SnowFlake(SnowFlakeParams params) : params_(params) {

    }

    void Draw(prac::QPainter& painter) const {
        painter.setPen(QPen(params_.color, params_.line_width));
        Point2D end;
        for (int i = 0; i < 6; ++i) {
            end = DrawRotatedVector(painter, params_.center, params_.rotation + 60 * i, params_.size);

            if (params_.depth > 0) {
                GetNextLevelFlake(end).Draw(painter);
            }
        }
    }

    QString GetDescription() const {
        return QString("Размер %1\nТолщина линии %2\nПоворот %3")
            .arg(params_.size)
            .arg(params_.line_width)
            .arg(params_.rotation);
    }

    SnowFlake GetNextLevelFlake(Point2D new_center) const {
        return SnowFlakeParams{
            .center = new_center,
            .color = params_.color,
            .size = params_.size * params_.scale_factor,
            .line_width = params_.line_width,
            .rotation = params_.rotation,
            .depth = params_.depth - 1,
            .scale_factor = params_.scale_factor
        };
    }

private:
    static Point2D DrawRotatedVector(prac::QPainter& painter, Point2D center, double angle, double length) {
        Vector2D lay = RotateVector(Vector2D{length, 0}, angle);
        Point2D end = Add(center, lay);

        QPointF start(center.x, center.y);
        QPointF stop(end.x, end.y);
        painter.drawLine(start, stop);

        return end;
    }

private:
    SnowFlakeParams params_;
};

class WinterWindow : public QMainWindow
{
    Q_OBJECT

public:
    WinterWindow(QWidget *parent = nullptr);
    ~WinterWindow();

private slots:
    void on_btn_color_clicked();
    void on_spin_depth_valueChanged(int arg1);

    void on_sld_factor_valueChanged(int value);

private:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::WinterWindow *ui;
    QColor color_ = Qt::white;
};
#endif // WINTERWINDOW_H
