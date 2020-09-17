#include "inventory.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Inventory::Inventory() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Inventory::~Inventory(){}


//-------------------------------- setData ------------------------------------
// Description:     Sets the data members of a Inventory Transaction
//
// Preconditions:   infile holds information about a Inventory Transaction
//
// Postconditions:  return true
//
bool Inventory::setData(stringstream& in_stream) {
   return true;
}

//--------------------------- executeTransaction ------------------------------
// Description:     Executes an Inventory transaction
//
// Preconditions:   Store* shop is pointing to a store object
//
// Postconditions:  displays the stock of every movie according to genre
//                  returns false
//
bool Inventory::executeTransaction(Store* shop) {

   cout << endl << "Comedy Inventory:";
   cout << "----------------------------------------------------------------";
   // display headings
   cout << endl << setw(5) << "Genre" << setw(8) << "Media";
   cout << setw(34) << "Title" << setw(20) << "Director";
   cout << setw(7) << "Year" << setw(7) << "Stock" << endl;
   cout << shop->getComedyTree();
   
   cout << "Classic Inventory:";
   cout << "----------------------------------------------------------------";
   // display headings
   cout << endl << setw(5) << "Genre" << setw(8) << "Media";
   cout << setw(25) << "Title" << setw(18) << "Director";
   cout << setw(20) << "Actor";
   cout << setw(7) << "Month" << setw(7) << "Year";
   cout << setw(7) << "Stock" << endl;
   cout << shop->getClassicTree();
   
   cout << "Drama Inventory:";
   cout << "----------------------------------------------------------------";
   // display headings
   cout << endl << setw(5) << "Genre" << setw(8) << "Media";
   cout << setw(34) << "Title" << setw(20) << "Director";
   cout << setw(7) << "Year" << setw(7) << "Stock" << endl;
   cout << shop->getDramaTree();
   
   // delete object after it's done because we do not store it in customer
   // transaction history
   return false;
}

//-------------------------------- display ------------------------------------
// Description:     Displays Inventory data
//
// Preconditions:   none
//
// Postconditions:  Inventory Transaction data is displayed
//
void Inventory::display() {
   cout << "Inventory" << endl;
}
