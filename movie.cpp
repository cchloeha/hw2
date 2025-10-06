#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating)
  : Product(category, name, price, qty), genre_(genre), rating_(rating) {

  }

Movie::~Movie() {

}

set<string> Movie::keywords() const {
  set<string> keywords;
  // Add keywords from movie name
  set<string> nameWords = parseStringToWords(name_);
  keywords.insert(nameWords.begin(), nameWords.end());

  // Add genre as a keyword 
  keywords.insert(convToLower(genre_));

  return keywords;
}

string Movie::displayString() const {
  stringstream ss;
  ss << name_ << "\n"
    << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
    << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Movie::dump(std::ostream& os) const {
  os << category_ << "\n"
    << name_ << "\n"
    << fixed << setprecision(2) << price_ << "\n"
    << qty_ << "\n"
    << genre_ << "\n"
    << rating_ << endl;
}