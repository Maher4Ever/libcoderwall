#include <gtest/gtest.h>
#include "tests_helper.h"

#include <coderwall/coderwall.h>

TEST(FetchingUserInfo, WorksWithValidUsername) {
  CoderwallUserData *user = coderwall_new_user_data();
  CoderwallResult status = coderwall_fetch_user_data("maher4ever", user);

  ASSERT_EQ(CODERWALL_RESULT_SUCCESS, status);

  EXPECT_STREQ("maher4ever", user->username);
  EXPECT_STREQ("Maher Sallam", user->name);
  EXPECT_STREQ("Netherlands",  user->location);

  /* The rest of the data could change and it is already tested in the json
   * tests, so no more expectations. */

  coderwall_free_user_data(user);
}

TEST(FetchingUserInfo, WorksWhenUsernameIsNotFound) {
  CoderwallUserData *user = coderwall_new_user_data();
  CoderwallResult status = coderwall_fetch_user_data(
      "some_crazy_username_which_no_one_sane_enough_would_use_unless_he_"
      "wants_to_screw_with_this_spec!"
      ,
      user
  );

  ASSERT_EQ(CODERWALL_RESULT_USER_NOT_FOUND, status);

  coderwall_free_user_data(user);
}
