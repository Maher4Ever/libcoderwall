#include <gtest/gtest.h>
#include "tests_helper.h"

#include "coderwall_http.h"

TEST(GettingUsenamerUrl, WorkWithUsername) {
  char *result = coderwall_get_url_of_username("maher4ever");

  ASSERT_STREQ("http://coderwall.com/maher4ever.json", result);

  free(result);
}

TEST(GettingUsenamerUrl, ReturnNullWithNull) {
  ASSERT_STREQ(
    NULL,
    coderwall_get_url_of_username(NULL)
  );
}

TEST(GettingUsenamerUrl, ReturnNullWithEmptyString) {
  ASSERT_STREQ(
    NULL,
    coderwall_get_url_of_username("")
  );
}

TEST(InitializingFetchedData, ReturnNewFetchedData) {
  CoderwallFetchedData *data = coderwall_new_fetched_data();

  EXPECT_EQ(0,  data->length);

  EXPECT_STREQ("", data->data);

  coderwall_free_fetched_data(data);
}

TEST(AccumulatingFetchedData, WorksWithEmptyData) {
  CoderwallFetchedData *data = coderwall_new_fetched_data();

  char *fetched_part = "WOHA!";
  size_t fetched_part_length = strlen(fetched_part);

  coderwall_accumulate_fetched_data(fetched_part, fetched_part_length, 1, data);

  EXPECT_STREQ("WOHA!", data->data);
  EXPECT_EQ(fetched_part_length, data->length);

  coderwall_free_fetched_data(data);
}

TEST(AccumulatingFetchedData, WorksWithPartialData) {
  CoderwallFetchedData *data = coderwall_new_fetched_data();

  char *partial_part = "OMG... ";
  size_t partial_part_length = strlen(partial_part);

  coderwall_accumulate_fetched_data(partial_part, partial_part_length, 1, data);

  char *fetched_part = "WOW!";
  size_t fetched_part_length = strlen(fetched_part);

  coderwall_accumulate_fetched_data(fetched_part, fetched_part_length, 1, data);

  EXPECT_STREQ("OMG... WOW!", data->data);
  EXPECT_EQ(fetched_part_length + partial_part_length, data->length);

  coderwall_free_fetched_data(data);
}
