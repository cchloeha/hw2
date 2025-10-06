#include "mydatastore.h"
#include "util.h"
#include <algorithm>
#include <iostream>

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
  // Clean up all product objects
  for(Product* p : products_) {
    delete p;
  }
  // Clean up all user objects
  for(User* u : users_) {
    delete u;
  }
}

void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);

  // Index the product by its keywords for efficient searching
  set<string> keywords = p->keywords();
  for(const string& keyword : keywords) {
    keywordIndex_[keyword].insert(p);
  }
}

void MyDataStore::addUser(User* u) {
  users_.push_back(u);
  // Initialize an empty shopping cart for user
  carts_[convToLower(u->getName())] = queue<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
  set<Product*> resultSet;
  // Handle empty search terms 
  if(terms.empty()) {
    return vector<Product*>();
  }
  if(type == 0) {
    // AND search - all items must match
    // Start with products matching the first terms
    resultSet = keywordIndex_[terms[0]];

    // Intersect with products matching each subsequent term 
    for(size_t i = 1; i < terms.size(); i++) {
      set<Product*> currentSet = keywordIndex_[terms[i]];
      resultSet = setIntersection(resultSet, currentSet);
    }
  } else { 
    // OR search - any term can match 
    // Union all products matching any of the terms 
    for(const string& term : terms) {
      set<Product*> currentSet = keywordIndex_[term];
      resultSet = setUnion(resultSet, currentSet);
    }

  }
  // Convert set to vector for return 
  return vector<Product*>(resultSet.begin(), resultSet.end());
}

void MyDataStore::dump(ostream& ofile) {
  // Write products section 
  ofile << "<products>" << endl;
  for(Product* p : products_) {
    p->dump(ofile);
  }
  ofile << "</products>" << endl;

  // Write users section 
  ofile << "<users>" << endl;
  for(User* u : users_) {
    u->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string username, Product* p) {
  username = convToLower(username);
  // Check if user exists in the system
  bool userExists = false;
  for(User*u : users_) {
    if(convToLower(u->getName()) == username) {
      userExists = true;
      break;
    }
  }
  if(userExists && carts_.find(username) != carts_.end()) {
    carts_[username].push(p);
  }
}

void MyDataStore::viewCart(string username) {
  username = convToLower(username);
  // Check if user exists
  bool userExists = false;
  for(User* u : users_) {
    if(convToLower(u->getName()) == username) {
      userExists = true;
      break;
    }
  }
  if(!userExists || carts_.find(username) == carts_.end()) {
    cout << "Invalid username" << endl;
    return;
  }

  // Create temporary copy to display without modifying the original
  queue<Product*> tempCart = carts_[username];
  int itemNum = 1;

  // Display each item in the cart
  while(!tempCart.empty()) {
    cout << "Item " << itemNum << endl;
    cout << tempCart.front()->displayString() << endl;
    cout << endl;
    tempCart.pop();
    itemNum++;
  }
}

void MyDataStore::buyCart(string username) {
  username = convToLower(username);
  // Check if user exists
  bool userExists = false;
  User* user = nullptr;
  for(User* u : users_) {
    if(convToLower(u->getName()) == username) {
      userExists = true;
      user = u;
      break;
    }
  }
  if(!userExists || carts_.find(username) == carts_.end()) {
    cout << "Invalid username" << endl;
    return;
  }

  queue<Product*>& cart = carts_[username];
  // Cart for items that could not be purchased 
  queue<Product*> newCart;

  // Process each item in cart
  while(!cart.empty()) {
    Product* p = cart.front();
    cart.pop();

    // Check if product is in stock and user can afford it 
    if(p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
      // Process purchase (reduce stock and deduct from user balance)
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
      } else {
        // Item out of stock or user not found, keep item in cart 
        newCart.push(p);
      }
  }
  // Update cart with remaining items 
  carts_[username] = newCart;
}

bool MyDataStore::userExists(const std::string& username) {
  std::string lowerUsername = convToLower(username);
  for(User* u : users_) {
    if(convToLower(u->getName()) == lowerUsername) {
      return true;
    }
  }
  return false;
}