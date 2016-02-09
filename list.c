/*
 * list.c - implementation of the integer list functions
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"



list_t* lst_new()
{
   list_t *list;
   list = (list_t*) malloc(sizeof(list_t));
   list->first = NULL;
   return list;
}


void lst_destroy(list_t *list)
{
	struct lst_iitem *item, *nextitem;

	item = list->first;
	while (item != NULL){
		nextitem = item->next;
		free(item);
		item = nextitem;
	}
	free(list);
}


void insert_new_process(list_t *list, int pid, time_t starttime)
{
	lst_iitem_t *item;

	item = (lst_iitem_t *) malloc (sizeof(lst_iitem_t));
	item->pid = pid;
	item->starttime = starttime;
	item->endtime = 0;
  item->status = 0;
	item->next = list->first;
	list->first = item;
}


void update_terminated_process(list_t *list, int pid, int status, time_t endtime)
{
   lst_iitem_t *item;
   item = list -> first;
   while (item != NULL){
     if (item -> pid == pid) {
       item -> endtime = endtime;
       item -> status = status;
       break;
     }
     else {
       item = item -> next;
     }
   }
}


void lst_print(list_t *list)
{
	lst_iitem_t *item;

	printf("\nProcess list with Start, End, Execution time and Status:\n\n");
	item = list->first;
	while (item != NULL) {
		printf("PID:\t\t%d\n", item->pid);
    printf("Start Time:\t%s", ctime(&(item->starttime)));
    printf("End Time:\t%s", ctime(&(item->endtime)));
    printf("Execution Time:\t%ld Seconds\n", item->endtime - item->starttime);
    printf("Status:\t\t%d\n\n", item->status);
		item = item->next;
	}
	printf("-- end of list.\n");
}
