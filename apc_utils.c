#include<stdio.h>
#include"apc.h"
#include<string.h>

// Function to print all digits in the linked list
void print_list(Dlist *head)
{
	/* Checking whether the list is empty */
	if (head == NULL)
	{
		printf(RED "INFO : List is empty\n" RESET);
	}
	else
	{
	    // Traverse and print each node
	    while (head)		
	    {
		    /* Printing each digit in green */
		    printf(GREEN "%d" RESET, head->data);

		    /* Move to next node */
		    head = head->next;
	    }
    }
} 


// Function to display operands, operator and final result
Status display(Dlist *head, char *argv[], char sign_r)
{
    // If result is zero, make sign positive
    if(head->data == 0 && head->next == NULL)
        sign_r = '+';

    printf(BLUE "\n════════════════════════════════════\n" RESET);
    printf(YELLOW "      APC - BIG INTEGER CALCULATOR\n" RESET);
    printf(BLUE "════════════════════════════════════\n" RESET);

    printf(CYAN " First Number  : " RESET "%s\n", argv[1]);
    printf(CYAN " Operation     : " RESET "%c\n", argv[2][0]);
    printf(CYAN " Second Number : " RESET "%s\n", argv[3]);

    printf(BLUE "────────────────────────────────────\n" RESET);

    printf(GREEN " Result        : " RESET);

    if(sign_r == '-')
    {
        printf(RED "-" RESET);
    }

    print_list(head);

    printf(BLUE "\n════════════════════════════════════\n\n" RESET);
}
// Function to validate input operands and extract their signs
Status read_and_validate_OPD_OPR(int argc,char*argv[],char *sign1,char *sign2)
{  
    // Check sign of first operand
     if(argv[1][0]=='-' )
    {     *sign1='-';
    }else if(argv[1][0]=='+')
    {
        *sign1='+';
    }
   
  int i=0;
  // Validate first operand characters
  while(argv[1][i]!='\0'){
       if (i == 0 && (argv[1][i] == '+' || argv[1][i] == '-'))
       {
        i++;
        continue;
       }

       if (!isdigit(argv[1][i]))
       {
       printf(RED "[ERROR] Invalid operand format. Use only digits with an optional leading '+' or '-'.\n" RESET);
        return failure;
       }

      i++;
  }
  // Check sign of second operand
  if(argv[3][0]=='-' )
    {     *sign2='-';
    }else if(argv[3][0]=='+')
    {
        *sign2='+';
    }
   
  i = 0;
// Validate second operand characters
while (argv[3][i] != '\0')
{
    if (i == 0 && (argv[3][i] == '+' || argv[3][i] == '-'))
    {
        i++;
        continue;
    }

    if (!isdigit(argv[3][i]))
    {
        printf(RED "[ERROR] Invalid operand format. Use only digits with an optional leading '+' or '-'.\n" RESET);
        return failure;
    }

    i++;
}
  return success;

}
// Function to convert string operands into linked lists
Status insert_operands(Dlist **head1, Dlist **tail1, char *str1,Dlist **head2, Dlist **tail2, char *str2)
{
    int i;
// Insert first operand into linked list
    for(i = 0; str1[i] != '\0'; i++)
    {   if(str1[i]=='-' || str1[i]=='+')
           continue;
        insert_last(head1, tail1, str1[i] - '0');
    }
// Insert second operand into linked list
    for(i = 0; str2[i] != '\0'; i++)
    {    if(str2[i]=='-' || str2[i]=='+')
           continue;
        insert_last(head2, tail2, str2[i] - '0');
    }
    // Remove leading zeros from operands
    remove_leading_zeros(head1,tail1);
    remove_leading_zeros(head2,tail2);


    return success;
}

// Function to insert node at last of the list
Status insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    if(new == NULL)
    {
        return failure;
    }

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if(*head == NULL)
    {
        *head = new;
        *tail = new;
        return success;
    }

    (*tail)->next = new;
    new->prev = *tail;
    *tail = new;

    return success;
}

Status insert_at_first(Dlist ** head,Dlist **tail,int data)
 {
    Dlist *new=malloc(sizeof(Dlist));
    if(new==NULL){
        return failure;
    }
    new->data=data;
    new->prev=new->next=NULL;
    if(*head==NULL){
        *head=new;
        *tail=new;
        return success;
    }
    (*head)->prev=new;
    new->next=*head;
    *head=new;
    return success;
 }

 // Function to delete all nodes in the linked list
Status Delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
    return success;
}

