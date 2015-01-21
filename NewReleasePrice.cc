// NewReleasePrice.cc
#include "NewReleasePrice.hh"
#include "Movie.hh"

int NewReleasePrice::
getPriceCode() const
{
  return Movie::NEW_RELEASE;
}

double NewReleasePrice::getCharge( int daysRented ) const
{
  return daysRented * 3;
}
