#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */

struct list_head *q_new()

{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL; 
    }

    INIT_LIST_HEAD(head);
    return head;
}


/* Free all storage used by queue */

void q_free(struct list_head *head) {

 if (!head)
        return;
    struct list_head *current = head->next;
    while (current != head) {
        struct list_head *tmp = current;
        current = current->next;
        element_t *entry = list_entry(tmp, element_t, list);
        free(entry->value);
        free(entry);
    }
    free(head);
}



/* Insert an element at head of queue */

bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element)
        return false;
    new_element->value = strdup(s);
    if (!new_element->value) {
        free(new_element);
        return false;
    }

    

    new_element->list.next = head->next;
    head->next->prev = &new_element->list;
    head->next = &new_element->list;
    new_element->list.prev = head;
    return true;

}



/* Insert an element at tail of queue */

bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element)
        return false;
    new_element->value = strdup(s);
    if (!new_element->value) {
        free(new_element);
        return false;
    }

    

    list_add_tail(&new_element->list, head);

    return true;

}



/* Remove an element from head of queue */

element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)

{

     if (!head || head->next == head)

        return NULL;



    struct list_head *first = head->next;

    element_t *elem = list_entry(first, element_t, list);

    

    // Copy string to provided buffer sp, if non-NULL

    if (sp && bufsize) {

        strncpy(sp, elem->value, bufsize - 1);

        sp[bufsize - 1] = '\0';

    }



    // Unlink the first element from the list

    head->next = first->next;

    first->next->prev = head;



    return elem;

}



/* Remove an element from tail of queue */

element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)

{

     if (!head || head->prev == head)

        return NULL;



    struct list_head *last = head->prev;

    element_t *elem = list_entry(last, element_t, list);



    // Copy string to provided buffer sp, if non-NULL

    if (sp && bufsize) {

        strncpy(sp, elem->value, bufsize - 1);

        sp[bufsize - 1] = '\0';

    }



    // Unlink the last element from the list

    head->prev = last->prev;

    last->prev->next = head;



    return elem;

}



/* Return number of elements in queue */

int q_size(struct list_head *head)

{

    if (!head) return 0;



    int len = 0;

    struct list_head *li;



    list_for_each (li, head)

        len++;

    return len;

}



/* Delete the middle node in queue */

bool q_delete_mid(struct list_head *head)

{

    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/

    // Return false if the list is empty or has only one element.

    if (!head || head->next == head || head->next->next == head) {

        return false;

    }



    struct list_head *slow = head->next;

    struct list_head *fast = head->next->next;

    

    // Find the middle node

    while (fast != head && fast->next != head) {

        slow = slow->next;

        fast = fast->next->next;

    }



    // Now 'slow' is pointing to the middle node.

    // Unlink the middle node from the list.

    slow->prev->next = slow->next;

    slow->next->prev = slow->prev;



    // Free the middle node.

    element_t *middle = list_entry(slow, element_t, list);

    free(middle->value);

    free(middle);



    return true;

}



/* Delete all nodes that have duplicate string */

bool q_delete_dup(struct list_head *head)

{

    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

    return true;

}



/* Swap every two adjacent nodes */

void q_swap(struct list_head *head)

{

    // https://leetcode.com/problems/swap-nodes-in-pairs/

}



/* Reverse elements in queue */

void q_reverse(struct list_head *head) 

{

    // https://leetcode.com/problems/reverse-nodes-in-k-group/

}



/* Reverse the nodes of the list k at a time */

void q_reverseK(struct list_head *head, int k)

{

    // https://leetcode.com/problems/reverse-nodes-in-k-group/

}



/* Sort elements of queue in ascending/descending order */

void q_sort(struct list_head *head, bool descend) {}



/* Remove every node which has a node with a strictly less value anywhere to

 * the right side of it */

int q_ascend(struct list_head *head)

{

    // https://leetcode.com/problems/remove-nodes-from-linked-list/

    return 0;

}



/* Remove every node which has a node with a strictly greater value anywhere to

 * the right side of it */

int q_descend(struct list_head *head)

{

    // https://leetcode.com/problems/remove-nodes-from-linked-list/

    return 0;

}
