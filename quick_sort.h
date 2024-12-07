#pragma once
#include "Tree.h"

void qsort(struct Node* a, int begin, int end);
void Swap(struct Node* a, struct Node* b);

//���ӽ�����鰴����score����
void qsort(struct Node* a, int begin, int end)
{
    //һ��Ԫ�ػ�û��Ԫ��ʱ,�ݹ����
    if (begin >= end) {
        return;
    }
		
    int left = begin;		//�ݹ�������ʼ
    int right = end;		//�ݹ�����ĩβ
    int keyi = left;    //keyi == key_index == key���±�
 
    while (left < right) {
        while (left < right && a[right].score >= a[keyi].score) { //Ҫ��С��key��,���ڵ��ڶ�Ҫ��,��Ȼִ�в��˺�����(�±��ƶ�),������ѭ��
            right--;  //���ܺϲ�,Ҫ��֤�±�ָ������ҵ����Ǹ�ֵ
        }
        while (left < right && a[left].score <= a[keyi].score) {
            left++;
        }
        Swap(&(a[left]), &(a[right]));
    }
 
    Swap(&(a[left]), &(a[keyi]));
    keyi = left;
 
    //���仮�ֳ�: [begin,keyi-1]  keyi  [keyi+1,end]
    qsort(a, begin, keyi - 1);
    qsort(a, keyi + 1, end);
}

void Swap(struct Node* a, struct Node* b)
{
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}