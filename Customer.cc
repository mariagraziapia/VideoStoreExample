// Customer.cc
#include <sstream>
#include <vector>
#include "Customer.hh"

using std::ostringstream;
using std::vector;

std::string Customer::statement()
{
  double totalAmount = 0;
  int frequentRenterPoints = 0;
  std::vector< Rental >::iterator iter = _rentals.begin();
  std::vector< Rental >::iterator iter_end = _rentals.end();
  std::ostringstream result;
  result << "Rental Record for " << getName() << "\n";
  for ( ; iter != iter_end; ++iter ) {
    double thisAmount = 0;
    Rental each = *iter;

    thisAmount = amountFor( each );

    // add frequent renter points
    frequentRenterPoints++;
    // add bonus for a two day new release rental
    if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
         && each.getDaysRented() > 1 ) frequentRenterPoints++;

    // show figures for this rental
    result << "\t" << each.getMovie().getTitle() << "\t"
           << thisAmount << "\n";
    totalAmount += thisAmount;
  }
  // add footer lines
  result << "Amount owed is " << totalAmount << "\n";
  result << "You earned " << frequentRenterPoints
         << " frequent renter points";
  return result.str();
}

double Customer::amountFor( const Rental& aRental ) const
{
  return aRental.getCharge();
}
