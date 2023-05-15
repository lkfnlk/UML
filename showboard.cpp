#include "showboard.h"
#include "ui_showboard.h"

#include "dataproduce.h"
#include "commonhelper.h"
#include "barthread.h"
#include <windows.h>
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QTime>
#include<qstring.h>
#include<qdebug.h>
//#include <QRandomGenerator>

#include <cmath>
#include <iostream>
using namespace std;


BuildBarChart* BarChartFactory::CreateBarChart(QString str,QVector<int> dataList,QString curStyle)
{
    BuildBarChart *BarChart=NULL;
    if(str=="Bubble")
    {
        BarChart= new BuildBarChart_Bubble(dataList,curStyle);
    }
    else if(str=="Insert")
    {
        BarChart= new BuildBarChart_Insert(dataList,curStyle);
    }
    else if(str=="Select")
    {
        BarChart= new BuildBarChart_Select(dataList,curStyle);
    }
    else if(str=="Heap")
    {
        BarChart= new BuildBarChart_Heap(dataList,curStyle);
    }

    else if(str=="Quick")
    {
        BarChart= new BuildBarChart_Quick(dataList,curStyle);
    }
    else if(str=="Merge")
    {
        BarChart= new BuildBarChart_Merge(dataList,curStyle);
    }
    else if(str=="Radix")
    {
        BarChart= new BuildBarChart_Radix(dataList,curStyle);
    }
    return BarChart;
}
BuildBarChart::BuildBarChart(QVector<int> dataList,QString curStyle)
{
    m_dataList=dataList;
    m_curStyle=curStyle;
}
void BuildBarChart::buildBarChart(QChart *chart, QBarSet *barSet)
{
    chart->removeAllSeries(); // 删除所有序列
    chart->removeAxis(chart->axisX()); // 删除坐标轴
    chart->removeAxis(chart->axisY()); // 删除坐标轴
    int minNum=0,maxNum=0;
    if(barSet->count()!= m_dataList.size())
    {
        for (int i = 0; i < m_dataList.size(); i++)
        {
             barSet->append(m_dataList.at(i));
             if(minNum>m_dataList.at(i))
                 minNum=m_dataList.at(i);
             if(maxNum<m_dataList.at(i))
                 maxNum=m_dataList.at(i);
        }
    }

    QBarSeries *series = new QBarSeries(); // 创建一个柱状图序列QBarSeries
    series->append(barSet); // 添加数据集
    chart->addSeries(series); // 添加柱状图序列

    // 设置横坐标
    QStringList categories;
    for (int i = 1; i <= 5; i++)
        categories << QString::number(i);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setRange(categories.at(0), categories.at(4)); // 这是坐标轴范围
    axisX->setTitleText("位置");
    chart->setAxisX(axisX, series); // 设置横坐标

    // 设置纵坐标
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(minNum, maxNum);
    axisY->setTitleText("数值");
    axisY->setTickCount(11);
    chart->setAxisY(axisY, series);

    if (m_curStyle == ":/qdarkstyle/style.qss") // 当界面为GitHub暗黑背景，所有chart主题为黑色
        chart->setTheme(QChart::ChartThemeDark);

    chart->legend()->setVisible(true); //显示图例
    chart->legend()->setAlignment(Qt::AlignBottom); //图例显示在下方
}



BuildBarChart_Bubble::BuildBarChart_Bubble(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
    m_dataList=dataList;
}

QChart* BuildBarChart_Bubble::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("冒泡排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;

}

BuildBarChart_Insert::BuildBarChart_Insert(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
 m_dataList=dataList;
}


QChart* BuildBarChart_Insert::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("插入排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;
}

BuildBarChart_Select::BuildBarChart_Select(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
 m_dataList=dataList;
}

QChart* BuildBarChart_Select::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("选择排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;
}

BuildBarChart_Quick::BuildBarChart_Quick(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
 m_dataList=dataList;
}

QChart* BuildBarChart_Quick::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("快速排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;
}

BuildBarChart_Merge::BuildBarChart_Merge(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
 m_dataList=dataList;
}

QChart* BuildBarChart_Merge::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("归并排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;
}

BuildBarChart_Heap::BuildBarChart_Heap(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
 m_dataList=dataList;
}

QChart* BuildBarChart_Heap::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("堆排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;
}

BuildBarChart_Radix::BuildBarChart_Radix(QVector<int> dataList,QString curStyle):BuildBarChart(dataList,curStyle)
{
 m_dataList=dataList;
}

QChart* BuildBarChart_Radix::iniBarChart()
{
    QChart *chart = new QChart(); // 创建chart
    chart->setTitle("基数排序动态演示");
    // 不设置动画效果，当数据较大时动画会出现卡顿、降低运行速度，并且显示效果不好
    chart->setAnimationOptions(QChart::NoAnimation);
    return chart;
}


