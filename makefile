Genebank2Fasta : main.c libgenebank.so libfasta.so
	gcc -o Genebank2Fasta main.c ./libgenebank.so ./libfasta.so

libgenebank.so : get_genSeq.o get_interval.o get_cdsSeq.o get_id.o 
	gcc -shared -o libgenebank.so get_genSeq.o get_interval.o get_cdsSeq.o get_id.o cout_fasta.o

libfasta.so : cout_fasta.o
	gcc -shared -o libfasta.so cout_fasta.o

get_genSeq.o : get_genSeq.c libgenbank.h
	gcc -fPIC -c get_genSeq.c libgenbank.h

get_interval.o : get_interval.c libgenbank.h
	gcc -fPIC -c get_interval.c libgenbank.h

get_cdsSeq.o : get_cdsSeq.c libgenbank.h
	gcc -fPIC -c get_cdsSeq.c libgenbank.h

get_id.o : get_id.c libgenbank.h
	gcc -fPIC -c get_id.c libgenbank.h

cout_fasta.o : cout_fasta.c libfasta.h
	gcc -fPIC -c cout_fasta.c libfasta.h

clean :
	rm -rf *.o 

test :
	gcc -o test test.c


