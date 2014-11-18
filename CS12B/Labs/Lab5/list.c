//  file:     list.c
//  Author  - John Allard
//  CruzID  - jhallard
//  Class   - CS12M, Lab #5
//  Date    - Nov 16th, 2014
//  Prupose - This file represents a linked list, it was buggy when given to us and our assignment was to rid it of bugs.

#include <stdio.h>
#include <stdlib.h>

// A node in a singly-linked list
struct node {
    int value;
    struct node *next;
};

// Head of the linked list
struct node *head;

// Insert a value into linked list
void list_insert(int v) {
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->value = v;
    n->next = head;
    head = n;
}

// Insert two values at once into linked list
void list_insert2(int a, int b) {

    list_insert(b);
    list_insert(a);
}

// Remove an element from linked list
void list_remove(int v) {
    struct node *n = head;

    while(n && n->next) {

        if(n->next->value == v) {
            struct node * temp = n->next;
            n->next = n->next->next;
            free(temp);
        }
        n = n->next;
    }
}

// Print out all values in linked list
void list_printall(void) {
    struct node *p = head;
    int n = 0;
    while(p) {
        printf("%d ", p->value);
        p=p->next;
        n++;
    }
    printf("\n");
}

// Deallocate all memory used in linked list

// BUGS list_destroy function, lines 57-59, it only destroyed the head ptr, it needs to go through the entirety of the list and delete all pointers.
void list_destroy(void) {

    struct node * temp = head;

    while(temp) {
        struct node * temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
}

int main(int argc, char *argv[]) {
    printf("Test linked lists\n");
    list_printall(); // Should print nothing
    list_insert(42);
    list_insert2(17, 10);
    list_insert(18);
    list_remove(10);
    list_printall(); // Should print 18 17 42
    // Cleanup memory
    list_destroy();
    return 0;
}
