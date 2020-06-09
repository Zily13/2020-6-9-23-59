#include "libgenbank.h"

// ����fasta_prod��ÿ�����һ��cds_stru��ָ����FASTA�ļ��У�
void fasta_prod(cds_stru* p_stru) {
    FILE* output = fopen("test.fasta", "a");

    fputs(">", output);
    fputs(p_stru->id, output);
    fputs("\n", output);
    fputs(p_stru->cdsSeq, output);
    fputs("\n", output);

    fclose(output);
   
}

// ����input_cds_stru��ÿ��Ϊһ��cds_stru���������Ϣ��
void input_cds_stru(char** input_id, char** input_seq, cds_stru* p_stru, int num){
    strcpy(p_stru->id , *(input_id+num));  // ����id
    strcpy(p_stru->cdsSeq, *(input_seq + num));  // ����sequence
}

// ���� print_cds_stru��ÿ�ν�һ��cds_stru����Ϣ��ӡ����Ļ�ϣ�
void print_cds_stru(const cds_stru* p_stru) {
    printf(">%s\n", p_stru->id);
    printf("%s\n", p_stru->cdsSeq);
}

