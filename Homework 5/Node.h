#ifndef NODE_H
#define NODE_H

typedef struct node_struct {
   char * input;
   struct node_struct* next;
} Node;

/* function prototypes */

void CreateNewNode(Node* thisNode, char * input, Node* nextCmd);
void InsertNodeAfter(Node* thisNode, Node* newNode);
Node* GetNextNode(Node* thisNode);
void FreeNodes(Node * node);

#endif