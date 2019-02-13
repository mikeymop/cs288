#include <stdio.h>
#include <stdlib.h>

/* self-referential structure */
struct Node {
    int item;
    struct Node *next;
};

struct Set {
    struct Node *head;
    struct Node *tail;
};

struct Set SET_new() {
    struct Set set;
    set.head = NULL;
    set.tail = NULL;
    return set;
}

void SET_add(struct Set *set, int element) {
    
    if(set->head == NULL) {
        struct Node *nnode = malloc(sizeof(struct Node));
        nnode->item = element;
        nnode->next = NULL;
        set->head = nnode;
        set->tail = nnode;
        return;
    }

    /* scan across the set for the element */
    struct Node *i;
    for(i = set->head; i != NULL; i = i->next) {
        if(element == i->item) {
            i->item = element;
            return;
        }
    }
    /* create node at end of set */ 
    struct Node *nnode = malloc(sizeof(struct Node));
    nnode->item = element;
    nnode->next = NULL;
    set->tail->next = nnode;
    set->tail = nnode;
}

void SET_remove(struct Set *set, int element) {
    /* scan across the set, find element*/
    struct Node *i;
    struct Node *prev;
    for(i = set->head; i != NULL; i = i->next) {
        if(element == i->item) {
            prev->next = i->next;
            return;
        }
        prev = i;
    }
    /* set element equal the elements next */
}

int SET_cardinality(struct Set *set) {
    /* returns the number of elements in the set */
    struct Node *i;

    int n = 0;
    for(i = set->head; i != NULL; i = i->next) {
        n++;
    }
    return n;
}

int SET_contains(struct Set *set, int element) {
    struct Node *i;

    for(i = set->head; i != NULL; i = i->next) {
        if(i->item == element) {
            return 1;
        }
    }
    return 0;
}

struct Set SET_union(struct Set s, struct Set t) {
}

struct Set SET_intersection(struct Set s, struct Set t) {
}

struct Set SET_difference(struct Set s, struct Set t) {
    /* return s - t */
}

int SET_min(struct Set *set) {
    /* return from the set the element of lowest value */

    int t = set->head->item;
    struct Node *i;
    for(i = set->head; i != NULL; i = i->next) {
        if(t > i->item) {
            t = i->item;
            continue;
        }
        continue;
    }
    return t;
}

int SET_max(struct Set *set) {
}

void SET_print(struct Set *set) {
    printf("{ ");
    int t;
    struct Node *i;
    for(i = set->head; i != NULL; i = i->next) {
        t = i->item;
        printf("%d, ", t);
    }
    printf("}\n");
}


int main() {
    struct Set mset = SET_new();
    int i, i2, i3, i4, i5;

    SET_add(&mset, 1);
    SET_add(&mset, 2);
    i = SET_cardinality(&mset);
    SET_add(&mset, 3);
    i2 = SET_cardinality(&mset);
    SET_add(&mset, 3);
    i3 = SET_cardinality(&mset);
    SET_add(&mset, 4);
    i4 = SET_cardinality(&mset);
    SET_add(&mset, 10);
    i5 = SET_cardinality(&mset);

    printf("%d, %d, %d, %d, %d\n", i, i2, i3, i4, i5);

    i = SET_cardinality(&mset);
    printf("%d\n", i);

    SET_remove(&mset, 10);

    if(SET_contains(&mset, 10)) {
        printf("Has ten\n");
    }
    if(SET_contains(&mset, 3)) {
        printf("Has 3\n");
    }

    SET_print(&mset);
    int min;
    min = SET_min(&mset);
    printf("Min value is %d\n", min);

}