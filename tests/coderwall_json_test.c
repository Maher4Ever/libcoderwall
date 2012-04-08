#include <gtest/gtest.h>
#include "tests_helper.h"

#include "coderwall_json.h"

TEST(ExtractingUserInfoFromJson, WorksWithValidData) {
  char *maher4ever_json = coderwall_tests_fixture("maher4ever.json");
  CoderwallUserData *user = coderwall_new_user_data();

  bool status = coderwall_get_user_info_from_json(maher4ever_json, user);

  ASSERT_EQ(true, status);

  EXPECT_STREQ("Maher Sallam", user->name);
  EXPECT_STREQ("maher4ever",   user->username);
  EXPECT_STREQ("Netherlands",  user->location);

  EXPECT_EQ   (0,  user->endorsements); /* :( */

  EXPECT_EQ   (2,  user->badges_count);

  int i = 0;

  EXPECT_STREQ("Charity", user->badges[i]->name);
  EXPECT_STREQ(
      "Fork and commit to someone's open source project in need",
      user->badges[i]->description
  );
  EXPECT_STREQ(
      "http://cdn.coderwall.com/assets/badges/charity-bf61e713137d910534ff805f389bcffb.png",
      user->badges[i]->image_url
  );

  ++i;

  EXPECT_STREQ("Mongoose", user->badges[i]->name);
  EXPECT_STREQ(
      "Have at least one original repo where Ruby is the dominant language",
      user->badges[i]->description
  );
  EXPECT_STREQ(
      "http://cdn.coderwall.com/assets/badges/mongoose-58cc728c2fc9af62e48c81a03029b23d.png",
      user->badges[i]->image_url
  );

  coderwall_free_user_data(user);
}


TEST(ExtractingUserInfoFromJson, WorksWithInvalidData) {
  CoderwallUserData *user = coderwall_new_user_data();
  bool status = coderwall_get_user_info_from_json("not json", user);

  ASSERT_EQ(false, status);

  coderwall_free_user_data(user);
}
