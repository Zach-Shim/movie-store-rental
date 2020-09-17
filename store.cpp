#include "store.h"
//-------------------------- default constructor ------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Store::Store() {}

//------------------------------ destructor -----------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Store::~Store(){}

//------------------------------ buildMovies ----------------------------------
// Description:     Creates all Movies that is in a Store's inventory
//
// Preconditions:   infile is an open stream to a text file containing movie
//                  data; the Movie data is correctly formatted
//
// Postconditions:  all valid Movies from the infile text stream have been
//                  initialized and inserted into their appropriate btree
//
bool Store::buildMovies(ifstream& infile) {
   bool success;
   string movieData;
   while(getline(infile, movieData)) {
      // create new movie object
      Movie* newMovie = nullptr;
      success = MovieFactory::createMovie(newMovie, movieData);
      
      // if createMovie was not succesful, delete Movie
      if(!success) {
         delete newMovie;
         newMovie = nullptr;
         continue;
      }
      
      // insert movie into appropriate tree
      switch(newMovie->getType()) {
         case 'F':
            success = comedyTree.insert(newMovie);
            break;
         case 'C':
            success = classicTree.insert(newMovie);
            break;
         case 'D':
            success = dramaTree.insert(newMovie);
            break;
      }
      
      // if insert was not succesful(duplicate data), delete Movie
      if(!success) {
         delete newMovie;
         newMovie = nullptr;
         continue;
      }
   }
   return true;
}

//------------------------------ buildCustomer --------------------------------
// Description:     Creates all Customers that a Store does Transactions with
//
// Preconditions:   infile is an open stream to a text file containing Customer
//                  data; the Customer data is correctly formatted
//
// Postconditions:  all valid Customers from the infile text stream have been
//                  initialized and inserted into hashtable database
//
bool Store::buildCustomers(ifstream& infile) {
   bool success;
   string customerData;
   while(getline(infile, customerData)) {
      // create and initialize customer object
      Customer* account = new Customer;
      success = account->setData(customerData);
      
      // if there was invalid data, delete customer object
      if(!success) {
         delete account;
         account = nullptr;
         continue;
      }
      
      // if there was valid data, add customer to hash table
      customerStorage.insert(account->getID(), account);
   }
   return true;
}

//-------------------------- processTransactions ------------------------------
// Description:     Creates all Transactions that Customers perform on a Store
//                  Also, processes all transactions
//
// Preconditions:   infile is an open stream to a text file containing
//                  Transaction data
//                  Assumes all Transaction data is correctly formatted
//
// Postconditions:  all valid Transaction from the infile text stream have been
//                  initialized and executed
//
bool Store::processTransactions(ifstream& infile) {
   bool success;
   string transData;
   while(getline(infile, transData)) {
      // create a new transaction
      Transaction* transPtr = nullptr;
      success = TransactionFactory::createTransaction(transPtr, transData);
      
      // if initialization was unsuccessful, delete the transPtr
      if(!success) {
         delete transPtr;
         transPtr = nullptr;
         continue;
      }
      
      // execute the transaction
      success = transPtr->executeTransaction(this);
      
      // delete if the transaction was unsuccessful or type Inventory/History
      if(!success) {
         delete transPtr;
         transPtr = nullptr;
      }
   }
   return true;
}

//----------------------------- getClassicTree --------------------------------
// Description:     return classicTree
//
// Preconditions:   none
//
// Postconditions:  return classicTree
//
BinTree<Movie>& Store::getClassicTree() {
   return classicTree;
}

//------------------------------ getComedyTree --------------------------------
// Description:     return comedyTree
//
// Preconditions:   none
//
// Postconditions:  return comedyTree
//
BinTree<Movie>& Store::getComedyTree() {
   return comedyTree;
}

//------------------------------ getDramaTree ---------------------------------
// Description:     return dramaTree
//
// Preconditions:   none
//
// Postconditions:  return dramaTree
//
BinTree<Movie>& Store::getDramaTree() {
   return dramaTree;
}

//------------------------------ getMovieTree ---------------------------------
// Description:     return customer information
//
// Preconditions:   none
//
// Postconditions:  return Customer hashtable
//
HashTable<int, Customer>& Store::getCustomerInfo() {
   return customerStorage;
}

