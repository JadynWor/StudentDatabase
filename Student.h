/*
 * Student.h
 *
 *  Created on: Sep 9, 2022
 *      Author: jadynworthington
 */

#ifndef STUDENT_H_
#define STUDENT_H_

typedef struct student{

    char *name;
    char *lastname;
    long studentID;
    char *class;
    int grad_Year;

    struct student *next;
    struct student *prev;
}student_t;

typedef struct DLL{
    struct student *head;   //pointer to head node
    struct student *tail;   //pointer to tail

    long maxID;             /* temporarily used to assign studentID */
} DLL_t;

#endif /* STUDENT_H_ */
