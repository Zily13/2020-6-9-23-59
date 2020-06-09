#include "libgenbank.h"

int main() {
    int cds_count;  // ���ڱ���CDS������Ŀ

    //  ��ȡinput_id (һ��������ÿһ��CDS��protein_id�Ķ���ָ��)��protein_id
    char** protein_id;  
    protein_id = get_id("./sequence_test.gb", &cds_count);
    
    // ��ȡcds��ǰ��˵�(һ��������ÿһ��CDS��ǰ��˵�Ķ���ָ��)��interval
    int** interval;
    interval = get_interval("./sequence_test.gb", "CDS");

    // ��ȡ���������������(һ��������CDS���ڻ�������������е��ַ�ָ��)��genSeq
    char* genSeq;
    genSeq = get_genSeq( "./sequence_test.gb");

    // ��ȡinput_seq (һ��������ÿһ��CDS��sequence�Ķ���ָ��)��sequence
    char** sequence;
    sequence = get_cdsSeq(cds_count, interval, genSeq);

    // Ϊcds_count��cds_stru���붯̬�ڴ棺
    cds_stru* p_cds_stru;
    p_cds_stru = (cds_stru*)malloc(cds_count * (sizeof(cds_stru)));
    if (p_cds_stru == NULL) { printf("Out of memory!\n"); exit(1); }

    // ��һΪÿ��cds_stru���protein_id��sequence����Ϣ��
    int num = 0;  // ��Ŵ�0��ʼ
    for (num; num < cds_count; num++) {
        input_cds_stru(protein_id, sequence,p_cds_stru+num, num); // ����Ϣ����cds_stru
        // print_cds_stru(p_cds_stru + num);  // ��ӡ��ǰcds_stru����Ϣ
        
        fasta_prod(p_cds_stru + num);  // ����ɡ�test.fasta���ļ�
    }

    return 0;
}