ShowBoard::ShowBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShowBoard)
{
    /*
     * 写在前面
     * 所有排序都是按照从小到大的顺序排列
     * 在showboard.ui文件中，QTabWidget组件的标题可能显示不正常，
     * 但在属性栏中是正确的，而且运行后显示也是正确的（这个标题用英文显示正常，用中文可能有点问题）
    */
    ui->setupUi(this);
    this->setWindowTitle(tr("排序算法演示"));
    //this->setWindowState(Qt::WindowMaximized); // 将整个界面设置为最大
    // 只允许最小化和关闭按钮可用，这样可以使整个界面保持最大，以达到最好的显示效果
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    m_curStyle = ":/qdarkstyle/style.qss";
    CommonHelper::setStyle(m_curStyle);

    // 初始化数据
    m_dataNum = 0; // 数据总数
    m_minNum = 0; // 最小值
    m_maxNum = 0; // 最大值
    m_avgNum = 0; // 平均值
    m_varNum = 0; // 方差
//    m_swapNum.resize(7); // 设置大小
//    m_cmpNum.resize(7);
    for (int i = 0; i < 7; i++)
    {
        m_swapNum[i] = 10;
        m_cmpNum[i] = 10;
    }
//    m_swapNums.resize(7);
//    m_cmpNums.resize(7);
   // m_cmpNum={0};


    ui->tabWidget->setCurrentIndex(0); // 界面首先展示的是索引为0的tab，即冒泡排序

    // 之后会遇到多次该语句的出现，因为没有这个会从暗黑变为白色
    if (m_curStyle == ":/qdarkstyle/style.qss") // 当界面为GitHub暗黑背景，所有chart主题为黑色
    {
        //ui->chartViewBubble->chart()->setTheme(QChart::ChartThemeDark);
        //ui->chartViewInsert->chart()->setTheme(QChart::ChartThemeDark);
        //ui->chartViewSelect->chart()->setTheme(QChart::ChartThemeDark);
        //ui->chartViewHeap->chart()->setTheme(QChart::ChartThemeDark);
        //ui->chartViewQuick->chart()->setTheme(QChart::ChartThemeDark);
        //ui->chartViewMerge->chart()->setTheme(QChart::ChartThemeDark);
        //ui->chartViewRadix->chart()->setTheme(QChart::ChartThemeDark);
        ui->chartViewPieCmp->chart()->setTheme(QChart::ChartThemeDark);
        ui->chartViewPieSwap->chart()->setTheme(QChart::ChartThemeDark);
    }
    //bubbleThread=AlgorithmFactory::CreateAlgorithm("Bubble");

    m_bubbleThread = new bubbleBarThread;
    connect(m_bubbleThread, SIGNAL(bubbleShowDone(int, int)), this, SLOT(on_bubbleShowDone(int, int)));
    m_insertThread = new insertBarThread;
    connect(m_insertThread, SIGNAL(insertShowDone(int, int)), this, SLOT(on_insertShowDone(int, int)));
    m_selectThread = new selectBarThread;
    connect(m_selectThread, SIGNAL(selectShowDone(int, int)), this, SLOT(on_selectShowDone(int, int)));
    m_heapThread = new heapBarThread;
    connect(m_heapThread, SIGNAL(heapShowDone(int, int)), this, SLOT(on_heapShowDone(int, int)));
    m_quickThread = new quickBarThread;
    connect(m_quickThread, SIGNAL(quickShowDone(int, int)), this, SLOT(on_quickShowDone(int, int)));
    m_mergeThread = new mergeBarThread;
    connect(m_mergeThread, SIGNAL(mergeShowDone(int, int)), this, SLOT(on_mergeShowDone(int, int)));
    m_radixThread = new radixBarThread;
    connect(m_radixThread, SIGNAL(radixShowDone(int, int)), this, SLOT(on_radixShowDone(int, int)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tabWidget_currentChanged(int)));


}

ShowBoard::~ShowBoard()
{
    delete ui;
}

