#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* sequence_get(char *file_name);

int main()
{
	char *sequence;
	sequence = (char*)malloc(500000*sizeof(char));
	char *file_name = "sequence.gb";
	sequence = sequence_get(file_name);
	printf("finished.");
	int i;
	printf("%c\n",sequence[308826]);
	return 0;
}


char* sequence_get(char *file_name)
{
	int i, j=0,origin_test=0,end;
	char str[100];
	static char sequence[500000];
	FILE *input_file;
	input_file = fopen(file_name,"r");
	while(!feof(input_file))
	{
		if(fgets(str,500,input_file)!=NULL)
		{
			for(i=0;i<strlen(str);i++)
			{
				if(str[0] == 'O' && str[1] == 'R' && str[2] == 'I' && str[3] == 'G')
					origin_test = 1;
			}	
			if(origin_test == 1)	
			{
				for(i=0;i<strlen(str);i++)
				{
					if(str[i]=='a'||str[i]=='t'||str[i]=='c'||str[i]=='g')
					{
						sequence[j++] = str[i];
					}
				}
			}
		}
	}
	end = fclose(input_file);
    if(end)
    {
        printf("while save sequence, file close failed!!!\n");
        exit(1);
    }
	return sequence;
}
			
			
