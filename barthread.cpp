#include "barthread.h"
#include <QBarSet>
#include <QVector>
#include <QList>


Algorithm* AlgorithmFactory::CreateAlgorithm(QString str,int speed=-1,RectanglePainter *RecP=nullptr)
{
    Algorithm *AlgorithmThread=NULL;
    if(RecP==nullptr) {
        if(str=="Bubble")
            AlgorithmThread= new bubbleBarThread();
        else if(str=="Insert")
            AlgorithmThread= new insertBarThread();
        else if(str=="Select")
            AlgorithmThread= new selectBarThread();
        else if(str=="Heap")
            AlgorithmThread= new heapBarThread();
        else if(str=="Quick")
            AlgorithmThread= new quickBarThread();
        else if(str=="Merge")
            AlgorithmThread= new mergeBarThread();
        else if(str=="Radix")
            AlgorithmThread= new radixBarThread();
    }
    else {
        if(str=="Bubble")
        {
            AlgorithmThread= new bubbleBarThread(speed,RecP);
        }
        else if(str=="Insert")
        {
            AlgorithmThread= new insertBarThread(speed,RecP);
        }
        else if(str=="Select")
        {
            AlgorithmThread= new selectBarThread(speed,RecP);
        }
        else if(str=="Heap")
        {
            AlgorithmThread= new heapBarThread(speed,RecP);
        }

        else if(str=="Quick")
        {
            AlgorithmThread= new quickBarThread(speed,RecP);
        }
        else if(str=="Merge")
        {
            AlgorithmThread= new mergeBarThread(speed,RecP);
        }
        else if(str=="Radix")
        {
            AlgorithmThread= new radixBarThread(speed,RecP);
        }
    }
    return AlgorithmThread;
}

//****************************************************************************
//*********************************冒泡排序************************************
//****************************************************************************

bubbleBarThread::bubbleBarThread(int speed,RectanglePainter *RecP)
{
    this->RecP = RecP;
    dataNum = RecP->count();
    this->speed=speed;
}

bubbleBarThread::bubbleBarThread()
{
    speed=1;
}

void bubbleBarThread::beginThread()
{
    m_paused = false;
}

void bubbleBarThread::pauseThread()
{
    m_paused = true;
}

void bubbleBarThread::stopThread()
{
    m_stop = true;
}

void bubbleBarThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop && !showEnd) // 事件主循环
    {
        // 冒泡排序循环
        for (int i = dataNum; i > 1 && !m_paused && !m_stop; i--)
        {
            for (int j = 0; j < i-1 && !m_paused && !m_stop; j++)
            {
                RecP->recolor(j,QColor(102,153,255));//浅蓝
                RecP->recolor(j+1,QColor(102,153,255));
                msleep(1*speed); // 停留1ms
                if (RecP->at(j) > RecP->at(j+1))
                {
                    RecP->swapRectangles(j,j+1);
                    swapNum += 3; // 交换次数+3
                }
                cmpNum += 1; // 比较次数+1
                msleep(0.5*speed); // 停留1ms
                RecP->recolor(j,QColor(56,196,108));//浅蓝
                RecP->recolor(j+1,QColor(56,196,108));
                //msleep(speed); // 停留1ms
            }
            RecP->recolor(i-1,QColor(255,204,204));
            //RecP->recolor(i-1,QColor(255,204,204));
            if (i == 2) //  下一次进入外层for循环i变为1，退出循环
            {
                RecP->recolor(0,QColor(255,204,204));
                showEnd = true;
                emit bubbleShowDone(cmpNum, swapNum); // 此时演示完毕，发送信号
            }

        }
    }
    quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}

//****************************************************************************
//*********************************插入排序************************************
//****************************************************************************

insertBarThread::insertBarThread(int speed,RectanglePainter *RecP=nullptr)
{
    this->RecP = RecP;
    dataNum = RecP->count();
    this->speed=speed;
}

insertBarThread::insertBarThread()
{
    speed=1;
}

void insertBarThread::beginThread()
{
    m_paused = false;
}

void insertBarThread::pauseThread()
{
    m_paused = true;
}

void insertBarThread::stopThread()
{
    m_stop = true;
}

void insertBarThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop && !showEnd) // 事件主循环
    {
        // 插入排序循环
        for (int i = 1; i < dataNum && !m_paused && !m_stop; i++)
        {
            RecP->recolor(0,QColor(102,153,255));//浅蓝
            int temp1 = RecP->at(i); // 当前元素
            int j;
            RecP->recolor(i,Qt::yellow);
            for ( j = i-1; j >= 0 && temp1 < RecP->at(j) && !m_paused && !m_stop; j--)
            {
                //RecP->recolor(j-1,Qt::blue);
                //int temp2 = RecP->at(j);

                //RecP->recolor(j,Qt::blue);
                RecP->recolor(j+1,Qt::yellow);
                //RecP->recolor(i,Qt::white);
                msleep(2*speed);
                RecP->swapRectangles(j+1,j);

                RecP->recolor(j+1,QColor(102,153,255));
                //RecP->recolor(j,Qt::red);
                //RecP->recolor(i,Qt::white);
                msleep(2*speed);
                //RecP->recolor(j-1,QColor(56,196,108));//恢复颜色
                cmpNum += 1;
                swapNum += 1;
            }
            RecP->recolor(j+1,QColor(102,153,255));
            swapNum += 1;
            if (i == dataNum-1) // 下一次进入外层for循环i变为dataNum，退出循环
            {
                RecP->recolor(i-1,QColor(102,153,255));
                RecP->recolor(i,QColor(102,153,255));

                showEnd = true;
                emit insertShowDone(cmpNum, swapNum); // 此时演示完毕，发送信号
            }
        }
    }
    quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}

//****************************************************************************
//*********************************选择排序************************************
//****************************************************************************

selectBarThread::selectBarThread(int speed,RectanglePainter *RecP=nullptr)
{
    this->RecP = RecP;
    dataNum = RecP->count();
    this->speed=speed;
}

selectBarThread::selectBarThread()
{
    speed=1;
}

void selectBarThread::beginThread()
{
    m_paused = false;
}

void selectBarThread::pauseThread()
{
    m_paused = true;
}

void selectBarThread::stopThread()
{
    m_stop = true;
}

void selectBarThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop && !showEnd) // 事件主循环
    {
        // 选择排序循环
        for (int i = dataNum; i > 1 && !m_paused && !m_stop; i--)
        {
            int indexOfMax = 0; // 找出数组a[0:size]中最大的元素的索引
            RecP->recolor(indexOfMax,Qt::red);
            for (int j = 1; j < i && !m_paused && !m_stop; j++)
            {
                RecP->recolor(j-1,Qt::yellow);
                msleep(2*speed);
                RecP->recolor(j-1,QColor(56,196,108));//恢复颜色
                if (RecP->at(indexOfMax) < RecP->at(j))
                {
                    RecP->recolor(indexOfMax,QColor(56,196,108));//恢复颜色
                    indexOfMax = j;
                    RecP->recolor(indexOfMax,Qt::red);
                }
                RecP->recolor(indexOfMax,Qt::red);
                //msleep(0.1*speed);

                /*
                if (RecP->at(indexOfMax) < RecP->at(j))
                {
                    indexOfMax = j;
                }
                cmpNum += 1;
                int temp1 = RecP->at(indexOfMax);
                int temp2 = RecP->at(i-1);

                RecP->replace(indexOfMax, temp2);
                //barSet->replace(indexOfMax, temp2);
                //msleep(2*speed);

                RecP->replace(i-1, temp1);
                //barSet->replace(i-1, temp1);
                msleep(2*speed);
                swapNum += 3;*/
            }
            //RecP->recolor(indexOfMax,QColor(56,196,108));
            RecP->swapRectangles(indexOfMax,i-1);
            msleep(2*speed);
            RecP->recolor(i-1,QColor(102,255,51));
            if (i == 2) // 下一次进入外层for循环i变为1，退出循环
            {
                RecP->recolor(0,QColor(102,255,51));
                showEnd = true;
                emit selectShowDone(cmpNum, swapNum); // 此时演示完毕，发送信号
            }
        }
    }
    quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}

//****************************************************************************
//*********************************堆排序************************************
//****************************************************************************

heapBarThread::heapBarThread(int speed,RectanglePainter *RecP=nullptr)
{
    this->RecP = RecP;
    dataNum = RecP->count();
    this->speed=speed;
}

heapBarThread::heapBarThread()
{
    speed=1;
}

