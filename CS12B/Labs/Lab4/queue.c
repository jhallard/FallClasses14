#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

#define MAXSIZE 100

int tests_run = 0; // keep track of number of unit tests run

typedef enum q_status {
    /* Enumerated status codes for queue operations */
    q_success = 0,
    q_failure
} q_status;

/**** Private variables for queue ****/
int *front = NULL;
int *back = NULL;
int queue[100] = {0};
int num_items;

/**** Functions on queues ****/

q_status q_init(void) {
    /* Initialize the queue */
    num_items = 0;
    front = &queue[0];
    back = &queue[0];
    return q_success;//q_failure;
}

q_status q_insert(int value) {
    if(num_items >= 100)
        return q_failure;

    *back = value;

    if(back == &queue[99]){
        back = &queue[0];
        num_items++;
    }
    else{
        ++back;
        num_items++;
    }
    return q_success;
    
}

q_status q_remove(int *value) {
    if(num_items == 0 || value == NULL)
        return q_failure;

    *value = *front;

    if(front == &queue[99])
        front = &queue[0];
    else
        front++;

    num_items--;
    return q_success;
}

q_status q_peek(int *value) {

    if(num_items == 0 || value == NULL)
        return q_failure;

    *value = *front;
    return q_success;
}

q_status q_destroy(void) {
    front = back = NULL;
    num_items = 0;

    return q_success;
}

int q_is_empty(void){
    return (num_items == 0)? 1 : 0;
}

/**** Unit tests ****/

char * test_lifecycle(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_one_insert(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(7) == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_one_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(16) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 16);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_two_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("insert", q_insert(91) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 91);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_multi_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("insert", q_insert(91) == q_success);
    for(int i = 0; i < 1000; i++) {
        // printf("%d \n", i);
        mu_assert("insert", q_insert(8) == q_success);
        mu_assert("insert", q_insert(91) == q_success);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == 8);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == 91);
    }
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_indexed_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 1000; i++) {
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("insert", q_insert(30 + i) == q_success);
    }
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_too_many_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("remove", q_remove(&v) == q_failure);
    return NULL;
}

char * test_insert_too_many_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 30; i++) {
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
    }
    mu_assert("remove", q_remove(&v) == q_failure);
    return NULL;
}

char * test_peek(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_peek(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_peek_two(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("peek", q_peek(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_peek_deep(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 1000; i++) {
        mu_assert("peek", q_peek(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("insert", q_insert(30 + i) == q_success);
    }
    mu_assert("destroy", q_destroy() == q_success);
    return NULL;
}

char * test_peek_empty(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("peek", q_peek(&v) == q_failure);
    return NULL;
}

char * test_peek_two_empty(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("peek", q_peek(&v) == q_failure);
    return NULL;
}

char * test_remove_null(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_remove(NULL) == q_failure);
    return NULL;
}

char * test_peek_null(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_peek(NULL) == q_failure);
    return NULL;
}

char * add_3_remove_3(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("insert", q_insert(65) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 42);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 65);
    return NULL;
}

char * is_empty_1(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("isEmpty", q_is_empty() == 1);
    return NULL;
}

char * is_empty_2(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(65) == q_success);
    mu_assert("isEmpty", q_is_empty() == 0);
    return NULL;
}

char * all_tests(void) {
    /* Run all unit tests */
    mu_run_test(test_lifecycle);
    printf("1 \n");
    mu_run_test(test_one_insert);
    printf("2 \n");
    mu_run_test(test_one_insert_remove);
    printf("3 \n");
    mu_run_test(test_two_insert_remove);
    printf("4 \n");
    mu_run_test(test_multi_insert_remove);
    printf("5 \n");
    mu_run_test(test_indexed_insert_remove);
    printf("6 \n");
    mu_run_test(test_too_many_remove);
    printf("7 \n");
    mu_run_test(test_insert_too_many_remove);
    printf("8 \n");
    mu_run_test(test_peek);
    printf("9 \n");
    mu_run_test(test_peek_two);
    printf("10 \n");
    mu_run_test(test_peek_deep);
    printf("11 \n");
    mu_run_test(test_peek_empty);
    printf("12 \n");
    mu_run_test(test_peek_two_empty);
    printf("13 \n");
    mu_run_test(test_remove_null);
    printf("14 \n");
    mu_run_test(test_peek_null);
    printf("15 \n");
    mu_run_test(add_3_remove_3);
    mu_run_test(is_empty_1);
    mu_run_test(is_empty_2);
    return NULL;
}

/**** Main unit test runner ****/

int main(int argc, char *argv[]) {
    printf("Queue Module unit tests\n");
    char *result = all_tests();
    if (result) {
        printf("FAILURE at %s\n", result);
    } else {
        printf("ALL TESTS PASS\n");
    }
    printf("Tests run: %d\n", tests_run);
    return EXIT_SUCCESS;
}