void ShowBoard::closeEvent(QCloseEvent *event)
{
    // 窗口关闭时间，必须结束线程
    if (m_bubbleThread->isRunning())
    {
        m_bubbleThread->stopThread();
        m_bubbleThread->wait();
    }
    if (m_insertThread->isRunning())
    {
        m_insertThread->stopThread();
        m_insertThread->wait();
    }
    if (m_selectThread->isRunning())
    {
        m_selectThread->stopThread();
        m_selectThread->wait();
    }
    if (m_heapThread->isRunning())
    {
        m_heapThread->stopThread();
        m_heapThread->wait();
    }
    if (m_quickThread->isRunning())
    {
        m_quickThread->stopThread();
        m_quickThread->wait();
    }
    if (m_mergeThread->isRunning())
    {
        m_mergeThread->stopThread();
        m_mergeThread->wait();
    }
    if (m_radixThread->isRunning())
    {
        m_radixThread->stopThread();
        m_radixThread->wait();
    }
    event->accept();
}
void ShowBoard::on_btnDataProdeuce_clicked()
{
    DialogDataProduce *dlgDataProduce = new DialogDataProduce(this);
    int ret = dlgDataProduce->exec(); // 以模态方式显示对话框
    if (ret == QDialog::Accepted)
    {
        m_dataNum = dlgDataProduce->dataNum();
        m_minNum = dlgDataProduce->minNum();
        m_maxNum = dlgDataProduce->maxNum();
       m_dataList.clear();
        QTime randtime;
        randtime = QTime::currentTime();
        qsrand(randtime.msec()+randtime.second()*1000); //以当前时间ms为随机种子
        int sum=0;
        for(int i=0;i<m_dataNum;i++)
        {
            int n=qrand()%(m_maxNum-m_minNum)+m_minNum;//生成随机数
            m_dataList.append(n);
            sum+=n;
        }
        m_avgNum = (double)sum / m_dataNum;
        m_varNum = 0;
        for (int i = 0; i < m_dataNum; i++)
            m_varNum += pow((m_dataList.at(i)-m_avgNum), 2) / m_dataNum;

    }
    delete dlgDataProduce;

    //工厂创建柱状图工厂
    m_bubbleBarChart=m_barChartFactory->CreateBarChart("Bubble",m_dataList,m_curStyle);
    m_insertBarChart=m_barChartFactory->CreateBarChart("Insert",m_dataList,m_curStyle);
    m_selectBarChart=m_barChartFactory->CreateBarChart("Select",m_dataList,m_curStyle);
    m_mergeBarChart=m_barChartFactory->CreateBarChart("Merge",m_dataList,m_curStyle);
    m_heapBarChart=m_barChartFactory->CreateBarChart("Heap",m_dataList,m_curStyle);
    m_radixBarChart=m_barChartFactory->CreateBarChart("Radix",m_dataList,m_curStyle);
    m_quickBarChart=m_barChartFactory->CreateBarChart("Quick",m_dataList,m_curStyle);

    //数据信息写入
    ui->lieDataNums->setText(QString::asprintf("%d", m_dataNum));
    ui->lieMinNum->setText(QString::asprintf("%d", m_minNum));
    ui->lieMaxNum->setText(QString::asprintf("%d", m_maxNum));
    ui->lieAvgNum->setText(QString::asprintf("%.2f", m_avgNum));
    ui->lieVarNum->setText(QString::asprintf("%.3f", m_varNum));
     QString s="";
    for(int i=0;i<m_dataList.size();i++)
    {
        s+=QString::number(m_dataList[i],10)+" ";
    }
    ui->DataShow->setText(s);


    //排序柱状图初始化
    buildBarChart_Bubble();
    buildBarChart_Insert();
    buildBarChart_Merge();
    buildBarChart_Select();
    buildBarChart_Quick();
    buildBarChart_Radix();
     buildBarChart_Heap();

   //排序饼状图初始化
    iniPieChart_Cmp();
    buildPieChart_Cmp();
    iniPieChart_Swap();
    buildPieChart_Swap();



}



//****************************************************************************
//*********************************冒泡排序************************************
//****************************************************************************

void ShowBoard::buildBarChart_Bubble()
{
    //QChart *bubblechart=m_bubbleBarChart->iniBarChart();

    bulle_RecP=new RectanglePainter(QString("冒泡排序动态演示"),m_dataList,ui->widget_Bubble);//+

    //ui->chartViewBubble->setChart(bubblechart); // 为chartViewBubble设置chart
    //ui->chartViewBubble->setRenderHint(QPainter::Antialiasing);
    if (m_bubbleThread->isRunning())
    {
        m_bubbleThread->stopThread();
        m_bubbleThread->wait();
    }
    //QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
    //m_bubbleBarChart->buildBarChart(bubblechart, barSet);
    delete m_bubbleThread; // 清空之前的bubbleThread，代码保证在此语句前，线程已终止
    int speed=ui->speed_Box->value()*100;
    //m_bubbleThread = new bubbleBarThread(speed,bulle_RecP); // 调用演示对象
    m_bubbleThread=m_algorithmFactory->CreateAlgorithm("Bubble",speed,bulle_RecP);
    connect(m_bubbleThread, SIGNAL(bubbleShowDone(int, int)), this, SLOT(on_bubbleShowDone(int, int)));
    m_bubbleThread->start(); // 启动线程
    ui->labBubbleTip->setText(tr("当前状态：冒泡排序演示就绪"));
    ui->btnBubbleStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnBubblePause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnBubbleStop->setEnabled(false);
    ui->btnBubbleInit->setEnabled(false);
}

void ShowBoard::on_btnBubbleStart_clicked()
{
    // 开始冒泡排序动态演示
    m_bubbleThread->beginThread();
    ui->labBubbleTip->setText(tr("当前状态：冒泡排序演示中..."));
    ui->btnBubbleStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnBubblePause->setEnabled(true);
    ui->btnBubbleStop->setEnabled(true);
    ui->btnBubbleInit->setEnabled(true);
}

void ShowBoard::on_btnBubblePause_clicked()
{
    // 暂停冒泡排序动态演示
    m_bubbleThread->pauseThread();
    ui->labBubbleTip->setText(tr("当前状态：冒泡排序演示暂停"));
    ui->btnBubbleStart->setEnabled(true);
    ui->btnBubblePause->setEnabled(false);
    ui->btnBubbleStop->setEnabled(true);
    ui->btnBubbleInit->setEnabled(true);
}

void ShowBoard::on_btnBubbleStop_clicked()
{
    // 终止冒泡排序动态演示
    if (m_bubbleThread->isRunning())
    {
        m_bubbleThread->stopThread();
        m_bubbleThread->wait();
    }
    ui->labBubbleTip->setText(tr("当前状态：冒泡排序演示终止"));
    ui->btnBubbleStart->setEnabled(false);
    ui->btnBubblePause->setEnabled(false);
    ui->btnBubbleStop->setEnabled(false);
    ui->btnBubbleInit->setEnabled(true);
}

void ShowBoard::on_btnBubbleInit_clicked()
{

    buildBarChart_Bubble();

}

