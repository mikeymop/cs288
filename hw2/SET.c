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

    /* first element? */
    if(element == set->head->item) {
        prev = set->head;
        i = set->head->next;
        free(set->head);
        set->head = i;
        return;
    }

    if(element == set->tail->item) {
        /*get 2nd to last element */
        for(i = set->head; i != set->tail; i = i->next)
            prev = i;
        free(prev->next);
        prev->next = NULL;
        set->tail = prev;
        return;
    } else {
        for(i = set->head; i != NULL; i = i->next) {
            if(element == i->item) {
                prev->next = i->next;
                free(i);
            }
            prev = i;
        }
        return;
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
    /* returns the union of set s and t */
    struct Set nset = SET_new();

    int val;
    struct Node *i;

    /* get elements from s into nset */
    for(i = s.head; i != NULL; i = i->next) {
        val = i->item;
        if(SET_contains(&nset, val)) 
            continue;
        SET_add(&nset, val);
    }
    for(i = t.head; i != NULL; i = i->next) {
        val = i->item;
        if(SET_contains(&nset, val))
            continue;
        SET_add(&nset, val);
    }
    return nset;
}

struct Set SET_intersection(struct Set s, struct Set t) {
    /* returns the union of set s and t */
    struct Set nset = SET_new();

    int val;
    struct Node *i;

    /* get elements from s into nset */
    for(i = s.head; i != NULL; i = i->next) {
        val = i->item;
        if(SET_contains(&t, val)) {
            SET_add(&nset, val);
        }
    }
    return nset;
}

struct Set SET_difference(struct Set s, struct Set t) {
    /* return s - t */
    struct Set nset = SET_new();

    int val;
    struct Node *i;

    /* sort out the elements for difference */
    for(i = s.head; i != NULL; i = i->next) {
        val = i->item;
        if(SET_contains(&t, val)) {
            continue;
        } else {
            SET_add(&nset, val);
        }
    }
    return nset;
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
    /* return from the set the element of lowest value */

    int t = set->head->item;
    struct Node *i;
    for(i = set->head; i != NULL; i = i->next) {
        if( t < i->item) {
            t = i->item;
            continue;
        }
        continue;
    }
    return t;
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

/*
    struct Set mset = SET_new();
    struct Set nset = SET_new();
    struct Set iset = SET_new();
    struct Set uset = SET_new();
    struct Set dset1 = SET_new();
    struct Set dset2 = SET_new();

    int i;

    SET_add(&mset, 1);
    SET_add(&nset, 1);
    SET_add(&mset, 3);
    SET_add(&nset, 3);
    SET_add(&mset, 3);
    SET_add(&mset, 11);
    SET_add(&nset, 11);
    SET_add(&nset, 12);
    SET_add(&nset, 4);
    SET_add(&mset, 10);

    i = SET_cardinality(&mset);
    printf("Cardin: %d\n", i);

    if(SET_contains(&mset, 10)) {
        printf("Has ten\n");
    }
    if(!SET_contains(&nset, 5)) {
        printf("Does not have 5\n");
    }
    SET_print(&mset);

    int min;
    min = SET_min(&mset);
    int max;
    max = SET_max(&mset);
    printf("Min value is %d\n", min);
    printf("Max value is %d\n", max);

    printf("mset: ");
    SET_print(&mset);
    printf("\nnset: ");
    SET_print(&nset);

    iset = SET_intersection(mset, nset);
    uset = SET_union(mset, nset);
    dset1 = SET_difference(mset, nset);
    dset2 = SET_difference(nset, mset);
    printf("\niset: ");
    SET_print(&iset);
    printf("\nuset: ");
    SET_print(&uset);
    printf("\nmset - nset: ");
    SET_print(&dset1);
    printf("nset - mset: ");
    SET_print(&dset2);

    printf("Remove from front of set\n");
    SET_remove(&uset, 1);
    SET_print(&uset);
    printf("Remove from middle of set\n");
    SET_remove(&uset, 12);
    SET_print(&uset);
    printf("Remove from end of set\n");
    SET_remove(&uset, 4);
    SET_print(&uset);

    printf("Remove all shit from one set\n");
    SET_remove(&uset, 3);
    SET_remove(&uset, 11);
    SET_remove(&uset, 10);
    SET_print(&uset);
    SET_add(&uset, 10);
    SET_print(&uset);
*/
    return 0;
}