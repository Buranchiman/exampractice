#include <stdio.h>
#include "bsq.h"

void process(FILE *file)
{
   t_map map;

   if (!file || parse_map(file, &map))
      fputs("map error\n", stderr);
   if (!solve_map(map))
      fputs("map error\n", stderr);
   return ;
}

int main(int arc, char *arv)
{

   if (arc < 2)
   {
      process(stdin);
      return (0);
   }
   for (int i = 1; i < arc; i++)
   {
        FILE    *file = fopen(arv[i], "r");
        if (!file)
            return (fprintf(stderr, "map error\n"));
         process(file);
         if (file)
            fclose(file);
         if (i < arc - 1)
            fputs("\n", stdout);
   }
}