#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interval_get.h"
#include "libgenbank.h"

char** get_CDS_sequence(int,int**,char*);
char* sequence_get(char*);
int main(){
  int num;
  char** ids=get_id("/root/workspace/Linuxhomework/sequence (5).gb",&num);
  for(int i=0;i<=num-1;i++){
    printf("%s\n",*(ids+i));
  }
    printf("+++++++++++\n");
  int** intervals=interval_get("/root/workspace/Linuxhomework/sequence (5).gb","CDS");
  for(int i=0;i<=num-1;i++){
    printf("%d   %d   %d\n",*(*(intervals+i)),*(*(intervals+i)+1),*(*(intervals+i)+2));
  }
    printf("+++++++++++\n");
  char* origin_sequence=sequence_get("/root/workspace/Linuxhomework/sequence (5).gb");
  printf("%s\n",origin_sequence);
  printf("+++++++++++\n");
  char** sequence=get_CDS_sequence(num,intervals,origin_sequence);
  for(int i=0;i<=num-1;i++){
    printf("第%d个CDS对应序列为%s\n",i+1,*(sequence+i));
  }
}
