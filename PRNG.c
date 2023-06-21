#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG_PRINT 0

enum
  {
   multipler = 10,
   ascii_zero = 48,
   ascii_space = 32,
   ascii_line = 10,
  };

void num_to_file(int n, FILE **f)
{
  if(n > 0)
    num_to_file(n / multipler, &(*f));
  else
    return;
  #if DEBUG_PRINT
  printf("%d", n % multipler);
  #endif
  fputc(n % multipler + ascii_zero, *f);
}

int main(int argc, char **argv)
{
  int total = 0, num_per_line = ascii_line, i;
  FILE *to;
  total = atoi(argv[1]);
  to = fopen(argv[3], "w");
  if(!to)
    {
      fprintf(stderr, "file is not open!\n");
      exit(1);
    }
  srand(time(NULL));
  for(i = 0; i < total; i++)
    {
      num_to_file((1 + (int) (atof(argv[2]) *rand() / (RAND_MAX + 1.0))), &to);
      #if DEBUG_PRINT
      printf("\n");
      #endif
      if(i == num_per_line)
	{
	  fputc(ascii_line, to);
	  num_per_line += ascii_line;
	}
      else
	fputc(ascii_space, to);
    }
  fclose(to);
  return 0;
}
  
