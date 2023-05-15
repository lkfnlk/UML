#include "allsortfunctions.h"


// 公共函数
void swap(int &x, int &y)
{
    // 交换整数x和y
    int temp = x;
    x = y;
    y = temp;
}

//*************************冒泡排序开始*************************//
BubbleSort::BubbleSort(int size, int *arr)
{
    this->arr = arr;
    this->size = size;
}

void BubbleSort::bubbleSort()
{
    for (int i = size; i > 1; i--)
        // 把arr[0, i-1]中最大的元素移动到arr[i-1]
        for (int j = 0; j < i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

void BubbleSort::bubbleSort_Stop()
{
    for (int i = size; i > 1; i--)
        {
            bool swapped = false; // 尚未发生交换
            // 把arr[0, i-1]中最大的元素移动到arr[i-1]
            for (int j = 0; j < i-1; j++)
                if (arr[j] > arr[j+1])
                {
                    swap(arr[j], arr[j+1]);
                    swapped=true; // 发生了交换
                }
            if (!swapped)
                break; // 没发生交换，说明全部有序
        }
}
//*************************冒泡排序结束*************************//

