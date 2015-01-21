// Movie.hh
#ifndef MOVIE_HH
#define MOVIE_HH
#include <string>

#include "Price.hh"

class Movie {
public:
  static const int CHILDRENS   = 2;
  static const int REGULAR     = 0;
  static const int NEW_RELEASE = 1;

  Movie( const std::string& title, int priceCode = REGULAR );

  Movie( const Movie& );
  ~Movie();

  Movie& operator=( const Movie& rhs );

  int getPriceCode() const;
  void setPriceCode( int arg );
  std::string getTitle() const;

  double getCharge( int daysRented ) const;
  int getFrequentRenterPoints( int daysRented ) const;

private:
  std::string _title;
  Price* _price;
};

inline Movie::~Movie()
{
  delete _price;
}

inline std::string Movie::getTitle() const { return _title; }

#endif // MOVIE_HH
