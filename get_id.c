#include <string.h>
#include <stdio.h>
#include <malloc.h>

char** get_id(char * gb_filename){  //字符串gb_filename是等待被转化为FASTA格式的genbank文件的文件名
  int maxnum_id=500;  //从文件中提取到的id的最大数量，数值上应该和CDS_info结构体数量一致
  FILE* genbank=fopen(gb_filename,"r"); 
  char** protein_id=(char**)malloc(maxnum_id*sizeof(char*));  //protein_id是存储提取出的指向id的指针的存储空间的首地址
  char temp[50];  //temp是暂时存储protein_id的字符串
  char eachline[500];  //eachline存储fgets()函数得到的文件的一行
  int i=0;
  int j=0;
  int id_num=0;  //id_num用于计算protein_id中已经有的id数量
  while(fgets(eachline,1000,genbank)!=NULL){
    i=0;
    j=0;
    if(eachline[0]=='O' && eachline[1]=='R' && eachline[2]=='I' && eachline[3]=='G'){
      break;
    }
    while(eachline[i]=='\t' || eachline[i]==' '){
      i++;
    }
    if (eachline[i]=='/' && eachline[i+1]=='p' && eachline[i+2]=='r' && eachline[i+3]=='o' && eachline[i+4]=='t' && eachline[i+5]=='e'){
      i=i+13;
      while(eachline[i]!='\"'){
	temp[j]=eachline[i];
	i++;
	j++;
      }
      temp[j]='\0';
      if (id_num<=maxnum_id){
	*(protein_id+id_num)=(char*)malloc(50*sizeof(char));
	strcpy(*(protein_id+id_num),temp);
	id_num+=1;
      }
      else{
	protein_id=(char**)realloc(protein_id,(maxnum_id+500)*sizeof(char*));
	protein_id+=500;
	*(protein_id+id_num)=(char*)malloc(50*sizeof(char));
	strcpy(*(protein_id+id_num),temp);
	id_num+=1;
      }
      continue;
    }
    else{
      continue;
    }
  }
  return protein_id;
}

