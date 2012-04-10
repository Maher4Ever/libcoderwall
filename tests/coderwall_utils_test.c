#include <gtest/gtest.h>
#include "tests_helper.h"

#include "coderwall_utils.h"

TEST(DefinedTypes, Bool) {
  ASSERT_EQ(sizeof(bool), sizeof(char));
}

TEST(DefinedTypes, True) {
  ASSERT_EQ(true, 1);
}

TEST(DefinedTypes, False) {
  ASSERT_EQ(false, 0);
}

TEST(HelperMacros, ToString) {
  ASSERT_STREQ("my_var", TO_STRING(my_var));
  ASSERT_STREQ("TEST",   TO_STRING(TEST));
}

TEST(ErrorReportingDeathTest, PrintsErrorAndExit) {
  ASSERT_DEATH_IF_SUPPORTED(coderwall_error("DIE!"), "Coderwall error: DIE!\n");
}

TEST(ErrorReportingDeathTest, PrintsErrorWithPassedFormatAndExit) {
  ASSERT_DEATH_IF_SUPPORTED(coderwall_error("%s", "DIE!"), "Coderwall error: DIE!\n");
}
