#include "libgenbank.h"

int main() {
    int cds_count;  // 用于保存CDS的总数目

    //  获取input_id (一个保存有每一个CDS的protein_id的二级指针)：protein_id
    char** protein_id;  
    protein_id = get_id("./sequence_test.gb", &cds_count);
    
    // 获取cds的前后端点(一个保存有每一个CDS的前后端点的二级指针)：interval
    int** interval;
    interval = get_interval("./sequence_test.gb", "CDS");

    // 获取基因组的完整序列(一个保存有CDS所在基因组的完整序列的字符指针)：genSeq
    char* genSeq;
    genSeq = get_genSeq( "./sequence_test.gb");

    // 获取input_seq (一个保存有每一个CDS的sequence的二级指针)：sequence
    char** sequence;
    sequence = get_cdsSeq(cds_count, interval, genSeq);

    // 为cds_count个cds_stru申请动态内存：
    cds_stru* p_cds_stru;
    p_cds_stru = (cds_stru*)malloc(cds_count * (sizeof(cds_stru)));
    if (p_cds_stru == NULL) { printf("Out of memory!\n"); exit(1); }

    // 逐一为每个cds_stru添加protein_id，sequence等信息：
    int num = 0;  // 编号从0开始
    for (num; num < cds_count; num++) {
        input_cds_stru(protein_id, sequence,p_cds_stru+num, num); // 将信息输入cds_stru
        // print_cds_stru(p_cds_stru + num);  // 打印当前cds_stru的信息
        
        fasta_prod(p_cds_stru + num);  // 输出成“test.fasta”文件
    }

    return 0;
}