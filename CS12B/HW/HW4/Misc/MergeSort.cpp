#include <iostream>

template<class T>
T* merge(T*, int, T*, int);

template <class T>
T* merge_sort(T arr[], int n) {
    if(n < 2){return arr;}
    int mid = n/2;
    T *arr1 = merge_sort<T>(arr,mid);
    T *arr2 = merge_sort<T>(arr+mid,n-mid);
    return merge(arr1, mid, arr2, n-mid);
}

template <class T>
T* merge(T arr1[], int size1, T arr2[], int size2) {
    int i = 0,j = 0;

    T* out_array = new T[size1+size2];

    while((i < size1) && (j < size2)) {
        if(arr1[i] >= arr2[j]) {
            out_array[i+j] = arr2[j];
            ++j;
        }
        else {
            out_array[i+j] = arr1[i];
            ++i;
        } 
    }
    while(i < size1) {
        //copy the reminder
        out_array[i+j] = arr1[i];
        i++;
    }
    while( j < size2) {
        out_array[i+j] = arr2[j];
        j++;
    }
    return out_array;
}

