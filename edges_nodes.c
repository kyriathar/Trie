#include "edges_nodes.h"
#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

extern int my_errorno;

int initializeEdge(Edge * edge)
{
    int returnValue =-1 ;
    
    if(edge == NULL) 
    {
        returnValue = 1;
    } 
    else
    {
        edge-> s = '-';
        edge-> trieNode_ptr = NULL ;
        returnValue = SUCCESS;    // SUCCESS
    }
    return returnValue ;
}

int setCharToEdge(Edge * edge , char s)
{
    int returnValue =-1 ;
    
    if(edge == NULL)
        returnValue = 1 ;
    else
    {
        edge-> s = s;
        returnValue = SUCCESS;    // SUCCESS
    }
    return returnValue ;
}

int setTrieNodeToEdge(Edge * edge , TrieNode * trieNode)
{
    int returnValue =-1 ;
    
    if(edge == NULL)
        returnValue = 1 ;
    else
    {
        if(trieNode == NULL)
            returnValue = 2 ;
        else
        {
            edge->trieNode_ptr = trieNode ;
            returnValue = SUCCESS;    // SUCCESS
        }
    }
    return returnValue ;
}
////////////////////////////////////////////////////////////////////////////////
int initializeFather(Father * father)
{
    int returnValue = -1 ;
    
    if(father == NULL)
        returnValue = 1;
    else
    {
        father->edge = NULL;
        father->trieNode_ptr = NULL;
    }
    return returnValue ;
}
////////////////////////////////////////////////////////////////////////////////
int initializeTrieNode(TrieNode * trieNode)
{
    int i ;
    int returnValue = -1 ;
    
    if(trieNode == NULL)
        returnValue = 1;
    else
    {
        for( i=0 ; i<=26 ; i++ )
        {
            initializeEdge(&(trieNode->edges[i]));
        }
        for( i=0 ; i<N ; i++ )
        {
            trieNode->frequentNodes[i] = NULL ;
        }
        initializeFather(&(trieNode->father));
        trieNode->freq_no = -1;
        returnValue = SUCCESS ;
    }
    return returnValue ;
}

int setFatherInTrieNode(TrieNode * trieNode ,TrieNode * father , Edge * motherEdge)
{
    int returnValue = -1 ;
    
    if(trieNode == NULL)
        returnValue = 1;
    else
    {
        trieNode->father.edge = motherEdge ;            
        trieNode->father.trieNode_ptr = father ;
        returnValue = SUCCESS ;
    }
    return returnValue ;
}
