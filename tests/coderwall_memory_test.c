#include <gtest/gtest.h>
#include "tests_helper.h"

#include "coderwall_memory.h"

TEST(AllocatingMemory, WorksWhenThereIsEnoughMemory) {
  void *mem = coderwall_malloc(1, "this won't be used!");

  ASSERT_TRUE( mem != NULL );

  free(mem);
}

#if 0
/* The following test does not work yet! */
TEST(AllocatingMemoryDeathTest, PrintsErrorAndExitWhenThereIsNotEnoughMemory) {
  ASSERT_DEATH_IF_SUPPORTED (
      coderwall_malloc(sizeof(size_t) -1, "testing"),
      "Memory error: Couldn't allocate memory for testing.\n"
  );
}
#endif

TEST(ReallocatingMemory, WorksWhenThereIsEnoughMemory) {
  void *mem = coderwall_malloc(1, "this won't be used!");
  mem = coderwall_realloc(mem, 2, "this won't be used!");

  ASSERT_TRUE( mem != NULL );

  free(mem);
}

#if 0
/* The following test does not work yet! */
TEST(ReallocatingMemory, PrintsErrorAndExitWhenThereIsNotEnoughMemory) {
  void *mem = coderwall_malloc(1, "this won't be used!");

  ASSERT_DEATH_IF_SUPPORTED (
      coderwall_realloc(mem, sizeof(size_t) -1, "testing"),
      "Memory error: Couldn't allocate memory for testing.\n"
  );
}
#endif
