#ifndef RECTANGLEPAINTER_H
#define RECTANGLEPAINTER_H
#include <QWidget>
#include<QPainter>
#include<QTime>
#include<QApplication>
#include<QPushButton>
#include<QVector>

class Rectangle
{
public:
    Rectangle(QRectF rect, int size, QColor color)
        : m_rect(rect), m_size(size), m_color(color) {}
    QRectF rect() const { return m_rect; }
    int size() const { return m_size; }
    void resize(int size){m_size=size;}
    QColor color() const { return m_color; }
    void recolor(QColor c){m_color=c;}
private:
    QRectF m_rect;
    int m_size;
    QColor m_color;
};

class RectanglePainter : public QWidget
{
public:
    RectanglePainter(QString title,QVector<int> array, QWidget *parent = nullptr);
    void swapRectangles(int index1, int index2);
    void recolor(int i, QColor c);
    void replace(int i,int size);
    QVector<Rectangle> get() {return m_rectangles;}
    int count() {return m_rectangles.size();}
    int at(int i) {return m_rectangles[i].size();}
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QVector<Rectangle> m_rectangles;
    QString title;
};
#endif // RECTANGLEPAINTER_H
