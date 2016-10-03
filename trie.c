#include "trie.h"
#include "edges_nodes.h"
#include "errors.h"
#include "frequency.h"
#include "rest_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int error_code;

// void printTrieError_code() {
    
// }

int initializeMotherTreeNode(MotherTreeNode * motherTreeNode)
{
    int returnValue =-1;
    
    if(motherTreeNode == NULL)
        returnValue = 1;
    else
    {
        motherTreeNode->first = NULL ;
        returnValue = SUCCESS ;
    }
    return returnValue ;
}

int addToMotherTreeNode(MotherTreeNode * motherTreeNode ,char * word)
{
    int returnValue =-1;
    
    if(motherTreeNode == NULL)
        returnValue = 1;
    else
    {
        if(word == NULL)
            returnValue = 2;
        else
        {
            motherTreeNode->first = addToMotherTreeNodeRec(motherTreeNode->first ,NULL,NULL, word);
            returnValue = SUCCESS ;
        }
    }
    return returnValue ;
}

TrieNode * addToMotherTreeNodeRec(TrieNode * trieNode,TrieNode * father,Edge * motherEdge,char * word)
{
    
    if(motherEdge!=NULL && motherEdge->s == '@')
    {
        TrieNode * temp =NULL;
        
        if(trieNode == NULL)        //leaf does not exit
        {
            int i;
            trieNode =(TrieNode *) malloc(sizeof(TrieNode));
            initializeTrieNode(trieNode);
            setFatherInTrieNode(trieNode , father,motherEdge);
            trieNode->freq_no = 0;
            
            
            temp = trieNode->father.trieNode_ptr ;
            
            
            while( temp != NULL )               //Update every father's Node frequency table if there is a NULL spot
            {
                for( i=0 ; i<N ; i++ )      
                {
                    if(temp->frequentNodes[i] == NULL)
                    {
                        temp->frequentNodes[i] = trieNode ;
                        break;
                    }
                }
                temp = temp->father.trieNode_ptr ;
            }
        }
        else
        {
            //printf("auksisa tin sixnotita ! \n");
            trieNode->freq_no ++;
            temp = trieNode->father.trieNode_ptr ;
            while(temp != NULL)
            {   
                findLessAndReplace(temp,trieNode);          //Update every father's Node frequency table by comparing frequencies
                temp = temp->father.trieNode_ptr ;
            }
        }
    }
    else if( (*word) == '\0' )                                        // reached '\0'
    {
        if(trieNode == NULL)
        {
            trieNode =(TrieNode *) malloc(sizeof(TrieNode));
            initializeTrieNode(trieNode);
            setFatherInTrieNode(trieNode , father,motherEdge);
        }
        
        setCharToEdge(&(trieNode->edges[26]),'@');
        
        trieNode->edges[26].trieNode_ptr = addToMotherTreeNodeRec (trieNode->edges[26].trieNode_ptr,trieNode,&(trieNode->edges[26]),NULL);
        //return NULL;
    }
    else if(trieNode == NULL)
    {
        trieNode =(TrieNode *) malloc(sizeof(TrieNode));        //Node creation
        initializeTrieNode(trieNode);
        setCharToEdge(&(trieNode->edges[word[0]-'a']),word[0]);
        setFatherInTrieNode(trieNode , father,motherEdge);
        trieNode->edges[word[0]-'a'].trieNode_ptr = addToMotherTreeNodeRec (trieNode->edges[word[0]-'a'].trieNode_ptr,trieNode,&(trieNode->edges[word[0]-'a']),word+1);
    }
    else if(trieNode != NULL)
    {
        /*Node-letter exists sto just move on...*/
        setCharToEdge(&(trieNode->edges[word[0]-'a']),word[0]);     //just overwrites
        trieNode->edges[word[0]-'a'].trieNode_ptr = addToMotherTreeNodeRec (trieNode->edges[word[0]-'a'].trieNode_ptr,trieNode,&(trieNode->edges[word[0]-'a']),word+1);
    }
        
    return trieNode ;
}