void ShowBoard::on_bubbleShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[0] = cmpNum;
   // m_cmpNums[0].append(cmpNum);
    this->m_swapNum[0] = swapNum;
   // m_swapNums[0].append(swapNum);
    ui->labBubbleTip->setText(tr("当前状态：冒泡排序演示结束"));
    ui->btnBubbleStart->setEnabled(false);
    ui->btnBubblePause->setEnabled(false);
    ui->btnBubbleStop->setEnabled(false);
    ui->btnBubbleInit->setEnabled(true);
}

//****************************************************************************
//*********************************插入排序************************************
//****************************************************************************



void ShowBoard::buildBarChart_Insert()
{
    insert_RecP=new RectanglePainter(QString("插入排序动态演示"),m_dataList,ui->widget_Insert);

    //QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
   int speed=ui->speed_Box->value()*100;
    //QChart *insertchart=m_insertBarChart->iniBarChart();
    //ui->chartViewInsert->setChart(insertchart); // 为chartViewinsert设置chart
    //ui->chartViewInsert->setRenderHint(QPainter::Antialiasing);
    if (m_insertThread->isRunning())
    {
        m_insertThread->stopThread();
        m_insertThread->wait();
    }
    //m_insertBarChart->buildBarChart(insertchart, barSet);
    delete m_insertThread; // 清空之前的insertThread，代码保证在此语句前，线程已终止
    m_insertThread = new insertBarThread(speed,insert_RecP); // 调用演示对象
    connect(m_insertThread, SIGNAL(insertShowDone(int, int)), this, SLOT(on_insertShowDone(int, int)));
    m_insertThread->start(); // 启动线程
    ui->labInsertTip->setText(tr("当前状态：插入排序演示就绪"));
    ui->btnInsertStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnInsertPause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnInsertStop->setEnabled(false);
    ui->btnInsertInit->setEnabled(false);
}

void ShowBoard::on_btnInsertStart_clicked()
{
    // 开始插入排序动态演示
    m_insertThread->beginThread();
    ui->labInsertTip->setText(tr("当前状态：插入排序演示中..."));
    ui->btnInsertStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnInsertPause->setEnabled(true);
    ui->btnInsertStop->setEnabled(true);
    ui->btnInsertInit->setEnabled(true);
}

void ShowBoard::on_btnInsertPause_clicked()
{
    // 暂停插入排序动态演示
    m_insertThread->pauseThread();
    ui->labInsertTip->setText(tr("当前状态：插入排序演示暂停"));
    ui->btnInsertStart->setEnabled(true);
    ui->btnInsertPause->setEnabled(false);
    ui->btnInsertStop->setEnabled(true);
    ui->btnInsertInit->setEnabled(true);
}

void ShowBoard::on_btnInsertStop_clicked()
{
    // 终止插入排序动态演示
    if (m_insertThread->isRunning())
    {
        m_insertThread->stopThread();
        m_insertThread->wait();
    }
    ui->labInsertTip->setText(tr("当前状态：插入排序演示终止"));
    ui->btnInsertStart->setEnabled(false);
    ui->btnInsertPause->setEnabled(false);
    ui->btnInsertStop->setEnabled(false);
    ui->btnInsertInit->setEnabled(true);
}

void ShowBoard::on_btnInsertInit_clicked()
{
    // 重新初始化插入排序动态演示
    // 关闭之前的线程，重新build
    buildBarChart_Insert();
}

void ShowBoard::on_insertShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[1] = cmpNum;
    this->m_swapNum[1] = swapNum;
    ui->labInsertTip->setText(tr("当前状态：插入排序演示结束"));
    ui->btnInsertStart->setEnabled(false);
    ui->btnInsertPause->setEnabled(false);
    ui->btnInsertStop->setEnabled(false);
    ui->btnInsertInit->setEnabled(true);
}

//****************************************************************************
//*********************************选择排序************************************
//****************************************************************************



void ShowBoard::buildBarChart_Select()
{
    select_RecP=new RectanglePainter(QString("选择排序动态演示"),m_dataList,ui->widget_Select);

    //QChart *selectchart=m_selectBarChart->iniBarChart();
    //QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
   int speed=ui->speed_Box->value()*100;
    //ui->chartViewSelect->setChart(selectchart); // 为chartViewselect设置chart
    //ui->chartViewSelect->setRenderHint(QPainter::Antialiasing);
    if (m_selectThread->isRunning())
    {
        m_selectThread->stopThread();
        m_selectThread->wait();
    }
    //m_selectBarChart->buildBarChart(selectchart, barSet);
    delete m_selectThread; // 清空之前的selectThread，代码保证在此语句前，线程已终止
    m_selectThread = new selectBarThread(speed,select_RecP); // 调用演示对象
    connect(m_selectThread, SIGNAL(selectShowDone(int, int)), this, SLOT(on_selectShowDone(int, int)));
    m_selectThread->start(); // 启动线程
    ui->labSelectTip->setText(tr("当前状态：选择排序演示就绪"));
    ui->btnSelectStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnSelectPause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnSelectStop->setEnabled(false);
    ui->btnSelectInit->setEnabled(false);
}

