/*!
 * Coderwall C API (libcoderwall)
 *
 * @brief Simple library to access the coderwall API.
 * @details This library allows developers working on C/C++ Projects
 *          to fetch information from the API of coderwall.com.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#ifndef CODERWALL_MEMORY_H
#define CODERWALL_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

void*
coderwall_malloc (size_t size, char *memory_for, ...);

void*
coderwall_realloc (void *ptr, size_t size, char *memory_for, ...);

#ifdef __cplusplus
}
#endif

#endif /* CODERWALL_MEMORY_H */
