#include<stdio.h>
#include"apc.h"
#include<string.h>

// Function to perform division operation
Status div_opr(Dlist **head1,Dlist **tail1,Dlist *head2,Dlist **tail2,Dlist **head_r,Dlist **tail_r)
{
    // Check for divide by zero
    if(head2->data == 0 && head2->next == NULL)
    {
        printf("ERROR: DIVIDE BY ZERO NOT POSSIBLE\n");
        return failure;
    }

    // Initialize quotient counter
    Dlist *count_head = malloc(sizeof(Dlist));
    Dlist *count_tail = NULL;

    Dlist *new = malloc(sizeof(Dlist));

    new->data = 0;
    new->prev = new->next = NULL;

    count_head->prev = count_head->next = NULL;
    count_head->data = new->data;
    count_tail = count_head;

    new->data = 1;
    new->prev = new->next = NULL;
    
    // Repeat subtraction until dividend becomes smaller than divisor
    while(compare_list(*head1 ,head2))
    { 
        // Subtract divisor from dividend
        sub(*tail1,*tail2,head_r,tail_r);

        // Remove leading zeros from intermediate result
        remove_leading_zeros(head_r, tail_r);

        // Delete old dividend list
        Delete_list(head1,tail1);

        // Update dividend with new result
        *head1 = *head_r;
        *tail1 = *tail_r;
         
        // Reset result list
        *head_r = *tail_r = NULL;
        
        // Increment quotient count
        increment(&count_head, &count_tail);
    }

    // Store final quotient in result
    *head_r = count_head;
    *tail_r = count_tail;

    // Remove leading zeros from quotient
    remove_leading_zeros(head_r,tail_r);

    return success;
}


// Function to compare two linked list numbers
Status compare_list(Dlist *head1 ,Dlist *head2)
{
    Dlist *temp1 = head1;
    int len2 = 0;

    Dlist *temp2 = head2;
    int len1 = 0;

    // Calculate length of both lists
    while(temp1 || temp2)
    {
        if(temp1)
        {
            len1++;
            temp1 = temp1->next;
        }

        if(temp2)
        {
            len2++;
            temp2 = temp2->next;
        }
    }

    // Compare based on length
    if(len1 > len2)
        return 1;

    else if(len2 > len1)
        return 0;

    else
    {
        temp1 = head1;
        temp2 = head2;

        // Compare digit by digit if lengths are equal
        while(temp1 && temp2)
        {
            if(temp1->data > temp2->data)
                return 1;

            else if(temp2->data > temp1->data)
                return 0;

            else
            {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }

        // Both numbers are equal
        return 2;
    }
}


// Function to increment linked list number by 1
Status increment(Dlist **head, Dlist **tail)
{
    Dlist *temp = *tail;
    int carry = 1;

    // Add 1 from last digit
    while(temp && carry)
    {
        temp->data += carry;

        // Handle carry
        if(temp->data > 9)
        {
            temp->data = 0;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        temp = temp->prev;
    }

    // Insert carry at beginning if needed
    if(carry)
    {
        insert_at_first(head, tail, 1);
    }

    return success;
}