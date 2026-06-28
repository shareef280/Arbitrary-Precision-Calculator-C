#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Terminal Colors */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

/* Status Codes */
typedef enum
{
    success,
    failure
} Status;

/* Supported Operations */
typedef enum
{
    add,
    subs,
    multiply,
    division,
    unsupported
} OperationType;

/* Doubly Linked List Node */
typedef struct OPERANDS
{
    int data;
    struct OPERANDS *prev;
    struct OPERANDS *next;
} Dlist;


/* Validation */
OperationType check_operation_type(int argc, char *argv[]);
Status read_and_validate_OPD_OPR(int argc,char*argv[],char *sign1,char *sign2);
Status execute_operation(Dlist ** head1,Dlist ** tail1,Dlist **head2,Dlist** tail2,Dlist **head_r,Dlist **tail_r,char sign1,char sign2,char *sign_r,char opt,char**argv);

/* Operand Handling */

Status insert_operands(Dlist **head1, Dlist **tail1, char *str1,Dlist **head2, Dlist **tail2, char *str2);

/* Linked List Utilities */

Status insert_last(Dlist **head, Dlist **tail, int data);
Status insert_at_first(Dlist **head, Dlist **tail, int data);
Status Delete_list(Dlist **head, Dlist **tail);
void print_list(Dlist *head);
void remove_leading_zeros(Dlist **head, Dlist **tail);

/* Addition */
Status add_opr(Dlist *tail1, Dlist *tail2, Dlist **head_r, Dlist **tail_r);

/* Subtraction */

Status compare_list(Dlist *head1, Dlist *head2);
Status sub(Dlist *tail1, Dlist *tail2,Dlist **head_r, Dlist **tail_r);
Status sub_opr(Dlist *head1, Dlist *tail1,Dlist *head2, Dlist *tail2,Dlist **head_r, Dlist **tail_r);

/* Multiplication */
Status mul_opr(Dlist *tail1, Dlist *tail2,Dlist **head_r, Dlist **tail_r);

/* Division */
Status increment(Dlist **head, Dlist **tail);
Status div_opr(Dlist **head1, Dlist **tail1,Dlist *head2, Dlist **tail2,Dlist **head_r, Dlist **tail_r);

/* Output */
Status display(Dlist *head, char *argv[],char sign_r);

#endif