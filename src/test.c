/* test.c: test the array with variable length.

   Copyright 1996, 2005, 2006, 2007, 2008, 2013, 2014 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libarray.h"

#define STRING_LENGTH 1024
#define BUFFER_STRING_SIZE 1024000
#define ARRAY_SIZE_INC 100

typedef struct array_element{
  char *str1;
} *ptr_array_element;

int
compare_array_element (const void  *e1, const void *e2)
{
  ptr_array_element p1 = (ptr_array_element) e1;
  ptr_array_element p2 = (ptr_array_element) e2;
  return strcmp (p1->str1, p2->str1);
}

/* void * */
/* array_extend (void* array, int array_size, size_t array_element_size) */
/* { */
/*   void *array_tmp; */
/*   array_tmp = realloc(array, array_element_size * (array_size + ARRAY_SIZE_INC)); */
/*   return array_tmp; */
/* } */

int
main()
{
  int array_size;
  int i;
  int j;
  array_size = 10;

  //  struct array_element array1[array_size];
  ptr_array_element array1;
  array1 = array_init(array_size, sizeof(struct array_element));
  /* array1 = calloc(array_size, sizeof(struct array_element)); */

  char *str_buf;
  str_buf = calloc(BUFFER_STRING_SIZE, sizeof(char));

  for (i=0; i<10; i++)
    {
      array1[i].str1 = calloc (STRING_LENGTH, sizeof(char));
    }


  FILE *corpus_txt;
  corpus_txt = fopen ("/Users/judy/GraduateStudy/UTD/Fall2017/CS6320.001-NaturalLanguageProcessing/Homework/Homework1/corpus.txt", "r");
  if (corpus_txt == NULL)
    {
      printf ("File could not be opened.\n");
    }
  else
    {
      /* for (i=0; i<10; i++) */
      /*   { */
      /*     if (fgets(array1[i].str1, STRING_LENGTH, corpus_txt) != NULL) */
      /*       { */
      /*         printf("Line %d: ", i); */
      /*         puts(array1[i].str1); */
      /*       } */
      /*   } */
      i = 0;
      while (fgets(str_buf, STRING_LENGTH, corpus_txt) != NULL)
        {
          if (i >= array_size)
            {
              array1 = (ptr_array_element)(array_extend(array1, array_size, ARRAY_SIZE_INC, sizeof(struct array_element)));
              for (j=array_size; j<array_size+ARRAY_SIZE_INC; j++)
                {
                  array1[j].str1 = calloc (STRING_LENGTH, sizeof(char));
                }
              array_size = array_size + ARRAY_SIZE_INC;
            }
          strcpy(array1[i].str1, str_buf);
          i++;
        }
    }


  qsort(array1, array_size, sizeof(struct array_element), compare_array_element);

  printf("-----------This is lines after qsorting-----------\n");
  for (i=0; i<array_size; i++)
    {
      printf("Line %d: ", i);
      puts(array1[i].str1);
    }
}
