/*!
 * Coderwall C API (libcoderwall)
 *
 * @brief Simple library to access the coderwall API.
 * @details This library allows developers working on C/C++ Projects
 *          to fetch information from the API of coderwall.com.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "coderwall_utils.h"
#include "coderwall_memory.h"

static void
print_error_and_exit(char *format, va_list format_args)
{
  fprintf(stderr, "Memory error: ");
  vfprintf(stderr, format, format_args);
  fprintf(stderr, ".\n");

  exit(EXIT_FAILURE);
}

void*
coderwall_malloc (size_t size, char *memory_for, ...)
{
  void *memory = malloc(size);

  if ( memory == NULL ) {
    va_list vars;
    va_start(vars, memory_for);
    print_error_and_exit(memory_for, vars);
  }

  return memory;
}

void*
coderwall_realloc (void *ptr, size_t size, char *memory_for, ...)
{
  void *memory = realloc(ptr, size);

  if ( memory == NULL ) {
    va_list vars;
    va_start(vars, memory_for);
    print_error_and_exit(memory_for, vars);
  }

  return memory;
}
