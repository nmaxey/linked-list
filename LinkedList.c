
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {	
	ListNode * e;
 	e = list->head;
	while (e != NULL) {

		if(e->value == value) { return 1;}
		e = e->next;

	}
	return 0;

}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * e = list->head;
	ListNode * prev = NULL;
	if(llist_exists(list,value) == 0){return 0;}
	
	while (e != NULL) {

		if(e->value == value) { break;}
		prev = e;
		e = e->next;

	}
	if (prev == NULL) {
		list->head = e->next;
	}else {
		prev->next = e->next;
	}
	
	//free(e->name);
	//free(e->address);
	free(e);
	return 1;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * e = list->head;
	int counter = 0;
	while (e != NULL) {

		if (ith == counter){
			*value = e->value;
			return 1;
		}
		e = e->next;
		counter++;

	}
	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * e = list->head;
	int counter = 0;
	while (e != NULL) {

		if (ith == counter){
			llist_remove(list,e->value);
			return 1;
		}
		e = e->next;
		counter++;

	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	ListNode * e = list->head;
	int counter = 0;
	while (e != NULL) {
		counter++;
		e = e->next;
	}
	return counter;

}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	ListNode * e = list->head;
	FILE * fd = fopen(file_name, "w+");
	if(fd == NULL)
		return 0;
	while (e != NULL) {
		fprintf(fd, "%d\n", e->value);
		e = e->next;
	}
	fclose(fd);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	int i = 0;
	int numbers = 0;
	char number;
	FILE * fd = fopen(file_name, "r");
	if (fd == NULL) {
		return 0;

     }
	llist_clear(list);
	fscanf (fd, "%d", &i);
	while (!feof (fd)) {
		llist_add(list,i);
		fscanf (fd, "%d", &i);
	}
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	ListNode * e = list->head;
	ListNode * f = list->head;
	int temp,k,i,j;
	int total = llist_number_elements(list);
	if(ascending == 0) {
		for(i = 0; i < total; i++) {
			for(j = i+1; j < total+1; j++) {
				if(e->value <= f->value){
					temp = e->value;
					e->value = f->value;
					f->value = temp;
				}
				f = f->next;
			}
			e = e->next;
			f = list->head;
			for(k = 0; k <= i; k++) {
				f = f->next;
			}
			
		}
	}else{
		for(i = 0; i < total; i++) {
			for(j = i+1; j < total+1; j++) {
				if(e->value >= f->value){
					temp = e->value;
					e->value = f->value;
					f->value = temp;
				}
				f = f->next;
			}
			e = e->next;
			f = list->head;
			for(k = 0; k <= i; k++) {
				f = f->next;
			}
			
		}

	}
	
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * e;
	if (list->head == NULL) return 0;
	e = list->head;
	*value = e->value;
	llist_remove(list,e->value);
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
	ListNode * e;
	if(list->head == NULL) return 0;
	e = list->head;
	while(1) { 
		if(e->next == NULL){
			*value = e->value;
			llist_remove(list,e->value);
			break;

		}
		e = e->next;
	}

	return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	llist_add(list,value);

}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {

	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	ListNode * e = list->head;
	if(list->head == NULL) {
		list->head = n;
		return;
	}

	while(1) { 
		if(e->next == NULL){
           	e->next = n;
                break;
          }
		e = e->next;
	}
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{

	for(int i = llist_number_elements(list); i >= 0; i--) {
		llist_remove_ith(list, i);
	}
	

}
