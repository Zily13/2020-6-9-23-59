#include "libgenbank.h"

// function fasta_prod()£ºoutput a cds_stru to given FASTA file each time£»
void fasta_prod(cds_stru* p_stru,char* output_file_name) {
    FILE* output = fopen(output_file_name, "a");

    fputs(">", output);
    fputs(p_stru->id, output);
    fputs("\n", output);
    fputs(p_stru->cdsSeq, output);
    fputs("\n", output);

    fclose(output);
   
}

// function input_cds_stru()£ºadd information for one cds_stru each time£»
void input_cds_stru(char** input_id, char** input_seq, cds_stru* p_stru, int num){
    strcpy(p_stru->id , *(input_id+num));  // input id
    strcpy(p_stru->cdsSeq, *(input_seq + num));  // input sequence
}

// funtion print_cds_stru()£ºprint information of one cds_stru on the screen each time£»
void print_cds_stru(const cds_stru* p_stru) {
    printf(">%s\n", p_stru->id);
    printf("%s\n", p_stru->cdsSeq);
}

