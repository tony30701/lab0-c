/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return false;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *front, *rear;
    if (q == NULL) {
        return;
    }
    if ((front = q->head) == NULL) {
        free(q);
        return;
    }
    rear = front->next;
    while (rear != NULL) {
        free(front->value);
        free(front);
        (q->size)--;
        front = rear;
        rear = rear->next;
    }
    free(front->value);
    free(front);
    (q->size)--;
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    list_ele_t *newh;
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        // printf("new->value allocation failed\n");
        free(newh);
        return false;
    }

    // while(newh->value == NULL){
    //    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    //}

    for (int i = 0; i < strlen(s); i++) {
        newh->value[i] = s[i];
    }
    newh->value[strlen(s)] = '\0';
    newh->next = q->head;
    q->head = newh;

    if (q->size == 0) {
        q->tail = q->head;
    }
    q->size++;

    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    if (q->head == NULL) {
        return q_insert_head(q, s) ? true : false;
    }

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;

    newt->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    for (int i = 0; i < strlen(s); i++) {
        newt->value[i] = s[i];
    }
    newt->value[strlen(s)] = '\0';

    newt->next = NULL;  // Take care of this assignemnt, it's a must-be action
                        // as test program would iterate the linked list.
    // If the NULL is not assigned to newt->next, the test program would make
    // not qualified judge.

    q->tail->next = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL)
        return false;

    // copy string from list element to sp
    size_t string_length = strlen(q->head->value);
    if (bufsize == 0) {
        // Do nothing
    } else if (string_length <= (bufsize - 1)) {
        for (int i = 0; i < string_length; i++) {
            sp[i] = q->head->value[i];
        }
        sp[string_length] = '\0';
    } else {
        for (int i = 0; i < (bufsize - 1); i++) {
            sp[i] = q->head->value[i];
        }
        sp[bufsize - 1] = '\0';
    }

    // Use tmp pointer to store current head memory location
    list_ele_t *tmp = q->head;

    // Redirect q->head to the memory location of q->head->next
    q->head = q->head->next;  // origin
    q->size--;

    // Remove the space of memory location in tmp
    free(tmp->value);
    free(tmp);

    return true;  // origin
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *tmp;

    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *front = q->head;
    list_ele_t *rear = front->next;
    while (rear != NULL) {
        tmp = rear;
        rear = rear->next;
        tmp->next = front;
        front = tmp;
    }
    q->tail = q->head;
    q->tail->next = NULL;
    q->head = front;
}
