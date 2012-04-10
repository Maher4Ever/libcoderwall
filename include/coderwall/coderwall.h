/*!
 * Coderwall C API (libcoderwall)
 *
 * @brief Simple library to access the coderwall API.
 * @details This library allows developers working on C/C++ Projects
 *          to fetch information from the API of coderwall.com.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#ifndef CODERWALL_H
#define CODERWALL_H

#ifdef __cplusplus
extern "C" {
#endif

#define CODERWALL_VERSION_MAJOR 0
#define CODERWALL_VERSION_MINOR 1
#define CODERWALL_VERSION_PATCH 0

/*!
 * @brief The result of fetching a user's data.
 *
 * This data-type can be used to know wether fetching
 * data from the coderwall API went well or not.
 */
typedef enum {
  /*! User was found and (s)he's data has been parsed */
  CODERWALL_RESULT_SUCCESS        =   1,

  /*! User was not found on coderwall.com */
  CODERWALL_RESULT_USER_NOT_FOUND =  10,

  /*! Fetching data (using libcurl) failed.  */
  CODERWALL_RESULT_FETCHING_FAIL  = 100,

  /*! Parsing server response (using yajl) failed. */
  CODERWALL_RESULT_PARSING_FAIL   = 101,
} CoderwallResult;

/*! Represents a coderwall badge. */
typedef struct {
  char *name;
  char *description;
  char *image_url;
} CoderwallBadge;

/*! Represents the info about a coderwall user. */
typedef struct {
  char* username;
  char *name;
  char *location;
  unsigned int endorsements;
  CoderwallBadge **badges; /*! Array of badges with size "badges_count" */
  size_t badges_count;
} CoderwallUserData;

/*!
 * Allocates memory for a new badge and all its members.
 *
 * @return pointer to the new badge
 */
CoderwallBadge*
coderwall_new_badge(void);

/*!
 * Frees memory already allocated for a badge.
 *
 * @param badge pointer to a badge
 */
void
coderwall_free_badge(CoderwallBadge *badge);

/*!
 * Allocates memory for a new user-data struct and all its members.
 *
 * @return pointer to thr new user-data struct
 */
CoderwallUserData*
coderwall_new_user_data(void);

/*!
 * Frees memory already allocated for a user-data struct.
 *
 * @param results_buffer pointer to a user-data struct
 */
void
coderwall_free_user_data(CoderwallUserData *results_buffer);

/*!
 * Fetches data about a given user and return the result.
 *
 * @param username the nickname of the username
 * @param[out] results_buffer buffer for the data
 *
 * @return the status of the request for data.
 */
CoderwallResult
coderwall_fetch_user_data(const char *username, CoderwallUserData *results_buffer);

#ifdef __cplusplus
}
#endif

#endif /* CODERWALL_H */
