#include <stdio.h>

// �ṹ����cds_stru�ģ����ڴ洢CDS��Ϣ�Ľṹ���ͣ�
typedef struct {
    char protein_id[12];
    char translaiton[100];
    /* other declarations */
} cds_stru;

// ����fasta_prod�����ڶ�ȡcds_stru�����Ӧ��FASTA�ļ���
void fasta_prod(cds_stru* p_stru) {
    FILE* output = fopen("test.fasta", "a");

    fputs(">", output);
    fputs(p_stru->protein_id, output);
    fputs("\n", output);
    fputs(p_stru->translaiton, output);
    fputs("\n", output);

    fclose(output);
}

// �������ã�
int main() {
    cds_stru stru1 = { "AYP74058.1", "MIVEKIAAWLLYPLCLLRCFRCFCCPCEVFLRCLCFPCRTLRRLYRGRMTRIREPGAAKDSRDPLICNSLCPATC" };
    cds_stru stru2 = { "AYP74058.2", "LLRCFRCFCCPCEVFLRCLCFPCRTFRCFCCPCEVFLRCLCFPCRTLRRLYRGRMTRIREPGAAKDSRDPLICNS" };
    
    //printf("stru1.protein_id: %s\n", stru1.protein_id);
   // printf("stru1.translaiton: %s\n", stru1.translaiton);

    fasta_prod(&stru1);
    fasta_prod(&stru2);

    return 0;
}