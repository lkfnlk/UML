#ifndef DIALOGPRODUCEFILE_H
#define DIALOGPRODUCEFILE_H

#include <QDialog>

namespace Ui {
class DialogDataProduce;
}

class DialogDataProduce : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDataProduce(QWidget *parent = nullptr);
    ~DialogDataProduce();

    int dataNum(); // 返回对话框输入的数据数量
    int minNum(); // 返回对话框输入的最小值
    int maxNum(); // 返回对话框输入的最大值

private:
    Ui::DialogDataProduce *ui;

    void setData(); // 初始化输入组件的初始值
};

#endif // DIALOGPRODUCEFILE_H
