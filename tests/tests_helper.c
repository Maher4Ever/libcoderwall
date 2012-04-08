#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests_helper.h"

char* coderwall_tests_fixture(const char *filename)
{
  char* file_path = (char *)malloc(strlen(FIXTURES_PATH) + strlen(filename) + 1);

  strcpy(file_path, FIXTURES_PATH);
  strcat(file_path, filename);

  FILE *f = fopen(file_path, "rb");

  if ( f == NULL )  {
    fprintf(stderr, "Fixture error: couldn't open fixture file '%s'.\n", file_path);
    exit(EXIT_FAILURE);
  }

  fseek(f , 0 , SEEK_END);
  long int file_size = ftell(f);
  rewind (f);

  char *data = (char *)malloc(sizeof(char) * file_size);

  if ( data == NULL ) {
    fprintf(stderr, "Fixture error: couldn't allocate memory for fixture file '%s'.\n", file_path);
    exit(EXIT_FAILURE);
  }

  size_t bytes_read = fread(data, 1, file_size, f);

  if ( bytes_read != file_size ) {
    fprintf(stderr, "Fixture error: something went wrong while reading the fixture file '%s'.\n", file_path);
    exit(EXIT_FAILURE);
  }

  free(file_path);
  fclose(f);

  return data;
}
