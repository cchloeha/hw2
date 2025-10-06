#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name, price, qty), size_(size), brand_(brand) {

}

Clothing::~Clothing() {

}

set<string> Clothing::keywords() const {
  set<string> keywords;

  // Add keywords from product name
  set<string> nameWords = parseStringToWords(name_);
  keywords.insert(nameWords.begin(), nameWords.end());

  // Add keywords from brand name
  set<string> brandWords = parseStringToWords(brand_);
  keywords.insert(brandWords.begin(), brandWords.end());

  return keywords;

}

string Clothing::displayString() const {
  stringstream ss;
  ss << name_ << "\n"
    << "Size: " << size_ << " Brand: " << brand_ << "\n"
    << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

  return ss.str();
}

void Clothing::dump(std::ostream& os) const {
  os << category_ << "\n"
    << name_ << "\n"
    << fixed << setprecision(2) << price_ << "\n"
    << qty_ << "\n"
    << size_ << "\n"
    << brand_ << endl;
}