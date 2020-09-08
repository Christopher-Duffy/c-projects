#include<stdio.h>
struct SLLNode{
  int data;
  struct SLLNode* next;
};

int main(void){
  struct SLLNode* head = new SLLNode();
  struct SLLNode* n = head;
  for(int i=0; i<5; i++){
      n->data = i*i;
      n->next = new SLLNode();
      n = n->next;
  }
  return 0;
}
