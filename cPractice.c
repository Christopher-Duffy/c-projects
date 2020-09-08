#include<stdio.h>
void prob0a(void){
  int SIZE = 5;
  int *p = NULL;
  int a[SIZE];
  for(p = a;p<a+SIZE;p++){
    *p = (p-a)*(p-a);
  }
  for(p = a;p<a+SIZE;p++){
    printf("%d ",*p);
  }
  printf("\n");
  for(p = a;p<a+SIZE;p++){
    printf("%p ",p);
  }
  printf("\n");
}
void prob0b(void){
  int size = 5;
  char s[size];
  char *p;
  for(p = s;p<s+size;p++){
    *p='a'+p-s;
  }
  for(p = s;p<s+size;p++){
    printf("%c ",*p);
  }
  printf("\n");
  for(p = s;p<s+size;p++){
    printf("%p ",p);
  }
  printf("\n");
}
int main(void){
  printf("C excersizes for Operating Systems Design\n");
  printf("Problem 0-a:\n");
  prob0a();
  printf("Problem 0-b:\n");
  prob0b();
  return 0;
}
