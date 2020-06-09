#ifndef _libfasta_h_
#define _libfasta_h_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char** get_id(char* gb_filename, int* count); // get the protein_id of CDS
int** get_interval(char* file, char* name); // get start and end points of CDS 
char* get_genSeq(char* file_name); // get the origin strand of CDS
char** get_cdsSeq(int CDS_num, int** intervals, char* origin_sequence); // get strand for the CDS

#endif