void heapBarThread::beginThread()
{
    m_paused = false;
}

void heapBarThread::pauseThread()
{
    m_paused = true;
}

void heapBarThread::stopThread()
{
    m_stop = true;
}

void heapBarThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop && !showEnd) // 事件主循环
    {
        // 堆排序循环
        // 首先初始化一个非空大根堆，接着将堆顶元素不断的与“最后一个”元素交换，即完成排序
        // 在barSet中建堆，索引我会通过适当的转换将其变为[1:dataNum]
        // 但这仅仅是表示问题，实际还是从[0:dataNum-1]
        // 下面的算法根据《数据结构、算法与应用 C++语言描述》优先级队列 大根堆部分改编

        // 构建大根堆
        for (int root = dataNum/2; root >= 1  && !m_stop; root--)
        {

            if (!m_paused)
            {
                int rootElement = RecP->at(root-1);
                int child = 2*root;
                while (child <= dataNum && !m_stop)
                {
                    if (!m_paused)
                    {
                        if (child < dataNum && RecP->at(child-1) < RecP->at(child))
                            child++;
                        if (rootElement >= RecP->at(child-1))
                            break;

                        RecP->replace(child/2-1, RecP->at(child-1));
                        //barSet->replace(child/2-1, barSet->at(child-1));
                        msleep(2*speed);
                        child *= 2;
                    }
                }
                RecP->replace(child/2-1, rootElement);
                //barSet->replace(child/2-1, rootElement);
                msleep(2*speed);
            }
            else
                root++;
        }

        // 从大根堆中删除元素
        for (int i = 0; i < dataNum && !m_stop; i++)
        {
            if (!m_paused)
            {
                int first = RecP->at(0);
                int last = RecP->at(dataNum-i-1);
                RecP->replace(0, last);
                //barSet->replace(0, last);
                msleep(2*speed);

                RecP->replace(dataNum-i-1, first);
                //barSet->replace(dataNum-i-1, first);
                msleep(2*speed);
                int currentNode = 1;
                int child = 2;
                while (child <= dataNum-i-1 && !m_stop)
                {
                    if (!m_paused)
                    {
                        if (child < dataNum-i-1 && RecP->at(child-1) < RecP->at(child))
                                child++;
                        if (last >= RecP->at(child-1))
                                break;
                        RecP->replace(currentNode-1, RecP->at(child-1));
                        //barSet->replace(currentNode-1, RecP->at(child-1));
                        msleep(2*speed);
                        currentNode = child;
                        child *= 2;
                    }
                }
                RecP->replace(currentNode-1, last);
                //barSet->replace(currentNode-1, last);
                msleep(2*speed);
                if (i == dataNum-1)
                {
                    showEnd = true;
                    emit heapShowDone(cmpNum, swapNum);
                }
            }
            else
                i--;
        }
    }
    quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}

//****************************************************************************
//*********************************快速排序************************************
//****************************************************************************

quickBarThread::quickBarThread(int speed, RectanglePainter *RecP)
{
   this->RecP = RecP;
   dataNum = RecP->count();
   this->speed=speed;
   max = 0;
   for (int i = 1; i < dataNum; i++)
   {
       // 获取最大元素的索引
       if (RecP->at(i) > RecP->at(max))
           max = i;
   }
}

quickBarThread::quickBarThread()
{
    speed=1;
}

void quickBarThread::beginThread()
{
    m_paused = false;
}

void quickBarThread::pauseThread()
{
    m_paused = true;
}

void quickBarThread::stopThread()
{
    m_stop = true;
}

void quickBarThread::run()
{
   m_stop = false; // 启动线程时令 m_stop = false
   while (!m_stop && !showEnd) // 事件主循环
   {
       // 快速排序循环
       // 把最大的元素移到数组最右端
       if (!m_paused)
       {
           msleep(2*speed);
           RecP->swapRectangles(dataNum-1,max);
           RecP->recolor(max, Qt::red);
           RecP->recolor(dataNum-1, Qt::blue);
           msleep(2*speed);
           quickSort(0, dataNum-2); // 函数名相同，参数不同
           showEnd = true;
           //RecP->recolor(-1, Qt::transparent);
           emit quickShowDone(cmpNum, swapNum);
       }
   }
   quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}

