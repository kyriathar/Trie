#ifndef TRIE_H
#define	TRIE_H

#include "edges_nodes.h"

typedef struct MotherTreeNode MotherTreeNode ;

struct MotherTreeNode{
    TrieNode * first ;
    //might need extra info 
};

int initializeMotherTreeNode(MotherTreeNode * motherTreeNode);

int addToMotherTreeNode(MotherTreeNode * motherTreeNode ,char * word);
TrieNode * addToMotherTreeNodeRec(TrieNode * trieNode,TrieNode * father,Edge * motherEdge,char * word);

void find(MotherTreeNode * motherTreeNode ,char *** stringMatrix,char * word );
void findRec(TrieNode * trieNode,TrieNode * father,char *** stringMatrix, char * word);

int destroyMotherTree(MotherTreeNode * motherTreeNode);
void destroyMotherTreeRec(TrieNode * trieNode);

/*FOR DEBUG*/
void printMotherTreeNode(MotherTreeNode * motherTreeNode);
void printTrieNode(TrieNode * trieNode,int depth);


#endif	/* TRIE_H */

// DESTROY