/*!
 * Coderwall CLI
 *
 * @brief Simple program to retrieve data about developers from the terminal.
 * @author Maher Sallam <maher@sallam.me>
 * @copyright MIT license. See the included LICENSE file for more details.
 */
#include <stdlib.h>
#include <stdio.h>

#include <coderwall/coderwall.h>

#define BADGES_PER_LINE 4

static void
print_user_data(CoderwallUserData *user)
{
  unsigned int i;

  printf("----------------------------------------------------\n"
         "Results for user: %s\n"
         "----------------------------------------------------\n"
         "\n"
         "Name: %s\n"
         "Location: %s\n"
         "Endorsements: %d\n"
         "Registered accounts (%d):"

         , user->username, user->name, user->location, user->endorsements, (unsigned int)user->accounts_count);

  for(i = 0; i < user->accounts_count; ++i) {
      printf(" %s,", user->accounts[i]->type);
  }

  printf("\b\n"
         "Badges (%d):"

         , (unsigned int)user->badges_count);

  for(i = 0; i < user->badges_count; ++i)
  {
    if  ( i % BADGES_PER_LINE == 0 )
      printf("\n  %s,", user->badges[i]->name);
    else
      printf(" %s,",    user->badges[i]->name);
  }

  printf("\b.\n"
         "----------------------------------------------------\n");
}

int main(int argc, char *argv[])
{
  if ( argc < 2 )
  {
    fprintf(stderr, "Usage: coderwall_user USERNAME\n");
    exit(EXIT_FAILURE);
  }

  char *username = argv[1];
  CoderwallUserData *user = coderwall_new_user_data();
  CoderwallResult status = coderwall_fetch_user_data(username, user);

  if ( status != CODERWALL_RESULT_SUCCESS )
  {
    coderwall_free_user_data(user);

    switch(status) {
      case CODERWALL_RESULT_USER_NOT_FOUND:
        fprintf(stderr, "Coderwall: User '%s' couldn't be found on coderwall.\n", username);
        break;
      case CODERWALL_RESULT_FETCHING_FAIL:
        fprintf(stderr, "Coderwall: Fetching the results for '%s' failed.\n", username);
        break;
      case CODERWALL_RESULT_PARSING_FAIL:
        fprintf(stderr, "Coderwall: Parsing the results of '%s' failed.\n", username);
        break;
    }

    return 1;
  }

  print_user_data(user);

  coderwall_free_user_data(user);
  return 0;
}
