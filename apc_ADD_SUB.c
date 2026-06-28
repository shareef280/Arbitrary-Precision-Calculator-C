#include<stdio.h>
#include"apc.h"
#include<string.h>
 
// Function to perform addition of two large numbers
Status add_opr(Dlist *tail1,Dlist *tail2,Dlist **head_r,Dlist**tail_r)
{ 
    int carry=0; 
    int data=0;

    // Traverse both lists from last digit
    while(tail1 || tail2)
    {
        // If both operands have digits
        if(tail1!=NULL && tail2!=NULL)
        {
            data = tail1->data + tail2->data + carry;
        }
        // If first operand has remaining digits
        else if(tail1 && tail2==NULL)
        {
            data = carry + tail1->data;
        }
        // If second operand has remaining digits
        else if(tail1==NULL && tail2)
        {
            data = carry + tail2->data;
        }
           
        // Check for carry generation
        if(data > 9)
        {
            data = data % 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        // Insert result digit at beginning
        insert_at_first(head_r,tail_r,data);

        // Move to previous node
        if(tail1!=NULL)
            tail1 = tail1->prev;

        if(tail2!=NULL)
            tail2 = tail2->prev;

        // Insert final carry if present
        if(tail1==NULL && tail2==NULL && carry)
        {
            insert_at_first(head_r,tail_r,carry);
        }
    }

    // Remove unnecessary leading zeros
    remove_leading_zeros(head_r,tail_r);
     
    return success;
}

 
// Function to perform subtraction by comparing operands
Status sub_opr(Dlist *head1, Dlist *tail1,Dlist *head2, Dlist *tail2,Dlist **head_r, Dlist **tail_r)
{
    int ret = compare_list(head1, head2);

    // If operand1 > operand2
    if(ret == 1)
    {
        sub(tail1, tail2, head_r, tail_r);
    }
    // If operand2 > operand1
    else if(ret == 0)
    {
        sub(tail2, tail1, head_r, tail_r);
    }
    // If both operands are equal
    else
    {
        insert_at_first(head_r, tail_r, 0);
    }

    // Remove unnecessary leading zeros
    remove_leading_zeros(head_r,tail_r);

    return success;
}


// Function to perform actual subtraction
Status sub(Dlist *tail1,Dlist *tail2,Dlist **head_r,Dlist **tail_r)
{
    int flag=0;
    int data;

    // Traverse both operands from last digit
    while(tail1 || tail2)
    {
        // Handle borrow from previous digit
        if(flag)
        {
            if(tail1->data==0)
            {
                tail1->data=(tail1->data +10) -1;
                flag=1;
            }
            else
            {
                tail1->data=tail1->data -1;
                flag=0;
            }
        }

        // If both operands have digits
        if(tail1 && tail2)
        {
            // Normal subtraction
            if(tail1->data >= tail2->data)
            {
                data = tail1->data - tail2->data;
            }
            // Borrow required
            else
            {
                data = (tail1->data +10) - tail2->data;
                flag = 1;
            }
        }
        // If first operand still has digits
        else if(tail1 && tail2==NULL)
        {
            data = tail1->data;
        }

        // Insert result digit at beginning
        insert_at_first(head_r,tail_r,data);

        // Move to previous node
        tail1 = tail1->prev;

        if(tail2)
            tail2 = tail2->prev;
    }

    // Remove leading zeros from result
    remove_leading_zeros(head_r, tail_r);

    return success;
}