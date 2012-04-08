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

#include "coderwall_utils.h"

void coderwall_error(const char* error)
{
  fprintf(stderr, "Coderwall error: %s\n", error);
  exit(EXIT_FAILURE);
}
