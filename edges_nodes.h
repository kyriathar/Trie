#ifndef EDGES_H
#define	EDGES_H

#define N 5

typedef struct Edge Edge ;
typedef struct TrieNode TrieNode ;
typedef struct Father Father ;


/*AKMH*/
struct Edge{
    char s ;
    TrieNode * trieNode_ptr;
};

/*PATERAS*/
struct Father{
    Edge * edge ;
    TrieNode * trieNode_ptr ;
};

/*KOMVOS*/
struct TrieNode{
    Edge edges[27];                 
    TrieNode * frequentNodes[N];
    Father father ;
    int freq_no ;
};


int initializeEdge(Edge * edge);
int setCharToEdge(Edge * edge , char s);
int setTrieNodeToEdge(Edge * edge , TrieNode * trieNode);
////////////////////////////////////////////////////////////////////////////////
int initializeFather(Father * father);
////////////////////////////////////////////////////////////////////////////////
int initializeTrieNode(TrieNode * trieNode);
int setFatherInTrieNode(TrieNode * trieNode ,TrieNode * father , Edge * motherEdge);
////////////////////////////////////////////////////////////////////////////////


#endif	/* TRIE_H */

