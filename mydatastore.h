#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:
  MyDataStore();
  virtual ~MyDataStore();

  // DataStore interface implementations
  virtual void addProduct(Product* p);
  virtual void addUser(User* u);
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
  virtual void dump(std::ostream& ofile);

  // Additional functions for cart operations
  void addToCart(std::string username, Product* p);
  void viewCart(std::string username);
  void buyCart(std::string username);
  bool userExists(const std::string& username);

private:
  // All products in the system
  std::vector<Product*> products_;
  // All users in the system
  std::vector<User*> users_;
  // User shopping carts
  std::map<std::string, std::queue<Product*>> carts_;
  // Search index
  std::map<std::string, std::set<Product*>> keywordIndex_;
};

#endif