#ifndef SHOWBOARD_H
#define SHOWBOARD_H

#include "barthread.h"
#include <QMainWindow>
#include <QList>
#include <QtCharts>
#include<qstring.h>
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class ShowBoard; }
QT_END_NAMESPACE



class BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
     QString m_curStyle;
public:
    BuildBarChart(QVector<int> dataList,QString curStyle);
    void buildBarChart(QChart *chart, QBarSet *barSet);
    virtual QChart* iniBarChart()=0;
};

class BarChartFactory
{
public:
    BarChartFactory();
    static BuildBarChart* CreateBarChart(QString str,QVector<int> dataList,QString curStyle);
};

class BuildBarChart_Bubble:public BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
public:
     BuildBarChart_Bubble(QVector<int> dataList,QString curStyle);
     QChart* iniBarChart();
};


class BuildBarChart_Insert:public BuildBarChart
{
private:
    QVector<int> m_dataList; // 用于存储数据
public:
    BuildBarChart_Insert(QVector<int> dataList,QString curStyle);
    QChart* iniBarChart();
};

class BuildBarChart_Select:public BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
public:
    BuildBarChart_Select(QVector<int> dataList,QString curStyle);
    QChart* iniBarChart();
};
class BuildBarChart_Quick:public BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
public:
    BuildBarChart_Quick(QVector<int> dataList,QString curStyle);
    QChart* iniBarChart();
};
class BuildBarChart_Merge:public BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
public:
    BuildBarChart_Merge(QVector<int> dataList,QString curStyle);
    QChart* iniBarChart();
};
class BuildBarChart_Heap:public BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
public:
    BuildBarChart_Heap(QVector<int> dataList,QString curStyle);
    QChart* iniBarChart();
};
class BuildBarChart_Radix:public BuildBarChart
{
private:
     QVector<int> m_dataList; // 用于存储数据
public:
    BuildBarChart_Radix(QVector<int> dataList,QString curStyle);
    QChart* iniBarChart();
};

class ShowBoard : public QMainWindow
{
    Q_OBJECT

public:
    ShowBoard(QWidget *parent = nullptr);
    ~ShowBoard();

protected:
    void closeEvent(QCloseEvent *event);


private:
    int m_dataNum; // 数据总数
    int m_minNum; // 最小值
    int m_maxNum; // 最大值
    double m_avgNum; // 平均值
    double m_varNum; // 方差

//    QVector<int> m_swapNum;
//    QVector<int> m_cmpNum;
    int m_swapNum[7]={0};
    int m_cmpNum[7]={0};


//    QVector<QVector<int>> m_swapNums; // 记录交换次数
//    QVector<QVector<int>> m_cmpNums; // 记录比较次数

    QVector<int> m_dataList; // 用于存储数据

    QString m_curStyle; // 当前的界面主题

    // 7个排序的动态演示的线程，每个线程都负责自己的动态演示
    Algorithm *m_bubbleThread;
    //bubbleBarThread *m_bubbleThread;
    insertBarThread *m_insertThread;
    selectBarThread *m_selectThread;
    heapBarThread *m_heapThread;
    quickBarThread *m_quickThread;
    mergeBarThread *m_mergeThread;
    radixBarThread *m_radixThread;

    //7个排序矩形图
    RectanglePainter *bulle_RecP;
    RectanglePainter *insert_RecP;
    RectanglePainter *select_RecP;
    RectanglePainter *heap_RecP;
    RectanglePainter *quick_RecP;
    RectanglePainter *mergeBar_RecP;
    RectanglePainter *radix_RecP;

    AlgorithmFactory *m_algorithmFactory;

    BarChartFactory *m_barChartFactory;
    BuildBarChart *m_bubbleBarChart;
    BuildBarChart *m_insertBarChart;
    BuildBarChart *m_selectBarChart;
    BuildBarChart *m_mergeBarChart;
    BuildBarChart *m_heapBarChart;
    BuildBarChart *m_radixBarChart;
    BuildBarChart *m_quickBarChart;



