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

#include <coderwall/coderwall.h>
#include "coderwall_utils.h"
#include "coderwall_http.h"
#include "coderwall_json.h"

CoderwallBadge* coderwall_new_badge(void)
{
  CoderwallBadge *badge = malloc(sizeof(CoderwallBadge));

  if ( badge == NULL ) coderwall_error("Couldn't create a new badge.");

  badge->name = malloc(sizeof(char *));
  badge->description = malloc(sizeof(char *));
  badge->image_url = malloc(sizeof(char *));

  if ( badge->name == NULL || badge->description == NULL || badge->image_url == NULL )
  {
    coderwall_error("Couldn't allocate memory for badge's data.");
  }

  return badge;
}

void coderwall_free_badge(CoderwallBadge *badge)
{
  free(badge->name);
  free(badge->description);
  free(badge->image_url);
  free(badge);
}

CoderwallUserData* coderwall_new_user_data(void)
{
  CoderwallUserData *user = malloc(sizeof(CoderwallUserData));

  if ( user == NULL ) coderwall_error("Couldn't create a new user data.");

  user->name = malloc(sizeof(char *));
  user->username = malloc(sizeof(char *));
  user->location = malloc(sizeof(char *));

  user->badges_count = 0;
  user->badges = malloc(sizeof(CoderwallBadge*));

  if ( user->name == NULL || user->username == NULL || user->location == NULL || user->badges == NULL )
  {
    coderwall_error("Couldn't allocate memory for user's data.");
  }

  return user;
}

void coderwall_free_user_data(CoderwallUserData *user)
{
  int i;

  free(user->name);
  free(user->username);
  free(user->location);

  for(i = 0; i < user->badges_count; ++i)
  {
    coderwall_free_badge(user->badges[i]);
  }

  free(user->badges);
  free(user);
}

CoderwallResult coderwall_fetch_user_data(const char *username, CoderwallUserData *result)
{
  char *url = coderwall_get_url_of_username(username);
  CoderwallFetchedData *buffer = coderwall_new_fetched_data();
  CURLcode status = coderwall_fetch_url(url, buffer);

  free(url);

  if ( buffer == NULL || status != CURLE_OK ) {
    coderwall_free_fetched_data(buffer);
    return status == CURLE_HTTP_RETURNED_ERROR ?
      CODERWALL_RESULT_USER_NOT_FOUND :
      CODERWALL_RESULT_FETCHING_FAIL;
  }

  bool parsing_status = coderwall_get_user_info_from_json(buffer->data, result);

  coderwall_free_fetched_data(buffer);

  if ( parsing_status == false ) return CODERWALL_RESULT_PARSING_FAIL;

  return CODERWALL_RESULT_SUCCESS;
}
