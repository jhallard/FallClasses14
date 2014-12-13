/*
*   @Author John Allard (template provded by Prof. Whitehead)
*   @File   heap.c
*   @Purpose This is a simple C implementation of a heap data structure. Our job as students is to finish and debug the implementation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/** Heap type **/

/* Heaps contain size information which is updated as elements are
   inserted and deleted. maxSize is the size of the array, which is
   allocated dynamically when the heap is created.
*/
struct heap {
    int size;
    int maxSize;
    int *array;
};
typedef struct heap heap;

/** Helper functions **/

int parent(int x) {
    return (x - 1) / 2;
}

int lchild(int x) {
    return 2 * x + 1;
}

int rchild(int x) {
    return 2 * x + 2;
}

/** Heap operations **/

/*  Print heap for debugging */
void printHeap(heap *aHeap) {
    assert(aHeap != NULL);
    for(int i = 0; i < aHeap->size; i++) {
        printf("%d ", aHeap->array[i]);
    }
    printf("\n");
}

/*  Create new heap dynamically
    Returns pointer to new heap object.
*/
heap *newHeap(int maxSize) {
    assert(maxSize > 0);
    heap *tmp = malloc(sizeof(heap));
    tmp->size = 0;
    tmp->maxSize = maxSize;
    tmp->array = malloc(sizeof(int) * tmp->maxSize);
    return tmp;
}

/*  Delete previously created heap
*/
void deleteHeap(heap *aHeap) {
    assert(aHeap != NULL);
    assert(aHeap->array != NULL);
    free(aHeap->array);
    free(aHeap);
}

/*  Check if heap is full */
bool isFullHeap(heap *aHeap) {
    assert(aHeap != NULL);
    return (aHeap->size == aHeap->maxSize);
}

/*  Check if heap is empty */
bool isEmptyHeap(heap *aHeap) {
    // assert(aHeap != NULL);
    if(aHeap == NULL)
        return false;
    return !aHeap->size;
}

void swap(int* x, int*y) {
    int t = *x;
    *x = *y;
    *y = t;
}

/*  Insert number into heap
    Unspecified behavior if heap is full before insert
*/
void insertHeap(heap *aHeap, int value) {
    assert(aHeap != NULL);
    assert(aHeap->size < aHeap->maxSize);
    aHeap->array[aHeap->size++] = value;
    int temp1 = aHeap->size-1;
    int temp2 = (temp1-1)/2;

    while(aHeap->array[temp1] > aHeap->array[temp2]) {
        swap((aHeap->array+temp1), (aHeap->array+temp2));
        temp1 = temp2;
        temp2 = (temp2-1)/2;
    }
}


/*  Remove number from heap
    Unspecified behavior if heap is empty
*/
int removeHeap(heap *aHeap) {
    assert(aHeap != NULL);
    assert(aHeap->size > 0);
    aHeap->size--;
    int retVal = aHeap->array[0];
    aHeap->array[0] = aHeap->array[aHeap->size];
    // Trickle down
    int position = 0;
    while (true) {
        int left = lchild(position);
        int right = rchild(position);
        int largest = position;
        if (left < aHeap->size && aHeap->array[left] > aHeap->array[largest]) {
            largest = left;
        }
        if (right < aHeap->size && aHeap->array[right] > aHeap->array[largest]) {
            largest = right;
        }
        if (largest == position) {
            break;
        } else {
            int tmp = aHeap->array[position];
            aHeap->array[position] = aHeap->array[largest];
            aHeap->array[largest] = tmp;
            position = largest;
        }
    }
    return retVal;
}

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc < 2) {
        printf("Wrong arguments\n");
        return EXIT_FAILURE;
    }
    int maxnum = atoi(argv[1]);
    char *filename = argv[2];

    // Create new heap
    heap *theHeap = newHeap(maxnum);

    // Read lines of file
    FILE *fp = fopen(filename, "rt");
    while(!feof(fp)) {
        char buffer[256];
        fgets(buffer, 256, fp);
        if (feof(fp)) break;
        int value = atoi(buffer);
        insertHeap(theHeap, value);
        if (isFullHeap(theHeap)) {
            removeHeap(theHeap);
        }
    }

    // Show contents
    while(!isEmptyHeap(theHeap)) {
        int value = removeHeap(theHeap);
        printf("%d\n", value);
    }
    
    // Delete heap
    deleteHeap(theHeap);

    return EXIT_SUCCESS;
}
