#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "../include/list.h"

void test_simple (void) 
{
    list_t lst;
    list_init (&lst);

    list_elem_t elem1;
    list_push_front (&lst, &elem1);

    assert (is_start (&elem1));
    assert (is_end (&elem1));

    list_elem_t elem2;
    list_push_front (&lst, &elem2);

    assert (is_start (&elem2));
    assert (is_end (&elem1));

    printf("test_simple passed\n");
}

void test_remove_items (void)
{
    list_t lst;
    list_init (&lst);

    list_elem_t elem1;
    list_elem_t elem2;
    list_elem_t elem3;
    list_elem_t elem4;
    list_elem_t elem5;

    list_push_front (&lst, &elem1);
    list_push_front (&lst, &elem2);
    list_push_front (&lst, &elem3);
    list_push_front (&lst, &elem4);
    list_push_front (&lst, &elem5);

    assert (is_start (&elem5));
    assert (is_end (&elem1));

    list_remove_elem (&elem5);
    list_remove_elem (&elem1);

    assert (is_start (&elem4));
    assert (is_end (&elem2));

    list_remove_elem (&elem4);
    list_remove_elem (&elem2);

    assert (is_start (&elem3));
    assert (is_end (&elem3));

    list_remove_elem (&elem3);

    assert (list_empty (&lst));

    printf("test_remove_items passed\n");
}

void test_push_back (void)
{
    list_t lst;
    list_init (&lst);

    list_elem_t elem1;
    list_elem_t elem2;
    list_elem_t elem3;

    list_push_back (&lst, &elem1);
    assert (list_size (&lst) == 1);
    assert (is_start (&elem1));
    assert (is_end (&elem1));

    list_push_back (&lst, &elem2);
    assert (list_size (&lst) == 2);
    assert (is_start (&elem1));
    assert (is_end (&elem2));

    list_push_back (&lst, &elem3);
    assert (list_size (&lst) == 3);
    assert (is_start (&elem1));
    assert (is_end (&elem3));

    printf ("test_push_back passed\n");
}

int main (void)
{
    test_simple ();
    test_remove_items ();
    test_push_back ();

    return 0;
}
