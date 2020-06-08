#include <stdio.h>

// 结构类型cds_stru的：用于存储CDS信息的结构类型；
typedef struct {
    char protein_id[12];
    char translaiton[100];
    /* other declarations */
} cds_stru;

// 函数fasta_prod：用于读取cds_stru输出相应的FASTA文件；
void fasta_prod(cds_stru* p_stru) {
    FILE* output = fopen("test.fasta", "a");

    fputs(">", output);
    fputs(p_stru->protein_id, output);
    fputs("\n", output);
    fputs(p_stru->translaiton, output);
    fputs("\n", output);

    fclose(output);
}

// 函数调用：
int main() {
    cds_stru stru1 = { "AYP74058.1", "MIVEKIAAWLLYPLCLLRCFRCFCCPCEVFLRCLCFPCRTLRRLYRGRMTRIREPGAAKDSRDPLICNSLCPATC" };
    cds_stru stru2 = { "AYP74058.2", "LLRCFRCFCCPCEVFLRCLCFPCRTFRCFCCPCEVFLRCLCFPCRTLRRLYRGRMTRIREPGAAKDSRDPLICNS" };
    
    //printf("stru1.protein_id: %s\n", stru1.protein_id);
   // printf("stru1.translaiton: %s\n", stru1.translaiton);

    fasta_prod(&stru1);
    fasta_prod(&stru2);

    return 0;
}