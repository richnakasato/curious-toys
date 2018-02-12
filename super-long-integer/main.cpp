/*
 * Had some conversations with co-workers about how to compare two super long
 * integers, so large that they cannot fit in a typical numeric data structure
 * in cpp language.  This number is stored as a string as a result.  The
 * assertion is that you could compare the two strings with strncmp.  I disagree
 * and think you would have to do a "digit" wise comparison of the strings
 * (given that they are of equal length).
 *
 * Turns out I was wrong.  You can use string::compare and/or strcmp to compare
 * equal length strings, as opposed to using a "digit" wise compare.  We only
 * need to check for string lengths before we use compare for everything to
 * work.
 *
 */

#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>

#include <cassert>

struct a_less_b {
  bool operator()(std::string const &a, std::string const &b) {
    if(a.length() != b.length()) {
      return (a.length() < b.length()) ? true : false;
    }
    return (a.compare(b) < 0) ? true : false;
  }
};

int main() {
  std::string super_num1 = "31415926535899932384626433832795";
  std::string super_num2 = "31415926535897932384626433832795";

  // we expect that one hundred should be larger than ninety_nine
  std::string one_hundred = "100";
  std::string ninety_nine = "99";
  //assert(one_hundred.compare(ninety_nine) > 0);
  //assert(strcmp(one_hundred.c_str(), ninety_nine.c_str()) > 0);
  //assert(strcmp(super_num1.c_str(), super_num2.c_str()) > 0);

  // this is how I imagine we should compare two ints represented as strings
  a_less_b compare;
  bool test1 = compare(one_hundred, ninety_nine);
  bool test2 = compare(super_num1, super_num2);

  assert(!test1);
  assert(!test2);

  return 0;
}