//Prints were just for debugging but can be used if one wants to check the tree...
void printMotherTreeNode(MotherTreeNode * motherTreeNode)
{
    printTrieNode(motherTreeNode->first,0);
    return ;
}

void printTrieNode(TrieNode * trieNode,int depth)
{
    int i ;
    int j ;
    
    if(trieNode == NULL)
        return;
    
    for(i=0;i<=25;i++)
    {
        if(trieNode->edges[i].s != '-')
        {    
            for(j=0;j<=depth;j++)
            {
                printf("   ");
            }
            printf("position = %d %c \n",i,trieNode->edges[i].s);
        }
        printTrieNode(trieNode->edges[i].trieNode_ptr,depth+1);
    }
}

void find(MotherTreeNode * motherTreeNode , char *** stringMatrix ,char * word )
{
    if((*word) != '\0')
        findRec(motherTreeNode->first,NULL,stringMatrix,word);
}

void findRec(TrieNode * trieNode,TrieNode * father, char *** stringMatrix ,char * word)
{
    if(trieNode->father.edge != NULL && trieNode->father.edge->s=='@')
    {
        //printf("H suxnotita tis leksis einai : %d\n",trieNode->freq_no);
    }
    else if( (*word) == '\0' )
    {   
        int i ;
        int j ;
        int k ;
        int buffer_lenght = -1 ;
        TrieNode * temp =NULL;
        temp = trieNode ;
        char buffer[128];
        char * temp_string =NULL ;
        
        memset(buffer,'\0',128);
        
        *stringMatrix =(char **) malloc(N*sizeof(char *));
        if(*stringMatrix == NULL)
        {
            printf("findRec : malloc1 failed !\n");
            return ;
        }
        
        for(k=0;k<N;k++)
        {
            (*stringMatrix)[k] = NULL;
        }
        
        for(i=0 ;i<N ;i++)                      //for each leafNode in the frequentNodes array
        {
            if(trieNode->frequentNodes[i] != NULL)
            {
                j=0;
                temp = trieNode->frequentNodes[i] ;
                
               
                while(temp->father.edge!= NULL)
                {   
                    if(temp->father.edge->s != '@')
                    {
                        buffer[j] = temp->father.edge->s ;
                        j++;
                    }
                    temp = temp->father.trieNode_ptr ;
                }
                reverseString(buffer);  //we have our correct buffer after this 
                
                buffer_lenght = strlen(buffer);
                temp_string = (char* )malloc((buffer_lenght+1)*sizeof(char));
                if(temp_string == NULL)
                {
                    printf("findRec : malloc2 failed !\n");
                    return ;
                }
                strcpy(temp_string,buffer);
                
                (*stringMatrix)[i] = temp_string ;
                
                
                memset(buffer,'\0',128);
            }
        }
        orderStringMatrix(*stringMatrix);           //stringMatrix was put into alphabetical order
        //findRec (trieNode->edges[26].trieNode_ptr,trieNode,NULL);
    }
    else if( trieNode == NULL || trieNode->edges[word[0]-'a'].s == '-' )
    {
        //word doesnt exit
        //printf("\nword not found ! \n");
    }
    else if( trieNode != NULL )
    {
        findRec (trieNode->edges[word[0]-'a'].trieNode_ptr,trieNode,stringMatrix,word+1);
    }
    return ;
}

int destroyMotherTree(MotherTreeNode * motherTreeNode)
{
    int returnValue =-1;
    
    if(motherTreeNode == NULL)
        returnValue = 1;
    else
    {
        destroyMotherTreeRec(motherTreeNode->first);
        returnValue = SUCCESS ;
    }
    return returnValue ;
}

void destroyMotherTreeRec(TrieNode * trieNode)
{
    int i;
    
    if(trieNode == NULL)
    {
        return ;
    }
    else if(trieNode != NULL)
    {
        for(i=0;i<27;i++)
        {
            destroyMotherTreeRec(trieNode->edges[i].trieNode_ptr);
        }
    }
    free(trieNode);
    return;
}