//file name: interval_get.c

#include <stdio.h>
#include <stdlib.h>
#include "interval_get.h"

int* interval_left_get (char* file, char* name)
{
  int line = 0;
  char ll[1024];
  int* interval = (int*)malloc(1*sizeof(int));
  
  FILE *fp = fopen (file, "r");
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
	  interval = realloc(interval, (line+2)*sizeof(int));
	  int j = 0;
	  for (int i = 0; ll[i] != '.'; i++)
	    {
	      if (isdigit(ll[i]) != 0)
		{
		  number[j] = ll[i];
		  j++;
		}
	    }
	  number[j] = '\0';
	  interval[line] = atol(number);
	  line++;
	}
    }
  return interval;
}

int* interval_right_get (char* file, char* name)
{
  int line = 0;
  char ll[1024];
  int* interval = (int*)malloc(1*sizeof(int));

  FILE *fp = fopen (file, "r");
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
	  interval = realloc(interval, (line+2)*sizeof(int));
	  int j = 0;
	  for (int i = 0; ll[i] != '\n'; i++)
	    {
	      if ((ll[i] == '.') && (ll[i+1] == '.'))
		{
		  for (; isdigit(ll[j+i+2]) != 0; j++)
		    {
		      number[j] = ll[j+i+2];
		    }
		  break;
		}
	    }
	  number[j] = '\0';
	  printf("%s ", number);
	  interval[line] = atol(number);
	  printf("%d\n", interval[line]);
	  line++;
	}
    }
  return interval;
}
