/*!
 * Coderwall C API (libcoderwall)
 *
 * @brief Simple library to access the coderwall API.
 * @details This library allows developers working on C/C++ Projects
 *          to fetch information from the API of coderwall.com.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#ifndef CODERWALL_JSON_H
#define CODERWALL_JSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <coderwall/coderwall.h>

bool coderwall_get_user_info_from_json(const char *json, CoderwallUserData *results_buffer);

#ifdef __cplusplus
}
#endif

#endif /* CODERWALL_JSON_H */
