/*
 * Had some conversations with co-workers about how to compare two super long
 * integers, so large that they cannot fit in a typical numeric data structure
 * in cpp language.  This number is stored as a string as a result.  The
 * assertion is that you could compare the two strings with strncmp.  I disagree
 * and think you would have to do a "digit" wise comparison of the strings
 * (given that they are of equal length).
 */

#include <string>
#include <string.h>
#include <iostream>

#include <cassert>

int main() {
  std::string super_num = "31415926535897932384626433832795";

  // this case is just to prove that strcmp or string::compare will not work
  std::string one_hundred = "100";
  std::string ninety_nine = "99";
  assert(one_hundred.compare(ninety_nine) < 0);
  assert(strcmp(one_hundred.c_str(), ninety_nine.c_str()) < 0);

  return 0;
}
