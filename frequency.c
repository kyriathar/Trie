#include "frequency.h"
#include "errors.h"


#include <stdio.h>
#include <stdlib.h>

int isTheSame( TrieNode * predecessor, TrieNode * child )
{
    int i ;
    int returnValue =-1;
    
    if( predecessor == NULL || child == NULL )
    {
        returnValue = 1 ;
    }
    else
    {   
        for( i=0 ; i<N ; i++ )     
        {
            if((predecessor->frequentNodes[i]) != NULL)
            {
                if( predecessor->frequentNodes[i] == child )        //check by memory adress if it is the same Node
                {
                    returnValue = SUCCESS ;
                    break ;
                }
            }
        }
    }
    return returnValue ;
}



int findLessAndReplace( TrieNode * predecessor, TrieNode * child )
{
    int i ;
    int min = MIN_VALUE ;
    int min_pos = -1 ;
    int returnValue = -1 ;
    
    
    if( predecessor == NULL || child == NULL )
    {
        returnValue = 1 ;
    }
    else
    {   
        if(child->freq_no == -1  )
        {
            printf("CHILD : ERROR @ FREQUENT\n");
            exit(-1);
        }
        
        if(isTheSame(predecessor,child) == 0)
        {
            returnValue = 2 ;
        }
        else
        {
            for( i=0 ; i<N ; i++ )      //find min
            {
                 if((predecessor->frequentNodes[i]) == NULL  )      
                 {
                     predecessor->frequentNodes[i] = child ;
                     returnValue = SUCCESS ;
                     break ;
                 } 

                if((predecessor->frequentNodes[i])->freq_no == -1  )
                {
                    printf("PREDECESSOR : ERROR @ FREQUENT\n");
                    exit(-1);
                }

                if((predecessor->frequentNodes[i])->freq_no < min)
                {
                    min = (predecessor->frequentNodes[i])->freq_no ;            //will find min value and...
                    min_pos = i ;                                               //... its position
                }
            }
            if(child->freq_no > min && child != predecessor->frequentNodes[min_pos] )
            {
                predecessor->frequentNodes[min_pos] =  child ;                  //replace
                returnValue = SUCCESS ;
            }
        }
    }
    return returnValue ;
}

