#pragma once
#include "Tree.h"

void qsort(struct Node* a, int begin, int end);
void Swap(struct Node* a, struct Node* b);

//对子结点数组按结点的score排序
void qsort(struct Node* a, int begin, int end)
{
    //一个元素或没有元素时,递归结束
    if (begin >= end) {
        return;
    }
		
    int left = begin;		//递归区间起始
    int right = end;		//递归区间末尾
    int keyi = left;    //keyi == key_index == key的下标
 
    while (left < right) {
        while (left < right && a[right].score >= a[keyi].score) { //要找小于key的,大于等于都要走,不然执行不了函数体(下标移动),导致死循环
            right--;  //不能合并,要保证下标指向的是找到的那个值
        }
        while (left < right && a[left].score <= a[keyi].score) {
            left++;
        }
        Swap(&(a[left]), &(a[right]));
    }
 
    Swap(&(a[left]), &(a[keyi]));
    keyi = left;
 
    //区间划分成: [begin,keyi-1]  keyi  [keyi+1,end]
    qsort(a, begin, keyi - 1);
    qsort(a, keyi + 1, end);
}

void Swap(struct Node* a, struct Node* b)
{
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}