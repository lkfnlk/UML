#ifndef COMMONHELPER
#define COMMONHELPER
#include <QFile>
#include <QApplication>

class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};
#endif // COMMONHELPER

