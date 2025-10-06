#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : public Product {
public:
  // Constructor
  Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);

  // Destructor
  virtual ~Movie();

  // Virtual function implementations
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  virtual void dump(std::ostream& os) const;

private:
  // Movie genre
  std::string genre_;
  // Content rating
  std::string rating_;
};

#endif