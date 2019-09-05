// Simple implementation of a doubly-linked list.
#include <stdio.h>
#include <stdlib.h>

struct node_t {
    struct node_t *next, *back;
    int value;
};

void print_list(struct node_t *);
void insert_node(struct node_t **, int pos, int val);
void delete_node(struct node_t **, int pos);
struct node_t * advance(struct node_t *head, int distance);

// Test case
int main() {
    struct node_t *list = NULL;

    printf("Doubly-Linked List Test!\n"
           "Available operations:\n"
           "    p -- print the contents of the list.\n"
           "    + <index> <value> -- insert a node with <value> after node #<index>\n"
           "    - <index> -- delete node #<index>\n"
           "Initially, the list is empty\n\n");
    for (;;) {
        printf("> ");
        char cmd[1];
        scanf("%s", cmd);

        int x, v;
        switch (cmd[0]) {
        case '+':
            scanf("%d", &x);
            scanf("%d", &v);
            insert_node(&list, x, v);
            print_list(list);
            break;
        case '-':
            scanf("%d", &x);
            delete_node(&list, x);
            print_list(list);
            break;
        case 'p':
            print_list(list);
            break;
        case 'q':
            return 0;
        default:
            printf("Unknown command: %c.", cmd);
        }
    }
    return 0;
}

/*!
 * Prints the contents of the list.
 * \param[in] phead pointer the the list
 */
void print_list(struct node_t *head) {
    printf("[]: ");

    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }

    printf("\n");
}

/*!
 * Create and insert a node after the node with specified index.
 * \param[inout] phead the list itself, if NULL, will be replaced by the new node.
 * \param[in] xid the index after which the new node should be inserted.
 * \param[in] val the value with which the new node should be initialized.
 *
 * \warning if xid exceeds the size of the suffix, excluding the head itself, except for when the head is NULL, a segmentation fault may occur.
 */
void insert_node(struct node_t **phead, int xid, int val) {
    struct node_t * new = (struct node_t *)malloc(sizeof(struct node_t));
    new->back = new->next = NULL;
    new->value = val;

    if (*phead == NULL) {
        *phead = new;
    } else {
        struct node_t *target = advance(*phead, xid);

        if (target->next != NULL) {
            target->next->back = new;
        }
        new->next = target->next;
        new->back = target;
        target->next = new;
    }
}

/*!
 * Delete the node at a specified index.
 *
 * \param[inout] phead the pointer to the list.
 * \param[in] xid the index of the node to be deleted.
 *
 * \warning if \a xid exceeds the size of the suffix, excluding the head itself, a segmentation fault may occur.
 */
void delete_node(struct node_t **phead, int xid) {
    struct node_t *target = advance(*phead, xid);
    if (xid == 0) {
        *phead = target->next;
        if (target->next)
            target->next->back = NULL;
    } else {
        if (target->back)
            target->back->next = target->next;
        if (target->next)
            target->next->back = target->back;
    }
    free(target);
}

/*!
 * Get the pointer to the node that's \a d nodes further than the provided head.
 *
 * \warning If \a d is bigger than the size of the suffix, excluding the head itself, the segmentation fault may occur.
 */
struct node_t * advance(struct node_t *head, int d) {
    while (d--)
        head = head->next;
    return head;
}
