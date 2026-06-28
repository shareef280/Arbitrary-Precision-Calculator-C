
/*
 * ==============================================================
 * Project : Arbitrary Precision Calculator (APC)
 * Name  : Shareef sab
 * Batch : 26001B(084)
 * date : 18/06/2026
 *
 * Description:
 * This project performs arithmetic operations on very large
 * integers using Doubly Linked Lists.
 *
 * Supported Operations:
 *      Addition (+)
 *      Subtraction (-)
 *      Multiplication (x)
 *      Division (/)
 *
 * ==============================================================
 */
#include<stdio.h>
#include"apc.h"
#include<string.h>


int main(int argc,char *argv[])
{
     

    /* Validate Command Line Arguments */
    if(argc == 1)
    {
        printf(RED "[ERROR] No command-line arguments provided.\n" RESET);
        printf(YELLOW "[USAGE] ./a.out <operand_1> <operator> <operand_2>\n" RESET);
        return failure;
    }
    else if(argc < 4)
    {
        printf(RED "[ERROR] Insufficient input arguments.\n" RESET);
        printf(YELLOW "[USAGE] ./a.out <operand_1> <operator> <operand_2>\n" RESET);
        return failure;
    }

    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    Dlist *head_r = NULL;
    Dlist *tail_r = NULL;
    char sign1='+';
    char sign2='+';
    char sign_r='+';
    char opt;

    /* ================= ADDITION ================= */

    if(check_operation_type(argc,argv) == add)
    {    opt='+';
         
        if(read_and_validate_OPD_OPR(argc,argv,&sign1,&sign2) == success)
        { 
            if(insert_operands(&head1,&tail1,argv[1],&head2,&tail2,argv[3]) == success)
            {
                if(execute_operation(&head1,&tail1,&head2,&tail2,&head_r,&tail_r,sign1,sign2,&sign_r,opt,argv)==success)
                {
                  // printf(GREEN "[SUCCESS] Operation completed successfully.\n" RESET);
                }else{
                    printf(RED "[ERROR] Failed to execute the operation.\n" RESET);
                    return failure;
                }
            }
            else
            {
                printf(RED "[ERROR] Failed to insert operands into linked lists.\n" RESET);
                return failure;
            }
        }
        else
        {
            printf(RED "[ERROR] Operand validation failed.\n" RESET);
            return failure;
        }
    }

    /* ================= SUBTRACTION ================= */

    else if(check_operation_type(argc,argv) == subs)
    {    opt='-';
        if(read_and_validate_OPD_OPR(argc,argv,&sign1,&sign2) == success)
        {
            if(insert_operands(&head1,&tail1,argv[1],&head2,&tail2,argv[3]) == success)
            {
                if(execute_operation(&head1,&tail1,&head2,&tail2,&head_r,&tail_r,sign1,sign2,&sign_r,opt,argv)==success)
                {
                    //printf(GREEN "[SUCCESS] Operation completed successfully.\n" RESET);
                }else{
                   printf(RED "[ERROR] Failed to execute the operation.\n" RESET);
                    return failure;
                }
            }
            else
            {
                printf(RED "[ERROR] Failed to insert operands into linked lists.\n" RESET);
                return failure;
            }
        }
        else
        {
            printf(RED "[ERROR] Operand validation failed.\n" RESET);
            return failure;
        }
    }

    /* ================= MULTIPLICATION ================= */

    else if(check_operation_type(argc,argv) == multiply)
    {   opt='x';
        if(read_and_validate_OPD_OPR(argc,argv,&sign1,&sign2) == success)
        {
            if(insert_operands(&head1,&tail1,argv[1], &head2,&tail2,argv[3]) == success)
            {
                 if(execute_operation(&head1,&tail1,&head2,&tail2,&head_r,&tail_r,sign1,sign2,&sign_r,opt,argv)==success)
                {
                    //printf(GREEN "[SUCCESS] Operation completed successfully.\n" RESET);
                }else{
                    printf(RED "[ERROR] Failed to execute the operation.\n" RESET);
                    return failure;
                }
            }
            else
            {
                printf(RED "[ERROR] Failed to insert operands into linked lists.\n" RESET);
                return failure;
            }
        }
        else
        {
            printf(RED "[ERROR] Operand validation failed.\n" RESET);
            return failure;
        }
    }

    /* ================= DIVISION ================= */

    else if(check_operation_type(argc,argv) == division)
    {  opt='/';
        if(read_and_validate_OPD_OPR(argc,argv,&sign1,&sign2) == success)
        {
            if(insert_operands(&head1,&tail1,argv[1], &head2,&tail2,argv[3]) == success)
            {
                if(execute_operation(&head1,&tail1,&head2,&tail2,&head_r,&tail_r,sign1,sign2,&sign_r,opt,argv)==success)
                {
                    //printf(GREEN "[SUCCESS] Operation completed successfully.\n" RESET);
                }else{
                   printf(RED "[ERROR] Failed to execute the operation.\n" RESET);
                    return failure;
                }
            }
            else
            {
                printf(RED "[ERROR] Failed to insert operands into linked lists.\n" RESET);
                return failure;
            }
        }
        else
        {
            printf(RED "[ERROR] Operand validation failed.\n" RESET);
            return failure;
        }
    }

    /* ================= INVALID OPERATOR ================= */

    else
    {
        printf(RED "[ERROR] Unsupported operator '%c'.\n" RESET, argv[2][0]);
        printf(YELLOW "[INFO] Supported operators: +  -  x  /\n" RESET);
        return failure;
    }

    return success;
}

/*
 * ==============================================================
 * Function Name : check_operation_type()
 *
 * Description:
 * Determines the arithmetic operation selected by the user.
 *
 * Parameters:
 *      argc  -> Argument count
 *      argv  -> Command-line arguments
 *
 * Returns:
 *      add
 *      subs
 *      multiply
 *      division
 *      unsupported
 * ==============================================================
 */

OperationType check_operation_type(int argc,char *argv[])
{
    if(argv[2][0] == '+')
    {
        return add;
    }
    else if(argv[2][0] == '-')
    {
        return subs;
    }
    else if(argv[2][0] == 'x'|| argv[2][0] == 'X')
    {
        return multiply;
    }
    else if(argv[2][0] == '/')
    {
        return division;
    }
    else
    {
        return unsupported;
    }
}