void quickBarThread::quickSort(int leftEnd, int rightEnd)
{
   if (leftEnd >= rightEnd)
       return;
   int leftCursor = leftEnd,
       rightCursor = rightEnd+1;
   int pivot = RecP->at(leftEnd);
    while (true && !m_stop)
   {
       if (!m_paused)
       {
           do
           {
               if (!m_paused)
               {
                   leftCursor++;
                   RecP->recolor(leftCursor, Qt::green);
                   cmpNum++;
                   msleep(2*speed);
                   RecP->recolor(leftCursor, Qt::blue);
               }
           } while (RecP->at(leftCursor) < pivot && !m_stop);
            do
           {
               if (!m_paused)
               {
                   rightCursor--;
                   RecP->recolor(rightCursor, Qt::green);
                   cmpNum++;
                   msleep(2*speed);
                   RecP->recolor(rightCursor, Qt::blue);
               }
           } while (RecP->at(rightCursor) > pivot && !m_stop);
            if (leftCursor >= rightCursor)
               break;
            RecP->swapRectangles(leftCursor,rightCursor);
           RecP->recolor(leftCursor, Qt::yellow);
           RecP->recolor(rightCursor, Qt::yellow);
           msleep(2*speed);
           cmpNum++;
           swapNum++;
           RecP->recolor(leftCursor, Qt::blue);
           RecP->recolor(rightCursor, Qt::blue);
       }
    }
    RecP->recolor(leftEnd, Qt::red);
   RecP->recolor(rightCursor, Qt::red);
   msleep(2*speed);
   RecP->replace(leftEnd, RecP->at(rightCursor));
   RecP->replace(rightCursor, pivot);
   RecP->recolor(leftEnd, Qt::white);
   RecP->recolor(rightCursor, Qt::white);
   msleep(2*speed);
   quickSort(leftEnd, rightCursor-1);
   quickSort(rightCursor+1, rightEnd);
}

//****************************************************************************
//*********************************归并排序************************************
//****************************************************************************

mergeBarThread::mergeBarThread(int speed,RectanglePainter *RecP=nullptr)
{
    this->RecP = RecP;
    dataNum = RecP->count();
    this->speed=speed;
    data.resize(dataNum);
    for (int i = 0; i < dataNum; i++)
        data[i] = RecP->at(i);
}
 mergeBarThread::mergeBarThread()
{
    speed=1;
}
 void mergeBarThread::beginThread()
{
    m_paused = false;
}
 void mergeBarThread::pauseThread()
{
    m_paused = true;
}
 void mergeBarThread::stopThread()
{
    m_stop = true;
}
 void mergeBarThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop && !showEnd) // 事件主循环
    {
        if (!m_paused)
        {
            mergeSort(0, dataNum-1);
            for(int i = 0; i < dataNum && !m_paused && !m_stop; i++){
                RecP->recolor(i, Qt::green); // 变成绿色
                RecP->replace(i, data[i]);   // 重新绘制
                msleep(2*speed);
            }
             showEnd = true;
            emit mergeShowDone(cmpNum, swapNum);
        }
    }
    quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}
 void mergeBarThread::mergeSort(int l, int r)
{
    if(l < r && !m_stop)
    {
        int m = l + (r-l)/2;
        mergeSort(l, m);
        mergeSort(m+1, r);
        merge(l, m, r);
    }
}
 //对于俩个被分开的两个部分进行整个归并排序
