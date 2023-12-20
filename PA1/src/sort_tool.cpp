// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
// #include<stdlib.h>  //for random()
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int len = data.size();
    for (int j=1; j<len; j++){
        int key = data[j];
        int i = j-1;
        while(i>=0 && data[i]>key){
            data[i+1] = data[i];
            i--;
        }
        data[i+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
   
    if(low<high){
        int q;
        if(flag == 0){
            q = Partition(data, low, high);
        }else{
            q = RandomizedPartition(data, low, high);
        }
        QuickSortSubVector(data, low, q-1, flag);
        QuickSortSubVector(data, q+1, high, flag);
    }
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    return;
}

int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int i = rand()%(high-low+1)+low;
    int temp = data[i];
    data[i] = data[high];
    data[high] = temp;
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x = data[high]; //pivot
    int i = low - 1;
    for (int j=low; j<high; j++){
        if(data[j]<=x){
            i++;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    i++;
    int temp = data[i];
    data[i] = data[high];
    data[high] = temp;
    return i;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low >= high) return;
    int mid = (low + high)/2;
    MergeSortSubVector(data, low, mid);
    MergeSortSubVector(data, mid+1, high);
    Merge(data, low, mid, mid+1, high);
    return;
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int nL = middle1-low+1;
    int nH = high-middle2+1;
    vector<int> L(nL);
    vector<int> H(nH);
    for (int i = 0; i < nL; i++) {
        L[i] = data[low + i];
    }
    for (int i = 0; i < nH; i++) {
        H[i] = data[middle2 + i];
    }
    int i=0, j=0, k=low;
    while(i<nL && j < nH){
        if(L[i] <= H[j]){
            data[k] = L[i];
            i++;
        }else{
            data[k] = H[j];
            j++;
        }
        k++;
    }
    while(i<nL){
        data[k] = L[i];
        i++;
        k++;
    }
    while(j<nH){
        data[k] = H[j];
        j++;
        k++;
    }
    return;
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2 * root + 1;
    int r = 2 * (root + 1);
    int largest = root;
    if(l <= heapSize-1 && data[l] > data[root]){
        largest = l;
    }
    if(r <= heapSize-1 && data[r] > data[largest]){
        largest = r;
    }
    if(largest != root){
        swap(data[largest], data[root]);
        MaxHeapify(data, largest);
    }
    return;
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=(heapSize-1)/2; i>=0; i--){
        MaxHeapify(data, i);
    }
}
