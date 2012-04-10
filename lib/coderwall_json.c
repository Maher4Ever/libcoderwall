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

#include <yajl/yajl_tree.h>

#include <coderwall/coderwall.h>

#include "coderwall_utils.h"
#include "coderwall_memory.h"
#include "coderwall_json.h"

#define CODERWALL_EXTRACT_STRING_FROM_JSON_FOR_MEMBER(key_, member_, target_var_, where_, top_node_, tmp_node_, path_var_) \
do {                                                                       \
  path_var_[0] = TO_STRING(key_);                                          \
  tmp_node_ = yajl_tree_get((where_), (path_var_), yajl_t_string);         \
                                                                           \
  if ( tmp_node_ == NULL ) {                                               \
    yajl_tree_free( (top_node_) );                                         \
    return false;                                                          \
  }                                                                        \
                                                                           \
  size_t str_len = strlen(YAJL_GET_STRING( tmp_node_ ));                   \
  target_var_->member_ = coderwall_realloc (                               \
      target_var_->member_, str_len + 1, "user's " TO_STRING(member_)      \
  );                                                                       \
                                                                           \
  memcpy(target_var_->member_, YAJL_GET_STRING( tmp_node_ ), str_len + 1); \
} while(false);

#define CODERWALL_EXTRACT_NUMBER_FROM_JSON_FOR_MEMBER(key_, member_, target_var_, where_, top_node_, tmp_node_, path_var_) \
do {                                                                  \
  path_var_[0] = TO_STRING(key_);                                     \
  tmp_node_ = yajl_tree_get((where_), (path_var_), yajl_t_number);    \
                                                                      \
  if ( tmp_node_ == NULL ) {                                          \
    yajl_tree_free( (top_node_) );                                    \
    return false;                                                     \
  }                                                                   \
                                                                      \
  target_var_->member_ = atoi(YAJL_GET_NUMBER( tmp_node_ ));          \
} while(false);


#define CODERWALL_EXTRACT_STRING_FROM_JSON(key_, target_var_, where_, top_node_, tmp_node_, path_var_) \
  CODERWALL_EXTRACT_STRING_FROM_JSON_FOR_MEMBER(key_, key_, target_var_, where_, top_node_, tmp_node_, path_var_)

#define CODERWALL_EXTRACT_NUMBER_FROM_JSON(key_, target_var_, where_, top_node_, tmp_node_, path_var_) \
  CODERWALL_EXTRACT_NUMBER_FROM_JSON_FOR_MEMBER(key_, key_, target_var_, where_, top_node_, tmp_node_, path_var_)

bool
coderwall_get_user_info_from_json(const char *json, CoderwallUserData *user)
{
  yajl_val top_node = yajl_tree_parse(json, NULL, 0);

  if ( top_node == NULL ) return false;

  const char *path[] = { NULL, '\0' };
  yajl_val node;

  CODERWALL_EXTRACT_STRING_FROM_JSON( name,         user, top_node, top_node, node, path );
  CODERWALL_EXTRACT_STRING_FROM_JSON( username,     user, top_node, top_node, node, path );
  CODERWALL_EXTRACT_STRING_FROM_JSON( location,     user, top_node, top_node ,node, path );
  CODERWALL_EXTRACT_NUMBER_FROM_JSON( endorsements, user, top_node, top_node, node, path );

  /* Extract accounts */
  path[0] = "accounts";
  node = yajl_tree_get(top_node, path, yajl_t_object);

  if ( node == NULL ) {
    yajl_tree_free( top_node );
    return false;
  }

  int i;
  char *tmp_string;
  size_t tmp_string_length;
  yajl_val account_username;

  user->accounts_count = YAJL_GET_OBJECT(node)->len;
  user->accounts = coderwall_realloc(
      user->accounts, user->accounts_count * sizeof(*user->accounts), "user's accounts"
  );

  for(i = 0; i < user->accounts_count; ++i) {
    user->accounts[i] = coderwall_new_user_account();

    tmp_string = YAJL_GET_OBJECT(node)->keys[i]; /* account type */
    tmp_string_length = strlen(tmp_string);
    user->accounts[i]->type = coderwall_realloc(
      user->accounts[i]->type, tmp_string_length + 1, "user-account's type"
    );
    memcpy( user->accounts[i]->type, tmp_string, tmp_string_length + 1);

    account_username = YAJL_GET_OBJECT(node)->values[i];
    tmp_string = YAJL_GET_STRING(account_username); /* account username */
    tmp_string_length = strlen(tmp_string);
    user->accounts[i]->username = coderwall_realloc(
      user->accounts[i]->username, tmp_string_length + 1, "user-account's username"
    );
    memcpy( user->accounts[i]->username, tmp_string, tmp_string_length + 1);
  }

  /* Extract badges */
  path[0] = "badges";
  node = yajl_tree_get(top_node, path, yajl_t_array);

  if ( node == NULL ) {
    yajl_tree_free( top_node );
    return false;
  }

  user->badges_count = YAJL_GET_ARRAY(node)->len;
  user->badges = coderwall_realloc(
      user->badges, user->badges_count * sizeof(*user->badges), "user's badges"
  );

  i = 0;
  yajl_val badge_node;

  for(i = 0; i < user->badges_count; ++i) {
    user->badges[i] = coderwall_new_badge();

    CODERWALL_EXTRACT_STRING_FROM_JSON( name,        user->badges[i], YAJL_GET_ARRAY(node)->values[i], top_node, badge_node, path );
    CODERWALL_EXTRACT_STRING_FROM_JSON( description, user->badges[i], YAJL_GET_ARRAY(node)->values[i], top_node, badge_node, path );

    /* 'badge' in json actually means the image url! */
    CODERWALL_EXTRACT_STRING_FROM_JSON_FOR_MEMBER( badge, image_url, user->badges[i], YAJL_GET_ARRAY(node)->values[i], top_node, badge_node, path );
  }

  yajl_tree_free(top_node);

  return true;
}