    //构建柱状图
    void buildBarChart_Bubble();
    void buildBarChart_Insert();
    void buildBarChart_Select();
    void buildBarChart_Heap();
    void buildBarChart_Quick();
    void buildBarChart_Merge();
    void buildBarChart_Radix();

    // 处理ChartVieWPieCmp
    void iniPieChart_Cmp(); // 初始化比较次数饼图
    void buildPieChart_Cmp(); // 构建比较次数饼图

    // 处理ChartViewPieSwap
    void iniPieChart_Swap(); // 初始化交换次数饼图
    void buildPieChart_Swap(); // 构建交换次数饼图

private slots:


    //************************冒泡排序************************

    void on_btnBubbleStart_clicked(); // 冒泡排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnBubblePause_clicked(); // 冒泡排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnBubbleStop_clicked(); // 冒泡排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnBubbleInit_clicked(); // 冒泡排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_bubbleShowDone(int cmpNum, int swapNum); // 响应冒泡排序演示线程发送的演示完毕的信号

    //************************插入排序************************

    void on_btnInsertStart_clicked(); // 插入排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnInsertPause_clicked(); // 插入排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnInsertStop_clicked(); // 插入排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnInsertInit_clicked(); // 插入排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_insertShowDone(int cmpNum, int swapNum); // 响应插入排序演示线程发送的演示完毕的信号

    //************************选择排序************************

    void on_btnSelectStart_clicked(); // 选择排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnSelectPause_clicked(); // 选择排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnSelectStop_clicked(); // 选择排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnSelectInit_clicked(); // 选择排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_selectShowDone(int cmpNum, int swapNum); // 响应选择排序演示线程发送的演示完毕的信号


    //************************堆排序************************

    void on_btnHeapStart_clicked(); // 堆排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnHeapPause_clicked(); // 堆排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnHeapStop_clicked(); // 堆排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnHeapInit_clicked(); // 堆排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_heapShowDone(int cmpNum, int swapNum); // 响应堆排序演示线程发送的演示完毕的信号

    //************************快速排序************************

    void on_btnQuickStart_clicked(); // 快速排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnQuickPause_clicked(); // 快速排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnQuickStop_clicked(); // 快速排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnQuickInit_clicked(); // 快速排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_quickShowDone(int cmpNum, int swapNum); // 响应快速排序演示线程发送的演示完毕的信号

    //************************归并排序************************

    void on_btnMergeStart_clicked(); // 归并排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnMergePause_clicked(); // 归并排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnMergeStop_clicked(); // 归并排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnMergeInit_clicked(); // 归并排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_mergeShowDone(int cmpNum, int swapNum); // 响应归并排序演示线程发送的演示完毕的信号

    //************************基数排序************************

    void on_btnRadixStart_clicked(); // 基数排序“开始动态演示”按钮按下后的槽函数，开始动态演示

    void on_btnRadixPause_clicked(); // 基数排序“暂停动态演示”按钮按下后的槽函数，暂停动态演示

    void on_btnRadixStop_clicked(); // 基数排序“终止动态演示”按钮按下后的槽函数，终止动态演示

    void on_btnRadixInit_clicked(); // 基数排序“重新初始化”按钮按下后的槽函数，初始化动态演示

    void on_radixShowDone(int cmpNum, int swapNum); // 响应基数排序演示线程发送的演示完毕的信号

    //************************饼图************************

    void on_btnCmp_clicked(); // 比较次数

    void on_btnSwap_clicked(); // 交换次数

    //************************排序介绍************************
    void on_tabWidget_currentChanged(int index);

    void on_speed_Box_valueChanged(int arg1);

    void on_btnDataProdeuce_clicked();

private:
    Ui::ShowBoard *ui;
};
#endif // SHOWBOARD_H
