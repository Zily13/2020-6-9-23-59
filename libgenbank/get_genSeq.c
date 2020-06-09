#include "libgenbank.h"

char* get_genSeq(char* file_name){
	int i, j = 0, origin_test = 0, end;
	char str[100];
	static char genSeq[500000];
	FILE* input_file;
	input_file = fopen(file_name, "r");
	while (!feof(input_file))
	{
		if (fgets(str, 500, input_file) != NULL)
		{
			for (i = 0;i < strlen(str);i++)
			{
				if (str[0] == 'O' && str[1] == 'R' && str[2] == 'I' && str[3] == 'G')
					origin_test = 1;
			}
			if (origin_test == 1)
			{
				for (i = 0;i < strlen(str);i++)
				{
					if (str[i] == 'a' || str[i] == 't' || str[i] == 'c' || str[i] == 'g')
					{
						genSeq[j++] = str[i];
					}
				}
			}
		}
	}
	end = fclose(input_file);
	if (end)
	{
		printf("while save genSeq, file close failed!!!\n");
		exit(1);
	}
	return genSeq;
	////函数调用方法
	//char* get_genSeq(char* file_name);
	//int main()
	//{
	//	char* genSeq;
	//	genSeq = (char*)malloc(500000 * sizeof(char));
	//	char* file_name = "./sequence_test.gb";
	//	genSeq = genSeq_get(file_name);
	//	printf("finished.");
	//	int i;
	//	printf("%c\n", genSeq[308826]);
	//	return 0;
	//}
}



	
