#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 结构类型cds_stru的：用于存储CDS信息的结构类型；
typedef struct {
    char id[20];
    char cdsSeq[2000];
    /* other declarations */
} cds_stru;


char** get_id(char* gb_filename, int* count); // 获取CDS的protein_id

int** get_interval(char* file, char* name); // 获取CDS的前后端点
char* get_genSeq(char* file_name); // 获取CDS所在基因组的完整序列

char** get_cdsSeq(int CDS_num, int** intervals, char* origin_sequence); // 获取CDS的sequence

void input_cds_stru(char** input_id, char** input_seq, cds_stru* p_stru, int num); // 将id, seq等信息输入cds_stru
void print_cds_stru(const cds_stru* p_stru); // 打印一个cds_stru的信息
void fasta_prod(cds_stru* p_stru);  // 输出成 .fasta 文件