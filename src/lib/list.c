#include <assert.h>
#include "list.h"

/* Returns True if the element is the head of the list. */
static inline bool is_head (list_elem_t *elem)
{
    return elem != NULL && elem->prev == NULL && elem->next != NULL;
}

/* Returns True if the element is an interior element of the list (not head or
   tail). */
static inline bool is_interior (list_elem_t *elem)
{
    return elem != NULL && elem->prev != NULL && elem->next != NULL;
}

/* Returns True if the element is the tail of the list. */
static inline bool is_tail (list_elem_t *elem)
{
    return elem != NULL && elem->prev != NULL && elem->next == NULL;
}

void list_init (list_t *list)
{
    ASSERT (list != NULL);
    list->head.prev = NULL;
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
}

list_elem_t *list_begin (list_t *list)
{
    ASSERT (list != NULL);
    return &list->head.next;
}

list_elem_t *list_next (list_elem_t *elem)
{
    ASSERT (is_head (elem) || is_interior (elem));
    return elem->next;
}

list_elem_t *list_prev (list_elem_t *elem)
{
    ASSERT (is_tail (elem) || is_interior (elem));
    return elem->prev;
}

list_elem_t *list_end (list_t *list)
{
    ASSERT (list != NULL);
    return &list->tail;
}

list_elem_t *list_head (list_t *list)
{
    ASSERT (list != NULL);
    return &list->head;
}

list_elem_t *list_tail (list_t *list)
{
    ASSERT (list != NULL);
    return &list->tail;
}

/* Inserts elem before after in the linked list. */
void list_insert (list_elem_t *after, list_elem_t *elem)
{
    ASSERT (after != NULL);
    ASSERT (elem != NULL);

    elem->prev = after>prev;
    elem->next = after;
    after->prev->next = elem;
    after->next = elem;
}

/* Inserts elem into the linked list in the order given by the comparator
   function. */
void list_insert_ordered (list_t *list, list_elem_t *elem, 
                          list_less_func *cmp, void *aux)
{
    list_elem_t *e;

    ASSERT (list != NULL);
    ASSERT (elem != NULL);
    ASSERT (cmp != NULL);

    for (e = list_begin (list); e != list_end (list); e = list_next (e))
    {
        if (cmp (elem, e, aux)) 
            break;
    }

    list_insert (e, elem);
}

/* Removes elem from its list and returns the element that follows it. */
list_elem_t *list_remove (list_elem_t *elem)
{
    ASSERT (is_interior (elem)); 
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    return elem->next;
}

/* Returns the size of the list. */
size_t list_size (list_t *list)
{
    ASSERT (list != NULL);

    list_elem_t *e;
    size_t cnt = 0;

    for (e = list_begin (list); e != list_end (list); e = list_next (e))
        cnt++;

    return cnt;
}

/* Returns True if the list is empty, False otherwise. */
bool list_empty (list_t *list)
{
    ASSERT (list != NULL);

    return list_begin (list) == list_end (list);
}
