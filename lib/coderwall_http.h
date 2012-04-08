/*!
 * Coderwall C API (libcoderwall)
 *
 * @brief Simple library to access the coderwall API.
 * @details This library allows developers working on C/C++ Projects
 *          to fetch information from the API of coderwall.com.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#ifndef CODERWALL_HTTP_H
#define CODERWALL_HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <curl/curl.h>

typedef struct {
  char *data;
  size_t length;
} CoderwallFetchedData;

CURL* coderwall_new_fetcher(void);
void  coderwall_free_fetcher(CURL *fetcher);

CoderwallFetchedData* coderwall_new_fetched_data(void);
void                  coderwall_free_fetched_data(CoderwallFetchedData *result);

size_t coderwall_accumulate_fetched_data(void *data, size_t size, size_t nmemb, CoderwallFetchedData *result);

CURLcode coderwall_fetch_url(const char *url, CoderwallFetchedData *result);

char*  coderwall_get_url_of_username(const char *username);

#ifdef __cplusplus
}
#endif

#endif /* CODERWALL_HTTP_H */
