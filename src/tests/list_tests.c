#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "../lib/list.h"

void test_simple (void) 
{
    list_t *lst = (list_t *) malloc (sizeof (list_t));
    list_init (lst);

    list_elem_t *elem1 = (list_elem_t *) malloc (sizeof (list_elem_t));
    list_push_front (lst, elem1);

    assert (is_start (elem1));
    assert (is_end (elem1));

    list_elem_t *elem2 = (list_elem_t *) malloc (sizeof (list_elem_t));
    list_push_front (lst, elem2);

    assert (is_start (elem2));
    assert (is_end (elem1));

    free (elem1);
    free (elem2);
    free (lst);

    printf("test_simple passed\n");
}

void test_remove_items (void)
{
    list_t *lst = (list_t *) malloc (sizeof (list_t));
    list_init (lst);

    list_elem_t *elem1 = (list_elem_t *) malloc (sizeof (list_elem_t));
    list_elem_t *elem2 = (list_elem_t *) malloc (sizeof (list_elem_t));
    list_elem_t *elem3 = (list_elem_t *) malloc (sizeof (list_elem_t));
    list_elem_t *elem4 = (list_elem_t *) malloc (sizeof (list_elem_t));
    list_elem_t *elem5 = (list_elem_t *) malloc (sizeof (list_elem_t));

    list_push_front (lst, elem1);
    list_push_front (lst, elem2);
    list_push_front (lst, elem3);
    list_push_front (lst, elem4);
    list_push_front (lst, elem5);

    assert (is_start (elem5));
    assert (is_end (elem1));

    list_remove (elem5);
    list_remove (elem1);

    assert (is_start (elem4));
    assert (is_end (elem2));

    list_remove (elem4);
    list_remove (elem2);

    assert (is_start (elem3));
    assert (is_end (elem3));

    list_remove (elem3);

    assert (list_empty (lst));

    free (elem1);
    free (elem2);
    free (elem3);
    free (elem4);
    free (elem5);
    free (lst);

    printf("test_remove_items passed\n");
}

int main (void)
{
    test_simple ();
    test_remove_items ();

    return 0;
}
