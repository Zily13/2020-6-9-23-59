#include "libgenbank.h"

// 函数fasta_prod：每次输出一个cds_stru到指定的FASTA文件中；
void fasta_prod(cds_stru* p_stru) {
    FILE* output = fopen("test.fasta", "a");

    fputs(">", output);
    fputs(p_stru->id, output);
    fputs("\n", output);
    fputs(p_stru->cdsSeq, output);
    fputs("\n", output);

    fclose(output);
   
}

// 函数input_cds_stru：每次为一个cds_stru添加输入信息；
void input_cds_stru(char** input_id, char** input_seq, cds_stru* p_stru, int num){
    strcpy(p_stru->id , *(input_id+num));  // 输入id
    strcpy(p_stru->cdsSeq, *(input_seq + num));  // 输入sequence
}

// 函数 print_cds_stru：每次将一个cds_stru的信息打印到屏幕上；
void print_cds_stru(const cds_stru* p_stru) {
    printf(">%s\n", p_stru->id);
    printf("%s\n", p_stru->cdsSeq);
}

