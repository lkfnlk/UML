#ifndef BARTHREAD_H
#define BARTHREAD_H
#include"rectanglepainter.h"
#include <QThread>
#include <QBarSet>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE




class Algorithm:public QThread
{
public:
    int speed;
    virtual void beginThread()=0; // 开始线程
    virtual void pauseThread()=0; // 暂停线程
    virtual void stopThread()=0; // 终止线程
};
class AlgorithmFactory
{
public:
   AlgorithmFactory();
   Algorithm* CreateAlgorithm(QString str,int speed,RectanglePainter *RecP);
};

//************************冒泡排序************************

class bubbleBarThread: public Algorithm
{
    Q_OBJECT

public:
    bubbleBarThread(int speed,RectanglePainter *RecP);
    bubbleBarThread();

    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QList<int> dataList; // 用于存储数据
    QVector<int> dataList;
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;

    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数
    int cmpNum; // 比较的次数

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void bubbleShowDone(int cmpNum, int swapNum);
};

//************************插入排序************************

class insertBarThread: public Algorithm
{
    Q_OBJECT

public:
    insertBarThread(int speed,RectanglePainter *RecP);
    insertBarThread();
    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;
    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数，事实上这里的交换次数应该叫做“移动次数”
    int cmpNum; // 比较的次数

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void insertShowDone(int cmpNum, int swapNum);
};

//************************选择排序************************

class selectBarThread: public Algorithm
{
    Q_OBJECT

public:
    selectBarThread(int speed,RectanglePainter *RecP);
    selectBarThread();
    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;
    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数
    int cmpNum; // 比较的次数

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void selectShowDone(int cmpNum, int swapNum);
};


//************************堆排序************************

class heapBarThread: public Algorithm
{
    Q_OBJECT

public:
    heapBarThread(int speed,RectanglePainter *RecP);
    heapBarThread();
    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;
    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数
    int cmpNum; // 比较的次数

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void heapShowDone(int cmpNum, int swapNum);
};

//************************快速排序************************

class quickBarThread: public Algorithm
{
    Q_OBJECT

public:
    quickBarThread(int speed,RectanglePainter *RecP);
    quickBarThread();
    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;
    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数
    int cmpNum; // 比较的次数
    int max; // 最大元素的索引

    void quickSort(int leftEnd, int rightEnd); // 快速排序

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void quickShowDone(int cmpNum, int swapNum);
};

//************************归并排序************************

class mergeBarThread: public Algorithm
{
    Q_OBJECT

public:
    mergeBarThread(int speed,RectanglePainter *RecP);
    mergeBarThread();
    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;
    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数
    int cmpNum; // 比较的次数

    QVector<int> data;

    void mergeSort(int l, int r); // 将数组分为尽可能相等的俩个部分
    void merge(int l, int m, int r); // 对于两个被分开的两个部分进行整个归并排序

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void mergeShowDone(int cmpNum, int swapNum);
};

//************************基数排序************************

class radixBarThread: public Algorithm
{
    Q_OBJECT

public:
    radixBarThread(int speed,RectanglePainter *RecP);
    radixBarThread();
    int speed;

    void beginThread()override; // 开始线程
    void pauseThread()override; // 暂停线程
    void stopThread()override; // 终止线程

    // QThread interface
protected:
    void run() override; // 线程任务

private:
    //QBarSet *barSet; // 柱状图数据
    RectanglePainter *RecP;
    bool m_paused = true; // 暂停
    bool m_stop = false; // 停止
    bool showEnd = false; // 演示结束为true
    int dataNum; // barSet->count() 数据数量
    int swapNum; // 交换的次数
    int cmpNum; // 比较的次数
    int max; // 最大值

    QVector<int> data;

signals:
    // 这个信号当且仅当动态演示完毕后发射
    // 目的是，主线程在收到此信号后，将“暂停~”和“终止~”按钮，设置为不可用，当前状态的QLabel更新
    // 主线程获得比较次数和交换次数
    void radixShowDone(int cmpNum, int swapNum);
};

#endif // BARTHREAD_H
