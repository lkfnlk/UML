#include "rectanglepainter.h"
#include <QThread>

RectanglePainter::RectanglePainter(QString title,QVector<int> array, QWidget *parent)
    : QWidget(parent) {
    /*
    // 创建矩形并设置颜色
    for (int i = 0; i < array.size(); ++i) {
        qreal posX = i * 30;
        qreal posY = 200 - array[i] * 2;
        QColor color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        m_rectangles.append(Rectangle(QRectF(posX, posY, 20, array[i] * 2),  array[i], color));
    }*/
    resize(parent->size());
    show();
    this->title=title;
    int n = array.size();
    const int barWidth = width() / n;
    for (int i = 0; i < n; ++i) {
        int barHeight = height() * array[i] / 100; // 计算矩形的高度
        QRectF rect(i * (barWidth + 10), height() - barHeight, barWidth - 1, barHeight);
        QColor color(QColor(56,196,108));
        m_rectangles.append(Rectangle(rect,array[i],color ));
    }


}
void RectanglePainter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int maxHeight = 0;
    // 计算最大高度
    for (const Rectangle &rect : m_rectangles) {
        if (rect.size() > maxHeight)
            maxHeight = rect.size();
    }
    // 根据数组大小绘制矩形
    int n = m_rectangles.size();
    const int barWidth = width() / (n+5);
    for (int i = 0; i < m_rectangles.size(); ++i) {
        const Rectangle &rect = m_rectangles.at(i);
        int he=height();
        int height = rect.size() * he / 100;
        QRectF bar(i * (barWidth+5), he - height, barWidth - 1, he);
        painter.setBrush(rect.color());
        painter.setPen(rect.color());
        painter.drawRect(bar);
        QRect textRect = QRect(bar.x(), bar.y() - 20, bar.width(), 20);
        painter.drawText(textRect, Qt::AlignCenter, QString::number(rect.size()));
    }
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRect textRect = QRect(size().width()/2-100, 0,200, 80);
    painter.drawText(textRect, Qt::AlignCenter, title);

}
void RectanglePainter::swapRectangles(int index1, int index2)
{
    if (index1 < 0 || index1 >= m_rectangles.size() ||
        index2 < 0 || index2 >= m_rectangles.size())
        return;
    //recolor(index1,Qt::blue);
    //recolor(index2,Qt::red);
    //m_rectangles[index1].recolor(Qt::blue);
   // m_rectangles[index2].recolor(Qt::red);
    std::swap(m_rectangles[index1], m_rectangles[index2]);
    update();
}

void RectanglePainter::recolor(int i,QColor c) {
    m_rectangles[i].recolor(c);
    update();
}

void RectanglePainter::replace(int i, int size) {
    m_rectangles[i].resize(size);
}
