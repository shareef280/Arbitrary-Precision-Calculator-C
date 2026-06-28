#include<stdio.h>
#include"apc.h"
#include<string.h>

// Function to perform multiplication of two large numbers
Status mul_opr(Dlist *tail1,Dlist*tail2,Dlist**head_r,Dlist **tail_r)
{
    Dlist *temp1 = tail1;
    int res = 0;
    int count = 0;

    Dlist *temp2 = tail2;
    int carry = 0;

    Dlist *headr1 = NULL;
    Dlist *tailr1 = NULL;

    Dlist *headr2 = NULL;
    Dlist *tailr2 = NULL;

    // Traverse second operand from last digit
    while(temp2)
    {
        temp1 = tail1;

        // Multiply each digit of first operand
        while(temp1)
        { 
            res = (temp2->data * temp1->data) + carry;

            // Handle carry
            if(res > 9)
            {
                carry = res / 10;
                res = res % 10;
            }
            else
            {
                carry = 0;
            }

            // Store partial result
            insert_at_first(head_r,tail_r,res);

            temp1 = temp1->prev;
        }

        // Insert remaining carry
        if(carry)
        {
            insert_at_first(head_r,tail_r,carry);
            carry = 0;
        }

        // Store first partial result
        if(headr1 == NULL && !count)
        {
            headr1 = *head_r;
            tailr1 = *tail_r;
        }
        else
        {
            // Store next partial result
            headr2 = *head_r;
            tailr2 = *tail_r;
            int n = 0;

            *head_r = *tail_r = NULL;

            // Add required zeros based on position
            while(count != n)
            {
                insert_last(&headr2,&tailr2,0);
                n++;
            }

            // Add previous result with current shifted result
            add_opr(tailr1,tailr2,head_r,tail_r);

            // Delete temporary lists
            Delete_list(&headr2,&tailr2);
            Delete_list(&headr1,&tailr1);

            // Update accumulated result
            headr1 = *head_r;
            tailr1 = *tail_r;
        }

        // Increase shift count
        count++;

        // Move to next digit of second operand
        temp2 = temp2->prev;

        // Reset result list for next partial multiplication
        if(temp2 != NULL)
        {
            *head_r = NULL;
            *tail_r = NULL;
        }
    }

    // Remove leading zeros from final result
    remove_leading_zeros(head_r,tail_r);

    return success;
}