void ShowBoard::on_btnSelectStart_clicked()
{
    // 开始选择排序动态演示
    m_selectThread->beginThread();
    ui->labSelectTip->setText(tr("当前状态：选择排序演示中..."));
    ui->btnSelectStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnSelectPause->setEnabled(true);
    ui->btnSelectStop->setEnabled(true);
    ui->btnSelectInit->setEnabled(true);
}

void ShowBoard::on_btnSelectPause_clicked()
{
    // 暂停选择排序动态演示
    m_selectThread->pauseThread();
    ui->labSelectTip->setText(tr("当前状态：选择排序演示暂停"));
    ui->btnSelectStart->setEnabled(true);
    ui->btnSelectPause->setEnabled(false);
    ui->btnSelectStop->setEnabled(true);
    ui->btnSelectInit->setEnabled(true);
}

void ShowBoard::on_btnSelectStop_clicked()
{
    // 终止选择排序动态演示
    if (m_selectThread->isRunning())
    {
        m_selectThread->stopThread();
        m_selectThread->wait();
    }
    ui->labSelectTip->setText(tr("当前状态：选择排序演示终止"));
    ui->btnSelectStart->setEnabled(false);
    ui->btnSelectPause->setEnabled(false);
    ui->btnSelectStop->setEnabled(false);
    ui->btnSelectInit->setEnabled(true);
}

void ShowBoard::on_btnSelectInit_clicked()
{  
    buildBarChart_Select(); 
}

void ShowBoard::on_selectShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[2] = cmpNum;
    //m_cmpNums[2].append(cmpNum);
    this->m_swapNum[2] = swapNum;
   // m_swapNums[2].append(swapNum);
    ui->labSelectTip->setText(tr("当前状态：选择排序演示结束"));
    ui->btnSelectStart->setEnabled(false);
    ui->btnSelectPause->setEnabled(false);
    ui->btnSelectStop->setEnabled(false);
    ui->btnSelectInit->setEnabled(true);
}



//****************************************************************************
//*********************************堆排序************************************
//****************************************************************************


void ShowBoard::buildBarChart_Heap()
{
    heap_RecP=new RectanglePainter(QString("堆排序动态演示"),m_dataList,ui->widget_Heap);
   // QChart *heapchart=m_heapBarChart->iniBarChart();
    //QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
   int speed=ui->speed_Box->value()*100;
    //ui->chartViewHeap->setChart(heapchart); // 为chartViewheap设置chart
    //ui->chartViewHeap->setRenderHint(QPainter::Antialiasing);
    if (m_heapThread->isRunning())
    {
        m_heapThread->stopThread();
        m_heapThread->wait();
    }
   // m_heapBarChart->buildBarChart(heapchart, barSet);
    delete m_heapThread; // 清空之前的heapThread，代码保证在此语句前，线程已终止
    m_heapThread = new heapBarThread(speed,heap_RecP); // 调用演示对象
    connect(m_heapThread, SIGNAL(heapShowDone(int, int)), this, SLOT(on_heapShowDone(int, int)));
    m_heapThread->start(); // 启动线程
    ui->labHeapTip->setText(tr("当前状态：堆排序演示就绪"));
    ui->btnHeapStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnHeapPause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnHeapStop->setEnabled(false);
    ui->btnHeapInit->setEnabled(false);
}

void ShowBoard::on_btnHeapStart_clicked()
{
    // 开始堆排序动态演示
    m_heapThread->beginThread();
    ui->labHeapTip->setText(tr("当前状态：堆排序演示中..."));
    ui->btnHeapStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnHeapPause->setEnabled(true);
    ui->btnHeapStop->setEnabled(true);
    ui->btnHeapInit->setEnabled(true);
}

void ShowBoard::on_btnHeapPause_clicked()
{
    // 暂停堆排序动态演示
    m_heapThread->pauseThread();
    ui->labHeapTip->setText(tr("当前状态：堆排序演示暂停"));
    ui->btnHeapStart->setEnabled(true);
    ui->btnHeapPause->setEnabled(false);
    ui->btnHeapStop->setEnabled(true);
    ui->btnHeapInit->setEnabled(true);
}

void ShowBoard::on_btnHeapStop_clicked()
{
    // 终止堆排序动态演示
    if (m_heapThread->isRunning())
    {
        m_heapThread->stopThread();
        m_heapThread->wait();
    }
    ui->labHeapTip->setText(tr("当前状态：堆排序演示终止"));
    ui->btnHeapStart->setEnabled(false);
    ui->btnHeapPause->setEnabled(false);
    ui->btnHeapStop->setEnabled(false);
    ui->btnHeapInit->setEnabled(true);
}

void ShowBoard::on_btnHeapInit_clicked()
{
    buildBarChart_Heap();
}

void ShowBoard::on_heapShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[3] = cmpNum;
    //m_cmpNums[5].append(cmpNum);
    this->m_swapNum[3] = swapNum;
    //m_swapNums[5].append(swapNum);
    ui->labHeapTip->setText(tr("当前状态：堆排序演示结束"));
    ui->btnHeapStart->setEnabled(false);
    ui->btnHeapPause->setEnabled(false);
    ui->btnHeapStop->setEnabled(false);
    ui->btnHeapInit->setEnabled(true);
}

//****************************************************************************
//*********************************快速排序************************************
//****************************************************************************



