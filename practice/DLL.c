#include <stdio.h>
#include <stdlib.h>


/* self-referential structure */
struct Node {
	int item;
	struct Node *next;
	struct Node *prev;
};

struct List {
	struct Node *head;
};


struct List DLL_new() {
	/* construct an empty list */
	struct List list;
	list.head = NULL;
	return list;
}

int DLL_length(struct List *list) {
	/* return the number of items in the list */
	struct Node *p;

	int n = 0;
	for (p = list->head; p != NULL; p = p->next) {
		++n;
	}
	return n;
}

int DLL_empty(struct List *list) {
	/* return true if the list contains no items */
	return list->head == NULL;
}

int DLL_pop(struct List *list) {
	/* remove and return the first item of the list */
	/* Fix me! I'm not tail aware */
	struct Node *node = list->head;
	int item = node->item;
	list->head = node->next;
	free(node);
	return item;
}

void DLL_clear(struct List *list) {
	/* remove all the items from the list */
	while (!DLL_empty(list)) {
		DLL_pop(list);
	}
}
/*
void DLL_push(struct List *list, int item) {
	struct Node *node = malloc(sizeof(struct Node));
	node->item = item;
	list->head->prev = node;
	node->next = list->head;
	list->head = node;
}*/
void DLL_push(struct List *list, int item) {
	/* push item to the front of the list */
    struct Node *node = malloc(sizeof(struct Node));
    node->item = item;
    node->next = list->head;
    node->prev = NULL;
    if(list-> head != NULL) /* you cannot store a value in null location */
        list-> head->prev = node;
    list -> head = node;
}

void DLL_append(struct List *list, int item) {
    /* append the item to the end of the list */
    struct Node* node = malloc(sizeof(struct Node));
    struct Node* last = list->head;
    node->item = item;
    node->next = NULL;
    if(list->head == NULL) {
        node->prev = NULL;
        list->head = node;
    } else {
        while(last->next != NULL)
            last = last->next;
        last->next = node;
        node->prev = last;
    }
}

void DLL_print(struct List *set) {
    int t;
    struct Node *i;

    printf("{ ");
    for(i = set->head; i != NULL; i = i->next) {
        t = i->item;
        printf("%d, ", t);
    }
    printf("}\n");
}

void DLL_remove(struct List *list, int item) {
	/* remove a given item from *list */
	struct Node *i;
	/* if first */

	/* if last */
	for(i = list->head; i != NULL; i = i->next) {
		if(i->item == item) {
			i->next->prev = i->prev->next;
			free(i);
		}
	}
}


int main() {
	int i, d;
	struct List list = DLL_new();

	i = 22;
	DLL_append(&list, 4); /* mind= blown */
	DLL_push(&list, i);
	i = 33;
	DLL_append(&list, i);
	d = 555;
	DLL_push(&list, d);

	DLL_print(&list);


	return 0;
}