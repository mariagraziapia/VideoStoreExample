// Movie.cpp
#include "Movie.hh"

#include <stdexcept>
#include "RegularPrice.hh"
#include "ChildrensPrice.hh"
#include "NewReleasePrice.hh"


const int Movie::CHILDRENS;
const int Movie::REGULAR;
const int Movie::NEW_RELEASE;

Movie::Movie( const std::string& title, int priceCode ): 
  _title( title ),
  _price( 0)
{
  setPriceCode( priceCode );
}

Movie::Movie( const Movie& movie ): 
  _title( movie._title ), 
  _price( 0 )
{
  setPriceCode( movie.getPriceCode() );
}

Movie& Movie::operator=( const Movie& rhs )
{
  if ( this == &rhs )
    return *this;
  _title = rhs._title;
  setPriceCode( rhs.getPriceCode() );
  return *this;
}

int Movie::getPriceCode() const
{
  return _price->getPriceCode();
}

void Movie::setPriceCode( int arg )
{
  delete _price;
  switch ( arg ) {
  case REGULAR:
    _price = new RegularPrice;
    break;
  case CHILDRENS:
    _price = new ChildrensPrice;
    break;
  case NEW_RELEASE:
    _price = new NewReleasePrice;
    break;
  default:
    throw std::invalid_argument("Incorrect Price Code");
  }
}


double Movie::getCharge( int daysRented ) const
{
  return _price->getCharge( daysRented );
}


int Movie::getFrequentRenterPoints( int daysRented ) const
{
  if ( ( getPriceCode() == Movie::NEW_RELEASE ) && daysRented > 1 )
    return 2;
  else
    return 1;
}

