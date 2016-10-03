#include "rest_functions.h"
#include "edges_nodes.h"
#include "errors.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int reverseString(char * str) 
{
    char temp;
    
    int i ;
    int returnValue =-1;
    int len = strlen(str)-1;
    int k = len ;
    
    if(str == NULL)
        returnValue = 1;
    else
    {
        for( i=0 ; i < len ; i++ )
        {
            /*swap*/
            temp = str[k];              
            str[k] = str[i];
            str[i] = temp ;
            k--;
            
            if(k == (len / 2))          //"scan" half the string
	    {
                returnValue = SUCCESS ;
                break;
	    }
        }
    }
    return returnValue ;
}

int deleteStringMatrix(char ** stringMatrix)
{
    int i ;
    int returnValue =-1;
    
    
    if(stringMatrix == NULL)
    {
        returnValue = 1 ;
    }
    else
    {
        for(i=0;i<N;i++)
        {
            if(stringMatrix[i] != NULL)
                free(stringMatrix[i]);
        }
        if(stringMatrix != NULL)  //perito
            free(stringMatrix);
        returnValue = SUCCESS ;
    }
    return returnValue ;
}

int orderStringMatrix(char ** stringMatrix)
{
    /*bubblesort based*/
    int i,j;
    int returnValue = -1 ;
    int flag =0;
    char * temp ;
    if(stringMatrix == NULL)
        returnValue = 1 ;
    else
    {
        for(i=0;i<N-1;i++)
        {
            for(j=0;j<N-i;j++)
            {
                if(j+1 == N)
                    break;
                
                if(stringMatrix[j] == NULL || stringMatrix[j+1] == NULL)        //if NULL do not continue 
                {
                    flag = 1;
                    break ;
                }
                //printf("\n%s\n",stringMatrix[j]);
                if(strcmp(stringMatrix[j],stringMatrix[j+1])>0)                 
                {
                    temp = stringMatrix[j];
                    stringMatrix[j] = stringMatrix[j+1] ;
                    stringMatrix[j+1] = temp ;
                }
            }
            if(flag == 1)
                break;
        }
        returnValue = SUCCESS ;
    }
    return returnValue;
}