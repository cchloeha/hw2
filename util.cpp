#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> keywords;
  string currentWord;

  // Iterate through each character in input string
  for(char c : rawWords) {
    if(isalnum(c)) {
      // Character is alphanumeric, add to curent word (convert to lowercase)
      currentWord += tolower(c);
    } else {
      // Character is punctuation or space, process the current word
      if(currentWord.length() >= 2) {
        // Word is long enough, add to keywords set
        keywords.insert(currentWord);
      }
      // Reset for next word
      currentWord.clear();
    }
  }
  if(currentWord.length() >= 2) {
    keywords.insert(currentWord);
  }
  return keywords;










}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
