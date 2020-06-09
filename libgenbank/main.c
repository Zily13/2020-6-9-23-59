#include "libgenbank.h"
#include "libfasta.h"

int main(int argc,char *argv[]) {
    if(argc!=2){
      printf("Error:no filename as arguement");
      exit(1);
    }
    int cds_count;  // the whole number of CDS

    // get input_id (a second rank pointer storing protein_ids of each CDS)：protein_id
    char** protein_id;  
    protein_id = get_id(argv[1], &cds_count);
    
    // get start and end point of each CDS(a second rank pointer storing start and end point of each CDS)：interval
    int** interval;
    interval = get_interval(argv[1], "CDS");

    // get the whole origin strand(a char pointer pointing to the start of the whole origin strand)：genSeq
    char* genSeq;
    genSeq = get_genSeq(argv[1]);

    // get input_seq (a second rank pointer storing sequence of each CDS)：sequence
    char** sequence;
    sequence = get_cdsSeq(cds_count, interval, genSeq);

    // call memory for cds_stru：
    cds_stru* p_cds_stru;
    p_cds_stru = (cds_stru*)malloc(cds_count * (sizeof(cds_stru)));
    if (p_cds_stru == NULL) { printf("Out of memory!\n"); exit(1); }

    // put information (protein_id,sequence) into each cds_stru：
    int num = 0;  // count from number 0
    char tempname[50];
    strncpy(tempname,argv[1],strlen(argv[1])-3);
    for (num; num < cds_count; num++) {
        input_cds_stru(protein_id, sequence,p_cds_stru+num, num); // put into cds_stru
        // print_cds_stru(p_cds_stru + num);  // print information from cds_stru
        
        fasta_prod(p_cds_stru + num,strcat(tempname,".gb"));  // output as .fasta file
    }

    return 0;
}
