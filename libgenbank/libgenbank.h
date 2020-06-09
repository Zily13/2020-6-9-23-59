#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// �ṹ����cds_stru�ģ����ڴ洢CDS��Ϣ�Ľṹ���ͣ�
typedef struct {
    char id[20];
    char cdsSeq[2000];
    /* other declarations */
} cds_stru;


char** get_id(char* gb_filename, int* count); // ��ȡCDS��protein_id

int** get_interval(char* file, char* name); // ��ȡCDS��ǰ��˵�
char* get_genSeq(char* file_name); // ��ȡCDS���ڻ��������������

char** get_cdsSeq(int CDS_num, int** intervals, char* origin_sequence); // ��ȡCDS��sequence

void input_cds_stru(char** input_id, char** input_seq, cds_stru* p_stru, int num); // ��id, seq����Ϣ����cds_stru
void print_cds_stru(const cds_stru* p_stru); // ��ӡһ��cds_stru����Ϣ
void fasta_prod(cds_stru* p_stru);  // ����� .fasta �ļ