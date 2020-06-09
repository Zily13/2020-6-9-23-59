#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libgenbank.h"

int main(){
  int num;
  char** protein_id=get_id("/root/workspace/sequence.gb",&num);
  for(int i=0;i<=num-1;i++){
    printf("%s\n",*(protein_id+i));
  }
}
