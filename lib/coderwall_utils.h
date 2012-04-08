/*!
 * Coderwall C API (libcoderwall)
 *
 * @brief Simple library to access the coderwall API.
 * @details This library allows developers working on C/C++ Projects
 *          to fetch information from the API of coderwall.com.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#ifndef CODERWALL_UTILS_H
#define CODERWALL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef bool
  #define bool char
#endif

#ifndef true
  #define true 1
#endif

#ifndef false
  #define false 0
#endif

#define TO_STRING_(x) #x
#define TO_STRING(x) TO_STRING_(x)

void coderwall_error(const char* error);

#ifdef __cplusplus
}
#endif

#endif /* CODERWALL_UTILS_H */
