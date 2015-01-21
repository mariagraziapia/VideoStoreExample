
#include "Movie.hh"
#include "Rental.hh"
#include "Customer.hh"

#include <iostream>
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE videostoretests
#include <boost/test/unit_test.hpp>


class VideoStoreTestFixture {

public:
  VideoStoreTestFixture() : 
    movie( "Title", Movie::REGULAR ),
    rental( movie, 3 ),
    customer( "Maria Grazia Pia" ) {
    BOOST_MESSAGE( "Create test fixture" );
  }
  virtual ~VideoStoreTestFixture() {
    BOOST_MESSAGE( "Tear down test fixture" );
  }

  Movie movie;
  Rental rental;
  Customer customer;
  
};


BOOST_FIXTURE_TEST_SUITE( videostoresuite, VideoStoreTestFixture )


// Movie

// test getPriceCode:
BOOST_AUTO_TEST_CASE( testgetPriceCode ) {
  int pc= movie.getPriceCode();
  BOOST_CHECK_EQUAL( pc, Movie::REGULAR );
}

// test setPriceCode:
BOOST_AUTO_TEST_CASE( testsetPriceCode ) {
  movie.setPriceCode( Movie::CHILDRENS );
  int pc= movie.getPriceCode();
  BOOST_CHECK_EQUAL( pc, Movie::CHILDRENS );
}

// test getTitle
BOOST_AUTO_TEST_CASE( testgetTitle ) {
  string title= movie.getTitle();
  BOOST_CHECK_EQUAL( title, "Title" );
}

// Rental

// getDaysRented
BOOST_AUTO_TEST_CASE( testgetDaysRented ) {
  int gdr= rental.getDaysRented();
  BOOST_CHECK_EQUAL( gdr, 3 );
}

// getMovie
BOOST_AUTO_TEST_CASE( testgetMovie ) {
  const Movie& m= rental.getMovie();
  BOOST_CHECK_EQUAL( m.getTitle(), movie.getTitle() );
  BOOST_CHECK_EQUAL( m.getPriceCode(), movie.getPriceCode() );
}

// getCharge
BOOST_AUTO_TEST_CASE( testgetCharge ) {
  double charge= rental.getCharge();
  BOOST_CHECK_EQUAL( charge, 3.5 );
}

// Customer

// getName
BOOST_AUTO_TEST_CASE( testgetName ) {
  string name= customer.getName();
  BOOST_CHECK_EQUAL( name, "Maria Grazia Pia" );
}

// statement
BOOST_AUTO_TEST_CASE( teststatement ) {

  // Expected printout:
  string line1( "Rental Record for Maria Grazia Pia");
  string line2( "Snow White and the Seven Dwarfs" );
  string line3( "Gone with the Wind" );
  string line4( "Amount owed is 3.5" );
  string line5( "You earned 2 frequent renter points" );
  stringstream ss;
  ss << line1 << "\n"
     << "\t" << line2 << "\t" << 1.5  << "\n"
     << "\t" << line3 << "\t" << 2 << "\n"
     << line4 << "\n"
     << line5;
  string reference= ss.str();

  // Setup movies and rentals:
  Movie snow( "Snow White and the Seven Dwarfs" );
  snow.setPriceCode( Movie::CHILDRENS );
  Rental snowRental( snow, 3 );
  Movie gone( "Gone with the Wind" );
  gone.setPriceCode( Movie::REGULAR );
  Rental goneRental( gone, 1 );
  customer.addRental( snowRental );
  customer.addRental( goneRental );

  // The test:  
  string receipt= customer.statement();
  BOOST_CHECK_EQUAL( receipt, reference );

}


BOOST_AUTO_TEST_SUITE_END()
