#ifndef ALLSORTFUNCTIONS_H
#define ALLSORTFUNCTIONS_H

/* 该文件处理所有排序算法类
 * 分别为：冒泡排序、插入排序、选择排序、箱子排序、堆排序、快速排序、归并排序
 */

void swap(int& x, int& y); // 交换两个整数，公共函数

//*************************冒泡排序开始*************************//
class BubbleSort
{
public:
    BubbleSort(int size, int* arr);

    void bubbleSort(); // 非及时终止的冒泡排序
    void bubbleSort_Stop(); // 及时终止的冒泡排序


private:
    int *arr; // 数组
    int size; // 数组的大小
};
//*************************冒泡排序结束*************************//

//*************************插入排序开始*************************//
class InsertSort
{
public:
    InsertSort();
};
//*************************插入排序结束*************************//

#endif // ALLSORTFUNCTIONS_H
