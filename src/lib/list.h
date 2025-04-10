#include <stdbool.h>

// Linked list element
typedef struct list_elem 
{
    struct list_elem *prev;
    struct list_elem *next;
}
list_elem_t;

// Linked list
typedef struct list
{
    list_elem_t head;
    list_elem_t tail;
}
list_t;

// List initialization
void list_init (list_t *list);

// List traversal
list_elem_t *list_begin (list_t *list);
list_elem_t *list_next (list_elem_t *list_elem);
list_elem_t *list_prev (list_elem_t *list_elem);
list_elem_t *list_end (list_t *list);

list_elem_t *list_head (list_t *list);
list_elem_t *list_tail (list_t *list);

// Comparator function for ordered operations on linked list elements
typedef bool list_less_func (const list_elem_t *a, const list_elem_t *b, 
                             void *aux);

// List insertion
void list_insert (list_elem_t *after, list_elem_t *elem);
void list_insert_ordered (list_t *list, list_elem_t *elem, 
                          list_less_func *func, void *aux);

// List removal
list_elem_t *list_remove (list_elem_t *elem);

// List properties
size_t list_size (list_t *list);
bool list_empty (list_t *list);

