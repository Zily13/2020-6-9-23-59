#include <string.h>
#include <stdio.h>
#include <malloc.h>

char** get_CDS_sequence(int CDS_num,int** intervals,char* origin_sequence){   //id_num是CDS的个数，intervals是存放CDS区间的二维数组
  char** CDS_sequence=(char**)malloc(CDS_num*sizeof(char*));
  int length;  //length是一个CDS对应序列的长度
  int pointer;
  for(int i=0;i<=CDS_num-1;i++){
    length=0;
    pointer=0;
    if (*(*(intervals+i))<=0){
      for (int j=0;j<=(-1)-(*(*(intervals+i)));j++){
	length+=*(*(intervals+i)+2*j+2)-*(*(intervals+i)+2*j+1)+2;
      }
      *(CDS_sequence+i)=(char*)malloc(length*sizeof(char));
      for (int j=0;j<=(-1)-(*(*(intervals+i)));j++){
	for (int k=*(*(intervals+i)+2*j+1);k<=*(*(intervals+i)+2*j+2);k++){
	  *(*(CDS_sequence+i)+pointer)=*(origin_sequence+k-1);
	  pointer++;
	}
	*(*(CDS_sequence+i)+pointer)=';';
	pointer++;
      }
      *(*(CDS_sequence+i)+length)='\0';
      for(int m=0;m<=length-1;i++){
	switch (*(*(CDS_sequence+i)+m))
        {
	case 'a': *(*(CDS_sequence+i)+m)='t';break;
        case 't': *(*(CDS_sequence+i)+m)='a';break;
        case 'c': *(*(CDS_sequence+i)+m)='g';break;
        case 'g': *(*(CDS_sequence+i)+m)='c';break;
        }
      }
    }
    else{
      for (int j=0;j<=(-1)+(*(*(intervals+i)));j++){
	length+=*(*(intervals+i)+2*j+2)-*(*(intervals+i)+2*j+1)+2;
      }
      *(CDS_sequence+i)=(char*)malloc(length*sizeof(char));
      for (int j=0;j<=(-1)+(*(*(intervals+i)));j++){
	for (int k=*(*(intervals+i)+2*j+1);k<=*(*(intervals+i)+2*j+2);k++){
	  *(*(CDS_sequence+i)+pointer)=*(origin_sequence+k-1);
	  pointer++;
	}
	*(*(CDS_sequence+i)+pointer)=';';
      }
      *(*(CDS_sequence+i)+length)='\0';
    }
  }
  return CDS_sequence;
}