void ShowBoard::buildBarChart_Quick()
{
    quick_RecP=new RectanglePainter(QString("快速排序动态演示"),m_dataList,ui->widget_Quick);
    QChart *quickchart=m_quickBarChart->iniBarChart();
    QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
   int speed=ui->speed_Box->value()*100;
    //ui->chartViewQuick->setChart(quickchart); // 为chartViewquick设置chart
    //ui->chartViewQuick->setRenderHint(QPainter::Antialiasing);
    if (m_quickThread->isRunning())
    {
        m_quickThread->stopThread();
        m_quickThread->wait();
    }
    m_quickBarChart->buildBarChart(quickchart, barSet);
    delete m_quickThread; // 清空之前的quickThread，代码保证在此语句前，线程已终止
    m_quickThread = new quickBarThread(speed,quick_RecP); // 调用演示对象
    connect(m_quickThread, SIGNAL(quickShowDone(int, int)), this, SLOT(on_quickShowDone(int, int)));
    m_quickThread->start(); // 启动线程
    ui->labQuickTip->setText(tr("当前状态：快速排序演示就绪"));
    ui->btnQuickStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnQuickPause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnQuickStop->setEnabled(false);
    ui->btnQuickInit->setEnabled(false);
}

void ShowBoard::on_btnQuickStart_clicked()
{
    // 开始快速排序动态演示
    m_quickThread->beginThread();
    ui->labQuickTip->setText(tr("当前状态：快速排序演示中..."));
    ui->btnQuickStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnQuickPause->setEnabled(true);
    ui->btnQuickStop->setEnabled(true);
    ui->btnQuickInit->setEnabled(true);
}

void ShowBoard::on_btnQuickPause_clicked()
{
    // 暂停快速排序动态演示
    m_quickThread->pauseThread();
    ui->labQuickTip->setText(tr("当前状态：快速排序演示暂停"));
    ui->btnQuickStart->setEnabled(true);
    ui->btnQuickPause->setEnabled(false);
    ui->btnQuickStop->setEnabled(true);
    ui->btnQuickInit->setEnabled(true);
}


void ShowBoard::on_btnQuickStop_clicked()
{
    // 终止快速排序动态演示
    if (m_quickThread->isRunning())
    {
        m_quickThread->stopThread();
        m_quickThread->wait();
    }
    ui->labQuickTip->setText(tr("当前状态：快速排序演示终止"));
    ui->btnQuickStart->setEnabled(false);
    ui->btnQuickPause->setEnabled(false);
    ui->btnQuickStop->setEnabled(false);
    ui->btnQuickInit->setEnabled(true);
}


void ShowBoard::on_btnQuickInit_clicked()
{

    buildBarChart_Quick();

}

void ShowBoard::on_quickShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[4] = cmpNum;
    //m_cmpNums[6].append(cmpNum);
    this->m_swapNum[4] = swapNum;
    //m_swapNums[6].append(swapNum);
    ui->labQuickTip->setText(tr("当前状态：快速排序演示结束"));
    ui->btnQuickStart->setEnabled(false);
    ui->btnQuickPause->setEnabled(false);
    ui->btnQuickStop->setEnabled(false);
    ui->btnQuickInit->setEnabled(true);
}

//****************************************************************************
//*********************************归并排序************************************
//****************************************************************************


void ShowBoard::buildBarChart_Merge()
{
    mergeBar_RecP=new RectanglePainter(QString("归并排序动态演示"),m_dataList,ui->widget_Merge);
    QChart *mergechart=m_mergeBarChart->iniBarChart();
    QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
   int speed=ui->speed_Box->value()*100;
    //ui->chartViewMerge->setChart(mergechart); // 为chartViewmerge设置chart
    //ui->chartViewMerge->setRenderHint(QPainter::Antialiasing);
    if (m_mergeThread->isRunning())
    {
        m_mergeThread->stopThread();
        m_mergeThread->wait();
    }
    m_mergeBarChart->buildBarChart(mergechart, barSet);
    delete m_mergeThread; // 清空之前的mergeThread，代码保证在此语句前，线程已终止
    m_mergeThread = new mergeBarThread(speed,mergeBar_RecP); // 调用演示对象
    connect(m_mergeThread, SIGNAL(mergeShowDone(int, int)), this, SLOT(on_mergeShowDone(int, int)));
    m_mergeThread->start(); // 启动线程
    ui->labMergeTip->setText(tr("当前状态：归并排序演示就绪"));
    ui->btnMergeStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnMergePause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnMergeStop->setEnabled(false);
    ui->btnMergeInit->setEnabled(false);
}

void ShowBoard::on_btnMergeStart_clicked()
{
    // 开始归并排序动态演示
    m_mergeThread->beginThread();
    ui->labMergeTip->setText(tr("当前状态：归并排序演示中..."));
    ui->btnMergeStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnMergePause->setEnabled(true);
    ui->btnMergeStop->setEnabled(true);
    ui->btnMergeInit->setEnabled(true);
}

void ShowBoard::on_btnMergePause_clicked()
{
    // 暂停归并排序动态演示
    m_mergeThread->pauseThread();
    ui->labMergeTip->setText(tr("当前状态：归并排序演示暂停"));
    ui->btnMergeStart->setEnabled(true);
    ui->btnMergePause->setEnabled(false);
    ui->btnMergeStop->setEnabled(true);
    ui->btnMergeInit->setEnabled(true);
}