// Function to remove unnecessary leading zeros
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while(*head && (*head)->next && (*head)->data == 0)
    {   
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}
// Function to decide and execute arithmetic operation based on operator
Status execute_operation(Dlist ** head1,Dlist ** tail1,Dlist **head2,Dlist** tail2,Dlist **head_r,Dlist **tail_r,char sign1,char sign2,char *sign_r,char opt,char**argv)
{
   switch(opt)
   {    // Addition operation
        case '+':
          if(sign1=='+' && sign2=='+'){
             *sign_r='+';
            if(add_opr(*tail1,*tail2,head_r,tail_r) == success)
                {
                   display(*head_r,argv,*sign_r);
                }
            else
                {
                    printf(RED "[ERROR] Addition operation failed.\n" RESET);
                }
          }else if(sign1=='-' && sign2=='-'){
                *sign_r='-';
               if(add_opr(*tail1,*tail2,head_r,tail_r) == success)
                {
                   display(*head_r,argv,*sign_r);
                }
            else
                {
                    printf(RED "[ERROR] Addition operation failed.\n" RESET);
                }
          }else if(sign1=='-' || sign2=='-')
          {      if(compare_list(*head1 ,*head2)==1){
                  *sign_r=sign1;
                 }else if(compare_list(*head1 ,*head2)==0){
                     *sign_r=sign2;
                 }
                 else{
                     *sign_r='+';
                  }
                  if(sub_opr(*head1,*tail1,*head2,*tail2,head_r,tail_r)== success)
                {   printf("sign_r ==%c\n",*sign_r);
                    display(*head_r,argv,*sign_r);
                }
                else
                {
                    printf(RED "[ERROR] Subtraction operation failed.\n" RESET);
                }
          } 
          break;
          // Subtraction operation
           case '-':
            if(sign1=='+' && sign2=='+' ) 
            {  if(compare_list(*head1 ,*head2)==1 )
                   *sign_r='+';
                if(compare_list(*head1 ,*head2)==0 )
                    *sign_r='-';
                  if(sub_opr(*head1,*tail1,*head2,*tail2,head_r,tail_r)== success)
                   {
                     display(*head_r,argv,*sign_r);
                   }
                   else
                  {
                     printf(RED "[ERROR] Subtraction operation failed.\n" RESET);
                  }
            }
            else if(sign1=='-' && sign2=='-'){
                    if(compare_list(*head1 ,*head2)==1 )
                       *sign_r='-';
                    if(compare_list(*head1 ,*head2)==0 )
                    *sign_r='+';
                    if(sub_opr(*head1,*tail1,*head2,*tail2,head_r,tail_r)== success)
                    {
                      display(*head_r,argv,*sign_r);
                    }
                  else
                   {
                     printf(RED "[ERROR] Addition operation failed.\n" RESET);
                   }
             }else if(sign1=='+' && sign2=='-')
             {    *sign_r='+';
                if(add_opr(*tail1,*tail2,head_r,tail_r) == success)
                {
                   display(*head_r,argv,*sign_r);
                }
                else
                   {
                     printf(RED "[ERROR] Addition operation failed.\n" RESET);
                   }
             }else if(sign1=='-' && sign2=='+') 
              {    *sign_r='-';
                if(add_opr(*tail1,*tail2,head_r,tail_r) == success)
                {
                   display(*head_r,argv,*sign_r);
                }
                else
                   {
                     printf(RED "[ERROR] Addition operation failed.\n" RESET);
                   }
             }
             break;
             // Multiplication operation
             case 'x':
                 if(sign1=='+' && sign2=='+')
                    *sign_r='+';
                 else if(sign1=='-' && sign2=='-')
                   *sign_r='+';
                 else if(sign1=='-' || sign2=='-')
                   *sign_r='-';

                 if(mul_opr(*tail1,*tail2,head_r,tail_r) == success)
                 {
                     display(*head_r,argv,*sign_r);
                 }
                 else
                 {
                     printf(RED "[ERROR] Multiplication operation failed.\n" RESET);
                 }
            
             break;
             // Division operation
             case '/':
                 if(sign1=='+' && sign2=='+')
                    *sign_r='+';
                 else if(sign1=='-' && sign2=='-')
                   *sign_r='+';
                 else if(sign1=='-' || sign2=='-')
                   *sign_r='-';

                 if(div_opr(head1,tail1,*head2,tail2,head_r,tail_r) == success)
                 {
                     display(*head_r,argv,*sign_r);
                 }
                 else
                 {
                     printf(RED "[ERROR] Division operation failed.\n" RESET);
                 }
             break;
             // Invalid operator case
            default: 
              printf("Invalid operator\n");
   }

   return success;             
}