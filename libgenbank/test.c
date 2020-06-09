#include "libgenbank.h"

int main() {
    int cds_count;  // the whole number of CDS

    // get input_id (a second rank pointer storing protein_ids of each CDS)£ºprotein_id
    char** protein_id;  
    protein_id = get_id("./sequence_test.gb", &cds_count);
    
    // get start and end point of each CDS(a second rank pointer storing start and end point of each CDS)£ºinterval
    int** interval;
    interval = get_interval("./sequence_test.gb", "CDS");

    // get the whole origin strand(a char pointer pointing to the start of the whole origin strand)£ºgenSeq
    char* genSeq;
    genSeq = get_genSeq( "./sequence_test.gb");

    // get input_seq (a second rank pointer storing sequence of each CDS)£ºsequence
    char** sequence;
    sequence = get_cdsSeq(cds_count, interval, genSeq);

    // call memory for cds_stru£º
    cds_stru* p_cds_stru;
    p_cds_stru = (cds_stru*)malloc(cds_count * (sizeof(cds_stru)));
    if (p_cds_stru == NULL) { printf("Out of memory!\n"); exit(1); }

    // put information (protein_id,sequence) into each cds_stru£º
    int num = 0;  // count from number 0
    for (num; num < cds_count; num++) {
        input_cds_stru(protein_id, sequence,p_cds_stru+num, num); // put into cds_stru
        // print_cds_stru(p_cds_stru + num);  // print information from cds_stru
        
        fasta_prod(p_cds_stru + num);  // output as¡°test.fasta file
    }

    return 0;
}
