#ifndef _libfasta_h_
#define _libfasta_h_ 

#include <string.h>
#include <stdio.h>
#include <stdlibb.h>
#include <ctype.h>

//struct cds_stru:storing CDS information from genbank file
typedef struct {
  char id[20];
  char cdsSeq[2000];
  /* other declarations */
}  cds_stru;

void input_cds_stru(char** input_id,char** input_seq,cds_stru* p_stru,int num); // put information (id,seq etc) into cds_stru
void print_cds_stru(const cds_stru* p_stru); // print information from a single cds_stru
void fasta_prod(cds_stru* p_stru); //print a .fasta file

#endif
