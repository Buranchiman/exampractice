#include <stdio.h>
#include "bsq.h"

int process(FILE *file)
{
   t_map map;

   if (!file || !parse_map(file, &map))
      return (fputs("map error\n", stderr));
   if (!solve(&map))
      return (fputs("map error\n", stderr));
	else
		print_map(&map);
	free_map(&map);
   return (0);
}

int main(int arc, char **arv)
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