void ShowBoard::on_btnMergeStop_clicked()
{
    // 终止归并排序动态演示
    if (m_mergeThread->isRunning())
    {
        m_mergeThread->stopThread();
        m_mergeThread->wait();
    }
    ui->labMergeTip->setText(tr("当前状态：归并排序演示终止"));
    ui->btnMergeStart->setEnabled(false);
    ui->btnMergePause->setEnabled(false);
    ui->btnMergeStop->setEnabled(false);
    ui->btnMergeInit->setEnabled(true);
}

void ShowBoard::on_btnMergeInit_clicked()
{

    buildBarChart_Merge();

}

void ShowBoard::on_mergeShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[5] = cmpNum;
    //m_cmpNums[7].append(cmpNum);
    this->m_swapNum[5] = swapNum;
    //m_swapNums[7].append(swapNum);
    ui->labMergeTip->setText(tr("当前状态：归并排序演示结束"));
    ui->btnMergeStart->setEnabled(false);
    ui->btnMergePause->setEnabled(false);
    ui->btnMergeStop->setEnabled(false);
    ui->btnMergeInit->setEnabled(true);
}

//****************************************************************************
//*********************************基数排序************************************
//****************************************************************************



void ShowBoard::buildBarChart_Radix()
{
    radix_RecP=new RectanglePainter(QString("基数排序动态演示"),m_dataList,ui->widget_Radix);
    QChart *radixchart=m_radixBarChart->iniBarChart();
    QBarSet *barSet = new QBarSet(tr("随机数")); // 创建一个数据集QBarSet
   int speed=ui->speed_Box->value()*100;
    //ui->chartViewRadix->setChart(radixchart); // 为chartViewradix设置chart
    //ui->chartViewRadix->setRenderHint(QPainter::Antialiasing);
    if (m_radixThread->isRunning())
    {
        m_radixThread->stopThread();
        m_radixThread->wait();
    }
    m_radixBarChart->buildBarChart(radixchart, barSet);
    delete m_radixThread; // 清空之前的radixThread，代码保证在此语句前，线程已终止
    m_radixThread = new radixBarThread(speed,radix_RecP); // 调用演示对象
    connect(m_radixThread, SIGNAL(radixShowDone(int, int)), this, SLOT(on_radixShowDone(int, int)));
    m_radixThread->start(); // 启动线程
    ui->labRadixTip->setText(tr("当前状态：基数排序演示就绪"));
    ui->btnRadixStart->setEnabled(true); // 虽然默认为true，但这样更清晰
    ui->btnRadixPause->setEnabled(false); // 只有在开始演示后(begin)，才能暂停和终止演示
    ui->btnRadixStop->setEnabled(false);
    ui->btnRadixInit->setEnabled(false);
}

void ShowBoard::on_btnRadixStart_clicked()
{
    // 开始基数排序动态演示
    m_radixThread->beginThread();
    ui->labRadixTip->setText(tr("当前状态：基数排序演示中..."));
    ui->btnRadixStart->setEnabled(false); // 开始演示后，再点击开始虽然没影响，但在逻辑上是不对的
    ui->btnRadixPause->setEnabled(true);
    ui->btnRadixStop->setEnabled(true);
    ui->btnRadixInit->setEnabled(true);
}

void ShowBoard::on_btnRadixPause_clicked()
{
    // 暂停基数排序动态演示
    m_radixThread->pauseThread();
    ui->labRadixTip->setText(tr("当前状态：基数排序演示暂停"));
    ui->btnRadixStart->setEnabled(true);
    ui->btnRadixPause->setEnabled(false);
    ui->btnRadixStop->setEnabled(true);
    ui->btnRadixInit->setEnabled(true);
}

void ShowBoard::on_btnRadixStop_clicked()
{
    // 终止基数排序动态演示
    if (m_radixThread->isRunning())
    {
        m_radixThread->stopThread();
        m_radixThread->wait();
    }
    ui->labRadixTip->setText(tr("当前状态：基数排序演示终止"));
    ui->btnRadixStart->setEnabled(false);
    ui->btnRadixPause->setEnabled(false);
    ui->btnRadixStop->setEnabled(false);
    ui->btnRadixInit->setEnabled(true);
}

void ShowBoard::on_btnRadixInit_clicked()
{

    buildBarChart_Radix();

}

void ShowBoard::on_radixShowDone(int cmpNum, int swapNum)
{
    this->m_cmpNum[6] = cmpNum;
   // m_cmpNums[8].append(cmpNum);
    this->m_swapNum[6] = swapNum;
   // m_swapNums[8].append(swapNum);
    ui->labRadixTip->setText(tr("当前状态：基数排序演示结束"));
    ui->btnRadixStart->setEnabled(false);
    ui->btnRadixPause->setEnabled(false);
    ui->btnRadixStop->setEnabled(false);
    ui->btnRadixInit->setEnabled(true);
}

//****************************************************************************
//*******************************比较次数饼图**********************************
//****************************************************************************

void ShowBoard::iniPieChart_Cmp()
{
    //饼图初始化
    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewPieCmp->setChart(chart);
    ui->chartViewPieCmp->setRenderHint(QPainter::Antialiasing);
}

