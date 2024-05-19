#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>



//Intro Paragraph: In this program, I used linked list to implement the matrix functions
//I used input files to load the matrix with its value, rows and columns
//I then implemented the set matrix function which set a given spot to the value based on its row and columns
//I then implemented the matrix addition and multiplication functions
//Partners: mcasper3, wshen15

//Method to load the matrix
sp_tuples * load_tuples(char* input_file)
{
    sp_tuples *list=(sp_tuples*)malloc(sizeof(sp_tuples));
    FILE *file=fopen(input_file, "r");   //read the input file
    fscanf(file, "%d %d", &list->m, &list->n); //get the m and n
    fgetc(file);
    list->nz=0;                             //set the nz value to 0
    list->tuples_head=NULL;                 //set the matrix head to null at the start
    int row, col;   
    double x;
    while(fscanf(file, "%d %d %lf", &row, &col, &x)!=EOF)   
    {
        set_tuples(list, row, col, x);      //set each value for each spot
    }
    fclose(file);                           //close the file
    return list;
}


//get value function
double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *temp=mat_t->tuples_head;    //set a temp node to the head of the matrix
    while(temp!=NULL)
    {
        if(temp->row==row&&temp->col==col)
        {
            return temp->value;                 //return the value
        }
        temp=temp->next;                        //move the temp node until find the right spot
    }

    return 0;
}


//Method to set the matrix for a given spot and value
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node *temp=mat_t->tuples_head;    //get a temp node
    if(value==0.0)                              //cases where given value is 0
    {
        if(temp==NULL)
        {
            return;                             //do nothing if the head is null
        }
        else
        {

            if(temp->row==row&&temp->col==col)  
            {
                mat_t->tuples_head=temp->next;  //remove the node at the spot and connect previous node to the next one
                free(temp);
                mat_t->nz--;                    //decrement non zero counter
                return;
            }
            else
            {
                sp_tuples_node *prev=mat_t->tuples_head;    //set the previous node to the head
                temp=temp->next;                            //move on to the next node
                while(temp!=NULL)
                {
                    if(temp->row==row&&temp->col==col)
                    {
                        prev->next=temp->next;
                        free(temp);
                        temp=prev->next;
                        mat_t->nz--;                        //move the temp until the right spot and then free the node at the spot then connect prevous node to next
                        return;
                    }
                    prev=temp;                              //move on to the next node
                    temp=temp->next;
                }
            }
        }
    }
    else        //cases where value doens't equal 0
    {
        if(row<0||row>mat_t->m||col<0||col>mat_t->n)
        {
            return;         //do nothing if given row and col is out of bounds
        }
        sp_tuples_node *prev=temp;  //set a previous node
        sp_tuples_node *node=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));  
        node->value=value;
        node->row=row;
        node->col=col;              //create a new node with given row, col, and value
        if(temp==NULL)
        {
            mat_t->tuples_head=node;
            mat_t->nz++;
            node->next=NULL;
            return;                 //set the head to the node if head is null, and set the next node to null
        }
        else
        {
            if(temp->row==row&&temp->col==col)
            {
                double val=temp->value;
                temp->value=value;
                if(val==0.0)
                {
                    mat_t->nz++;
                }
                free(node);
                return;         //if at the right spot, switch the value, and free the memory 
            }
            if(temp->row>row||(temp->row==row&&temp->col>col))
            {
                node->next=temp;
                mat_t->tuples_head=node;
                mat_t->nz++;
                return;
            }
            temp=temp->next;    //move on to the next node.
            while(temp!=NULL)
            {
                if(temp->row==row&&temp->col==col)
                {
                    double val=temp->value;
                    temp->value=value;
                    if(val==0.0)
                    {
                        mat_t->nz++;
                    }
                    free(node);
                    return;     //if at the right spot, switch the value and free the memory
                }

                if(temp->row>row||(temp->row==row&&temp->col>col))
                {
                    node->next=temp;
                    prev->next=node;
                    mat_t->nz++;
                    return;
                }
                prev=temp;
                temp=temp->next;    //move on to the next nodes
            }
            node->next=NULL;    //when done, set the next node to null
            prev->next=node;    //set the current node to node
            mat_t->nz++;        //update the nz value 
            return;
        }
    }
    return;
}


//method to save the matrix
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE *file=fopen(file_name, "w");
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);
    sp_tuples_node *temp=mat_t->tuples_head;
    while(temp!=NULL)
    {
        fprintf(file, "%d %d %lf\n", temp->row, temp->col, temp->value);
        temp=temp->next;    //print out the matrix elements until its done
    }
    fclose(file);
	return;
}


//Matrix addition function
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    if(matA->m!=matB->m||matA->n!=matB->n)
    {
        return NULL;    //if m and n don't match, return null
    }
    else
    {
        sp_tuples *matC=(sp_tuples*)malloc(sizeof(sp_tuples));  //create an answer matrix
        matC->m=matA->m;
        matC->n=matA->n;
        matC->nz=0;
        sp_tuples_node *A=matA->tuples_head;
        sp_tuples_node *B=matB->tuples_head;    //get the two head nodes
        while(A!=NULL)
        {
            set_tuples(matC, A->row, A->col, A->value);
            A=A->next;  //put matrix A in the answer matrix first
        }
        while(B!=NULL)
        {
            set_tuples(matC, B->row, B->col, B->value+gv_tuples(matC, B->row, B->col));
            B=B->next;  //then add the value of the B matrix to the answer matrix
        }
        return matC;    //return the answer matrix
    }
}


//function to matrix multiplications
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    if(matA->n!=matB->m)
    {
        return NULL;    //if m and n don't match, return null
    }
    else
    {
        sp_tuples *matC=(sp_tuples*)malloc(sizeof(sp_tuples));  //else create a matrix C
        matC->m=matA->m;
        matC->n=matB->n;
        matC->nz=0;
        sp_tuples_node *A=matA->tuples_head;
        sp_tuples_node *B=matB->tuples_head;
        while(A!=NULL)
        {
            while(B!=NULL)
            {
                if(B->row==A->col)
                {
                    set_tuples(matC, A->row, B->col, (B->value*A->value)+gv_tuples(matC, A->row, B->col));  //update values
                    
                }
                    B=B->next;                      //move on the the next B node
            }
            A=A->next;      //move on to the next A node
            B=matB->tuples_head;    //Reset B node
        }
        return matC;    //return the answer matrix
    }
}


//get rid of the matrix and free the memory
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node *temp= mat_t->tuples_head;
    while(temp!=NULL)
    {
        sp_tuples_node *node=temp;
        temp=temp->next;
        free(node); //free each node
    }
    free(mat_t);//free the matrix
    return;
}  






