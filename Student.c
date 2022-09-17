/*
 * Student.c
 *
 *  Created on: Sep 9, 2022
 *      Author: jadynworthington
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Student.h"

#define MAXC 128

// Functions
void instructions(void){
  fputs ( "\nEnter your choice:\n"
          "   1.  to insert an element into the list.\n"
          "   2.  to delete an element from the list.\n"
          "   3.  print list.\n"
		  "   4.  print reversed list.\n"
          "   5.  to end.\n\n"
          " Your choice: ", stdout);
  fflush (stdout);      /* flushing output */
}
char *strdupe (const char *src)
{
  char *dst = NULL;
  size_t length = strlen (src);              /* get length of source */

  if (!(dst = malloc (length + 1))) {        /* allocate/validate destination */
    perror ("malloc-strdupe");
    return NULL;
  }

  return memcpy (dst, src, length + 1);      /* return pointner to dst */
}

student_t *createnode (char *name, char *lastname, char *class,
                        long studentID, int grad_Year)
{
  student_t *node = malloc (sizeof *node);      /* allocate for node */

  if (!node) {  /* validate allocation for node */
    perror ("malloc-createnode-dst");
    return NULL;
  }
  node->next = node->prev = NULL;     /* initialize node pointers null */

  if (!(node->name = strdupe (name))) {         /* allocate/validate name */
    return NULL;
  }

  if (!(node->lastname = strdupe (lastname))) { /* ditto - lastname */
    return NULL;
  }

  if (!(node->class = strdupe (class))) {       /* ditto - class */
    return NULL;
  }

  /* assign remaining member values */
  node->studentID = studentID;
  node->grad_Year = grad_Year;

  return node;                        /* return pointer to allocated node */
}

student_t *insert (DLL_t *list, char *name, char *lastname,
                   char *class, long studentID, int grad_Year)
{
  /* create and validate new node */
  student_t *node = createnode (name, lastname, class,
                                studentID, grad_Year);
  if (!node) {
      return NULL;
  }

  if (!list->head)                      /* if 1st node, node is head/tail */
      list->head = list->tail = node;
  else {  /* otherwise */
      node->prev = list->tail;          /* set prev to tail */
      list->tail->next = node;          /* add at end, update tail pointer */
      list->tail = node;
  }

  return node;    /* return new node */
}

/** print helper for single node */
void print_node (student_t *node)
{
  printf ("\nEntry Key  : %ld\n"
          "First name : %s\n"
          "Last name  : %s\n"
          "Class      : %s\n"
          "Student ID  : %d\n",
          node->studentID, node->name, node->lastname,
          node->class, node->grad_Year);
}

/** print all nodes in list */
void print_list (DLL_t *list)
{
    if (!list->head) {
        puts ("list-empty");
        return;
    }

    /* loop over each node in list */
    for (student_t *n = list->head; n; n = n->next) {
        print_node (n);
    }
}
void print_listrev(DLL_t *list){
	 if (!list->head) {
	        puts ("list-empty");
	        return;
	 }

	    /* loop over each node in list */
	 for (student_t *n = list->tail; n; n = n->prev) {
	        print_node (n);
	 }
}

/** delete single node helper */
void del_node (student_t * node)
{
	//
	char buf[MAXC];
	char lastname[MAXC];

	fputs ("\nEnter Last name to delete: ", stdout);
	    if (!fgets (lastname, MAXC, stdin)){
	    	free (node->name);
	    	free (node->lastname);
	    	free (node->class);
	    	free (node);
	  }
	  lastname[strcspn (lastname, "\n")] = 0;
//

//	  free (node->name);
//	  free (node->lastname);
//	  free (node->class);
//	  free (node);


}

/** delete all nodes in list */
void del_list (DLL_t *list)
{
    student_t *n = list->head;

    while (n) {
        student_t *victim = n;      /* create temporary to delete */
        n = n->next;                /* advance node pointer to next */
        del_node (victim);          /* now free current node */
    }

    list->head = list->tail = NULL;
    list->maxID = 0;
}

int main (void) {     /* argument is void if you pass no arguments */

    char buf[MAXC];                   /* tmp buffer for all input */
    int option;

    DLL_t list = { .head = NULL};     /* initialize DLL_t struct pointers
                                       * no need to allocate.
                                       */

    while (1) { /* loop continually - use case to exit */

        instructions();                         /* show prompt */
        if (!fgets (buf, MAXC, stdin)) {        /* validate input received */
          puts ("(user canceled input)");
          return 0;
        }
        if (sscanf (buf, "%d", &option) != 1) { /* parse int from buf */
          fputs ("error: invalid integer input.\n", stderr);
          return 1;
        }

        switch (option) {

        case 1:
        {
          /* temp storage for strings */
          char name[MAXC], lastname[MAXC], class[MAXC];
          int grad_Year = 0;

          /* there is no conversion in the string - no need for printf() */
          fputs ("\nEnter first name : ", stdout);
          if (!fgets (name, MAXC, stdin)) {
            puts ("(user canceled input)");
            return 0;
          }
          name[strcspn (name, "\n")] = 0;           /* trim \n from name */

          fputs ("Enter lastname   : ", stdout);
          if (!fgets (lastname, MAXC, stdin)) {
            puts ("(user canceled input)");
            return 0;
          }
          lastname[strcspn (lastname, "\n")] = 0;   /* trim \n from lastname */

          fputs ("Enter class name : ", stdout);
          if (!fgets (class, MAXC, stdin)) {
            puts ("(user canceled input)");
            return 0;
          }
          class[strcspn (class, "\n")] = 0;         /* trim \n from class */

          fputs ("Enter grad year  : ", stdout);
          if (!fgets (buf, MAXC, stdin)) {
            puts ("(user canceled input)");
            return 0;
          }
          class[strcspn (class, "\n")] = 0;

          fputs("Enter StudentID   : ",stdout);
          if (!fgets(buf, MAXC, stdin)){
            puts("user canceled input");
            return 0;
          }
          if (sscanf (buf, "%d", &grad_Year) != 1) {  /* parse grad_Year */
            fputs ("error: invalid integer input.\n", stderr);
            return 1;
          }

          if (!insert (&list, name, lastname, class, list.maxID, grad_Year)) {
            continue;
          }

          list.maxID += 1;
          break;
        }

        case 2:
        	del_node(&list);
        	//del_list(&list);
        case 3:
        	printf("\nViewing List\n");
            print_list (&list);
            break;
        case 4:
        	print_listrev(&list);
            break;
        case 5:
        	fputs("\nExiting software\n",stdout);
        	goto donelooping;
            break;
        default:
            puts ("Invalid choice.");
            break;
        }
    }
    donelooping:;

    del_list (&list);   /* free all allocated memmory */
}
