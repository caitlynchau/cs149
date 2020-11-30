#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


#include "Node.h"

/**
  Example of linked list initialization in code:
  //First command node (head of list)
  headCommand = (CommandNode*)malloc(sizeof(CommandNode));
  CreateCommandNode(headCommand, command, index, NULL);
  .....
  //Later command nodes
  nextCommand1 = (CommandNode*)malloc(sizeof(CommandNode));
  CreateCommandNode(nextCommand1, command, index, NULL);
  InsertCommandAfter(headCommand, nextCommand1);
**/


//create a new command node. usually nextCmd can be NULL and function InsertCommandAfter can be called to insert after head node.
void CreateNewNode(Node* thisNode, char * input, Node* nextCmd) {
  //this is useful if you store a string (char *): strcpy(thisNode->command, cmd);
  thisNode->input = input;
  thisNode->next = nextCmd;
  return;
}

//insert node newNode after thisNode 
void InsertNodeAfter(Node* thisNode, Node* newNode) {
  Node * tmpNext = NULL;

  tmpNext = thisNode->next;
  thisNode->next = newNode;
  newNode->next = tmpNext;
  return;
}

//get next command node in linked list
Node * GetNextNode(Node* thisNode) {
  return thisNode->next;
}

void FreeNodes(Node * head) {
  Node * temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }

}