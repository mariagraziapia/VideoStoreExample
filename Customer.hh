// Customer.hh
#ifndef CUSTOMER_HH
#define CUSTOMER_HH

#include <string>
#include <vector>
#include "Rental.hh"

// The customer class represents the customer of the store

class Customer {
public:
  Customer();
  explicit Customer( const std::string& name );

  void addRental( const Rental& arg );
  std::string getName() const;
  std::string statement();
  
  // Produce a statement in HTML format
  std::string htmlStatement();

private:
  std::string _name;
  std::vector< Rental > _rentals;

  // Extract Method
  double amountFor( const Rental& each ) const;

  // Replace Temp with Query
  double getTotalCharge();
  int getTotalFrequentRenterPoints();

};


inline Customer::Customer() {}

inline Customer::Customer( const std::string& name ):
  _name( name ) {}

inline void Customer::addRental( const Rental& arg ) { _rentals.push_back( arg ); }

inline std::string Customer::getName() const { return _name; }


#endif // CUSTOMER_HH