void mergeBarThread::merge(int l, int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1],R[n2];
     for(int i = 0; i < n1; i++)
        L[i] = data[l+i];       //存数组l到m之间的数据
    for(int i = 0; i < n2; i++)
        R[i] = data[m + 1 + i]; //存数组m+1到r之间的数据
    int k = l, i = 0, j = 0;
     while(i < n1 && j < n2 && !m_stop)
    {   //将两个部分进行排序
        if (!m_paused)
        {
            cmpNum++; // 比较次数加1
            if(L[i] <= R[j]){
                data[k] = L[i];
                i++;
            }
            else{
                data[k] = R[j];
                j++;
            }
            k++;
            RecP->recolor(k-1, Qt::blue); // 变成蓝色
            RecP->replace(k-1, data[k-1]); // 重新绘制
            msleep(2*speed);
        }
    }
    while(i < n1 && !m_paused && !m_stop)
    {   //将L中剩余的值放入data中
        if (!m_paused)
        {
            data[k] = L[i];
            i++;
            k++;
            RecP->recolor(k-1, Qt::blue); // 变成蓝色
            RecP->replace(k-1, data[k-1]); // 重新绘制
            msleep(2*speed);
        }
    }
    while(j < n2 && !m_paused && !m_stop)
    {
        //将R中剩余的值放入data中
        if (!m_paused)
        {
            data[k] = R[j];
            j++;
            k++;
            RecP->recolor(k-1, Qt::blue); // 变成蓝色
            RecP->replace(k-1, data[k-1]); // 重新绘制
            msleep(2*speed);
        }
    }
     // 进行交换操作，变为红色，并交换2个矩形位置
    for(int i = l; i <= r && !m_paused && !m_stop; i++){
        RecP->recolor(i, Qt::red); // 变成红色
        RecP->swapRectangles(i, k-i-1+l); // 交换
        swapNum++; // 交换次数加1
        msleep(2*speed);
    }
}

//****************************************************************************
//*********************************基数排序************************************
//****************************************************************************

radixBarThread::radixBarThread(int speed,RectanglePainter *RecP=nullptr)
{
    this->RecP = RecP;
    dataNum = RecP->count();
    this->speed=speed;
    data.resize(dataNum);
    max = 0; //寻找最大值，由此得知所需的位数
    for (int i = 0; i < dataNum; i++)
    {
        if (max < RecP->at(i))
            max = RecP->at(i);
        data[i] = RecP->at(i);
    }
}

radixBarThread::radixBarThread()
{
    speed=1;
}

void radixBarThread::beginThread()
{
    m_paused = false;
}

void radixBarThread::pauseThread()
{
    m_paused = true;
}

void radixBarThread::stopThread()
{
    m_stop = true;
}

void radixBarThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop && !showEnd) // 事件主循环
    {
        if (!m_paused)
            {
                // 插入排序循环
                for (int exp = 1; max/exp > 0 && !m_stop; exp *= 10)
                {
                    if (!m_paused)
                    {
                        int output[dataNum];
                        int count[10] = {0};
                        for(int i = 0; i < dataNum; i++)
                        {
                            // 得到每个位数上的数字的个数
                            count[(data[i]/exp)%10]++;  // 例如在{1,2,11,13,4}个位为一的有2个，个位为2的有1，...
                        }
                        // 然后将所得到的所有位数进行累加求和，方便判断是在output[]的那个位子上
                        for(int i = 1; i < 10 ; i++)
                        {
                            count[i] += count[i-1];
                        }
                        // 读取过程中，高亮颜色
                        QColor readColor = QColor("lime");
                        // 写入过程中，高亮颜色
                        QColor writeColor = QColor("red");
                        for(int i = dataNum - 1; i >= 0 && !m_stop; i--)
                        {
                            if (!m_paused)
                            {
                                // 更改读取颜色
                                RecP->recolor(i, readColor);
                                msleep(2*speed);
                                 output[count[(data[i]/exp)%10] - 1]= data[i];
                                count[(data[i]/exp)%10] --;
                                 RecP->replace(i, data[i]);
                                // 更改写入颜色
                                RecP->recolor(i, writeColor);
                                msleep(2*speed);
                                 // 还原颜色
                                RecP->recolor(i, QColor("blue"));
                            }
                            else
                                i++;
                        }
                        for(int i = 0; i < dataNum && !m_stop; i++)
                        {
                            if (!m_paused)
                            {
                                data[i] = output[i];    // 将此趟排序好的数据赋值回去
                                 // 更改颜色为读取颜色
                                RecP->recolor(i, readColor);
                                msleep(2*speed);
                                 RecP->replace(i, data[i]);
                                msleep(2*speed);
                                 // 更改颜色为写入颜色
                                RecP->recolor(i, writeColor);
                                msleep(2*speed);
                                 // 还原颜色
                                RecP->recolor(i, QColor("blue"));
                            }
                            else
                                i--;
                        }
                    }
                    else
                        exp /= 10;
                }
                 showEnd = true;
                emit radixShowDone(cmpNum, swapNum);
            }
    }
    quit(); // m_stop为true（按终止键）或者showEnd为true（演示完毕），退出线程的事件循环
}