void ShowBoard::buildPieChart_Cmp()
{
    // 绘制饼图
    QChart *chart =ui->chartViewPieCmp->chart(); // 获取chart对象
    chart->removeAllSeries(); // 删除所有序列
    int cmpsum=0;

    QPieSeries *series = new QPieSeries(); // 创建饼图序列
    series->setHoleSize(0); // 饼图中间空心的大小
    series->setPieSize(0.55);

    for (int i = 0; i < 7; i++) // 添加分块数据，分别代表各算法，忽略箱子排序和基数排序
    {
        // 添加一个饼图分块数据：标签，数值
         series->append(ui->tabWidget->tabText(i), m_cmpNum[i]);
         //qDebug()<<"比较次数"<<ui->tabWidget->tabText(i)<<m_cmpNum[i]<<endl;
         cmpsum+=m_cmpNum[i];
    }

    QPieSlice *slice; // 饼图分块
    for(int i = 0; i < 7; i++) // 设置每个分块的标签文字，忽略箱子排序和基数排序
    {
        slice =series->slices().at(i); // 获取分块
        slice->setLabel(slice->label().left(2)+QString::number(slice->value()/cmpsum*100)+"%"); // 设置分块的标签
       // qDebug()<<"比较占比"<<slice->label().left(2)+QString::number(slice->value()/cmpsum*100)+"%"<<endl;
    }

    series->setLabelsVisible(true); // 只影响当前的slices，必须添加完slice之后再设置
    chart->addSeries(series); //添加饼图序列
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setVisible(false);
}

void ShowBoard::on_btnCmp_clicked()
{
    buildPieChart_Cmp();
}

//****************************************************************************
//*******************************交换次数饼图**********************************
//****************************************************************************

void ShowBoard::iniPieChart_Swap()
{
    //饼图初始化
    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewPieSwap->setChart(chart);
    ui->chartViewPieSwap->setRenderHint(QPainter::Antialiasing);
}

void ShowBoard::buildPieChart_Swap()
{
    // 绘制饼图
    QChart *chart =ui->chartViewPieSwap->chart(); // 获取chart对象
    chart->removeAllSeries(); // 删除所有序列

    QPieSeries *series = new QPieSeries(); // 创建饼图序列
    series->setHoleSize(0); // 饼图中间空心的大小
    series->setPieSize(0.55);
    int swpsum=0;

    for (int i = 0; i < 7; i++) // 添加分块数据，分别代表各算法，忽略箱子排序和基数排序
    {
        // 添加一个饼图分块数据：标签，数值
         series->append(ui->tabWidget->tabText(i), m_swapNum[i]);
         swpsum+=m_swapNum[i];
         //qDebug()<<"交换次数"<<ui->tabWidget->tabText(i)<<m_swapNum[i]<<endl;

    }


    QPieSlice *slice; // 饼图分块
    for(int i = 0; i < 7; i++) // 设置每个分块的标签文字，忽略箱子排序和基数排序
    {

        slice =series->slices().at(i); // 获取分块
        slice->setLabel(slice->label().left(2)+QString::number(slice->value()/swpsum*100)+"%"); // 设置分块的标签
        //qDebug()<<"交换占比"<<slice->label().left(2)+QString::number(slice->value()/swpsum*100)+"%"<<endl;

    }

    series->setLabelsVisible(true); // 只影响当前的slices，必须添加完slice之后再设置
    chart->addSeries(series); //添加饼图序列
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setVisible(false);
}

void ShowBoard::on_btnSwap_clicked()
{
    buildPieChart_Swap();
}

//****************************************************************************
//*******************************排序介绍**********************************
//****************************************************************************

void ShowBoard::on_tabWidget_currentChanged(int index)
{
    ui->grbSort->setTitle(ui->tabWidget->tabText(index));
    QString str;
    switch(index)
    {
    case 0:
        str = "稳定排序\n时间复杂度\n最好情况：n\n平均情况：n^2\n最坏情况：n^2";//冒泡
    break;
    case 1:
        str = "稳定排序\n时间复杂度\n最好情况：n\n平均情况：n^2\n最坏情况：n^2";//插入
    break;
    case 2:
        str = "不稳定排序\n时间复杂度\n最好情况：n^2\n平均情况：n^2\n最坏情况：n^2";//选择
    break;
    case 3:
        str = "不稳定排序\n时间复杂度\n最好情况：nlogn\n平均情况：nlogn\n最坏情况：nlogn";//堆
    break;
    case 4:
        str = "不稳定排序\n时间复杂度\n最好情况：nlogn\n平均情况：nlogn\n最坏情况：n^2";//快速
    break;
    case 5:
        str = "稳定排序\n时间复杂度\n最好情况：nlogn\n平均情况：nlogn\n最坏情况：nlogn";//归并
    break;
    case 6:
        str = "稳定排序\n时间复杂度\n最好情况：n\n平均情况：n\n最坏情况：n";//基数
    break;
    }
    ui->pteSort->setPlainText(str);
}

//速度
void ShowBoard::on_speed_Box_valueChanged(int arg1)
{
    arg1*=100;
    qDebug()<<"变化"<<arg1;
    m_bubbleThread->speed=arg1;
    m_insertThread->speed=arg1;
    m_selectThread->speed=arg1;
    m_heapThread->speed=arg1;
    m_quickThread->speed=arg1;
    m_mergeThread->speed=arg1;
    m_radixThread->speed=arg1;
}


