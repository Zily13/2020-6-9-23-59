//file name: interval_get.c

#include <stdio.h>
#include <stdlib.h>
#include "interval_get.h"

int** interval_get (char* file, char* name) //for example: interval_get (A.txt, CDS)
{
  int line = 0;
  char ll[1024];
  int** interval = (int**)malloc(1*sizeof(int*)); 
  
  FILE *fp = fopen (file, "r"); //if the file input doesnot exist
  if (fp == NULL) 
    {
      printf ("Erro: The file does not exit or cannot be opened!\n");
      exit(1);
    }
  
  for (; (feof(fp) == 0); )
    {
      char number[64];
      fgets(ll, 1024, fp);
      if ((strstr(ll, name) != NULL) && (strstr(ll, "..") != NULL))
	{
	  printf("%s =>", ll);
	  
	  interval = realloc(interval, (line+1)*sizeof(int*));
	  interval[line] = (int*)malloc(3*sizeof(int));
	  interval[line][0] = 1; //means there is 1 interval
	  if (strstr(ll, "complement") != NULL)
	    {
	      interval[line][0] = -1 * interval[line][0]; //means the interval should be opposite
	    }
	  
	  int j = 0; int i = 0;
	  for (; ll[i] != '.'; i++)
	    {
	      if (isdigit(ll[i]) != 0)
		{
		  number[j] = ll[i];
		  j++;
		}
	    }
	  number[j] = '\0';
	  interval[line][1] = atol(number);

	  j = 0; i = i + 2;
	  for (; isdigit(ll[i]) != 0; i++)
	    {
	      if (isdigit(ll[i]) != 0)
		{
		  number[j] = ll[i];
		  j++;
		}
	    }
	  number[j] = '\0';
	  interval[line][2] = atol(number);

	  int n = 2;
	  if (strstr(ll, "join") != NULL)
	    {
	      while (ll[i] != ')')
		{
		  interval[line][0]++;
		  
		  interval[line] = realloc (interval[line], (n+2)*sizeof(int));
		  i = i + 1; j = 0;
		  for (; isdigit(ll[i]) != 0; i++)
		    {
		      if (isdigit(ll[i]) != 0)
			{
			  number[j] = ll[i];
			  j++;
			}
		    }
		  number[j] = '\0';
		  interval[line][n+1] = atol(number);

		  i = i + 2; j = 0;
		  for (; isdigit(ll[i]) != 0; i++)
		    {
		      if (isdigit(ll[i]) != 0)
			{
			  number[j] = ll[i];
			  j++;
			}
		    }
		  number[j] = '\0';
		  interval[line][n+2] = atol(number);
		  
		  n = n + 2;
		}
	    }
	      
	  for (int k = 0; k <= n; k++)
	    {
	      printf("%d ", interval[line][k]);
	    }
	  printf ("\n\n");
	  
	  line++;
	}
    }
  return interval;
}

