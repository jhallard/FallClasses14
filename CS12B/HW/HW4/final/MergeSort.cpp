/**
*   @author - John Allard
*   @file   - MergeSort.cpp
*   @data   - 11/28/2014
*   @info   - This is the definition of a simple templated mergesort routine written in the c++ language (using very c-like syntax). This isn't a very 
*             robust or extensively-tested implementation, I just wrote it a few weeks back while studying for some technical interviews.
*
**/

#include <iostream>

template<class DataType>
DataType* merge(DataType*, int, DataType*, int);

template <class DataType>
DataType* merge_sort(DataType arr[], int n) {
    if(n < 2)
        return arr;
    int mid = n/2;
    DataType *left = merge_sort<DataType>(arr,mid);
    DataType *right = merge_sort<DataType>(arr+mid,n-mid);
    return merge(left, mid, right, n-mid);
}

template <class DataType>
DataType* merge(DataType left[], int size_left, DataType right[], int size_right) {
    int i = 0,j = 0;

    DataType* out_array = new DataType[size_left+size_right];

    while((i < size_left) && (j < size_right)) {
        if(left[i] >= right[j]) {
            out_array[i+j] = right[j];
            ++j;
        }
        else {
            out_array[i+j] = left[i];
            ++i;
        } 
    }
    while(i < size_left) {
        out_array[i+j] = left[i];
        i++;
    }
    while( j < size_right) {
        out_array[i+j] = right[j];
        j++;
    }
    return out_array;
}

