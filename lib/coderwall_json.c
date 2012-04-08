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
  target_var_->member_ = realloc(target_var_->member_, str_len + 1);       \
                                                                           \
  if ( target_var_->member_ == NULL ) {                                    \
    coderwall_error("Couldn't allocate memory when parsing response.");    \
  }                                                                        \
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

bool coderwall_get_user_info_from_json(const char *json, CoderwallUserData *user)
{
  yajl_val top_node = yajl_tree_parse(json, NULL, 0);

  if ( top_node == NULL ) return false;

  const char *path[] = { NULL, '\0' };
  yajl_val node;

  CODERWALL_EXTRACT_STRING_FROM_JSON( name,         user, top_node, top_node, node, path );
  CODERWALL_EXTRACT_STRING_FROM_JSON( username,     user, top_node, top_node, node, path );
  CODERWALL_EXTRACT_STRING_FROM_JSON( location,     user, top_node, top_node ,node, path );
  CODERWALL_EXTRACT_NUMBER_FROM_JSON( endorsements, user, top_node, top_node, node, path );

  path[0] = "badges";
  node = yajl_tree_get(top_node, path, yajl_t_array);

  user->badges_count = (unsigned int)YAJL_GET_ARRAY(node)->len;
  user->badges = realloc(user->badges, sizeof(CoderwallBadge*) * user->badges_count);

  if ( user->badges == NULL ) coderwall_error("Couldn't allocate memory when parsing response.");

  int i = 0;
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
