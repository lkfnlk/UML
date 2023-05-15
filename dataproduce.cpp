#include "dataproduce.h"
#include "ui_dataproduce.h"

DialogDataProduce::DialogDataProduce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDataProduce)
{
    // 此对话框为模态对话框（模态方式），动态创建，用过后删除
    ui->setupUi(this);
    this->setWindowTitle(tr("数据文件信息对话框"));
    setData();
}

DialogDataProduce::~DialogDataProduce()
{
    delete ui;
}

int DialogDataProduce::dataNum()
{
    // 返回对话框输入的数据数量
    return ui->spnDiaDataNum->value();
}

int DialogDataProduce::minNum()
{
    // 返回对话框输入的最小值
    return ui->spnDiaMinNum->value();
}

int DialogDataProduce::maxNum()
{
    // 返回对话框输入的最大值
    return ui->spnDiaMaxNum->value();
}

void DialogDataProduce::setData()
{
    // 初始化输入组件的初始值
    ui->spnDiaDataNum->setValue(20);
    ui->spnDiaMinNum->setValue(1);
    ui->spnDiaMaxNum->setValue(80);
}
