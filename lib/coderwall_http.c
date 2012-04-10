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
#include <string.h>

#include <curl/curl.h>

#include "coderwall_utils.h"
#include "coderwall_memory.h"
#include "coderwall_http.h"

CURL *coderwall_new_fetcher()
{
  CURL *fetcher = curl_easy_init();

  if ( fetcher == NULL )
  {
    coderwall_error("Couldn't initialize a fetcher.");
  }

  /* curl_easy_setopt(fetcher, CURLOPT_VERBOSE, 1); */
  curl_easy_setopt(fetcher, CURLOPT_NOPROGRESS, 1);
  curl_easy_setopt(fetcher, CURLOPT_FAILONERROR, 1);
  curl_easy_setopt(fetcher, CURLOPT_WRITEFUNCTION, coderwall_accumulate_fetched_data);

  return fetcher;
}

void coderwall_free_fetcher(CURL *fetcher)
{
  curl_easy_cleanup(fetcher);
}

char* coderwall_get_url_of_username(const char *username)
{
  if ( username == NULL || username[0] == '\0' ) return NULL;

  const char *api_url = "http://coderwall.com/";
  const char *data_ext = ".json";

  unsigned int api_url_length = strlen(api_url);
  unsigned int data_ext_length = strlen(data_ext);
  unsigned int username_length = strlen(username);

  char *url = coderwall_malloc(api_url_length + username_length + data_ext_length + 1, "user url"); /* 1 for the '\0' */

  memcpy(url,  api_url, api_url_length);
  memcpy(url + api_url_length,  username, username_length);
  memcpy(url + api_url_length + username_length, data_ext, data_ext_length + 1);

  return url;
}

CoderwallFetchedData *coderwall_new_fetched_data(void)
{
  CoderwallFetchedData *result;
  result = coderwall_malloc(sizeof *result, "results");

  result->data = coderwall_malloc(sizeof *result->data, "results buffer");

  result->length = 0;
  result->data[0] = '\0';

  return result;
}

void coderwall_free_fetched_data(CoderwallFetchedData *result)
{
  free(result->data);
  free(result);
}

size_t coderwall_accumulate_fetched_data(void *data, size_t size, size_t nmemb, CoderwallFetchedData *result)
{
  if ( data == NULL ) return 0;

  size_t data_size = size * nmemb; /* Data size is NOT null terminated */
  size_t new_length = result->length + data_size;

  result->data = coderwall_realloc(result->data, new_length + 1, "results data");

  memcpy(result->data + result->length, data, data_size);

  result->data[new_length] = '\0';
  result->length = new_length;

  return data_size;
}

CURLcode coderwall_fetch_url(const char *url, CoderwallFetchedData *result)
{
  CURL *fetcher;
  CURLcode status;

  fetcher = coderwall_new_fetcher();

  curl_easy_setopt(fetcher, CURLOPT_URL, url);
  curl_easy_setopt(fetcher, CURLOPT_WRITEDATA, result);

  status = curl_easy_perform(fetcher);

  coderwall_free_fetcher(fetcher);

  return status;
}
