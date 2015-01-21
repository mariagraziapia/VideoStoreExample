
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

// getFrequentRenterPoints
BOOST_AUTO_TEST_CASE( testgetFrequentRenterPoints ) {
  int points= rental.getFrequentRenterPoints();
  BOOST_CHECK_EQUAL( points, 1 );
  Movie newmovie( "New Movie" );
  newmovie.setPriceCode( Movie::NEW_RELEASE );
  Rental newrental( newmovie, 3 );  
  int newpoints= newrental.getFrequentRenterPoints();
  BOOST_CHECK_EQUAL( newpoints, 2 );
}

// Customer

// getName
BOOST_AUTO_TEST_CASE( testgetName ) {
  string name= customer.getName();
  BOOST_CHECK_EQUAL( name, "Maria Grazia Pia" );  
}


BOOST_AUTO_TEST_SUITE_END()


class VideoStoreStatementTestFixture {

public:
  VideoStoreStatementTestFixture() : 
    snow( "Snow White and the Seven Dwarfs", Movie::CHILDRENS ),
    gone( "Gone with the Wind", Movie::REGULAR ),
    snowRental( snow, 3 ),
    goneRental( gone, 1 ),    
    customer( "Maria Grazia Pia" ) {
    BOOST_MESSAGE( "Create VideoStoreStatementTestFixture" );
    customer.addRental( snowRental );
    customer.addRental( goneRental );
  }
  virtual ~VideoStoreStatementTestFixture() {
    BOOST_MESSAGE( "Tear down VideoStoreStatementTestFixture" );
  }

  Movie snow, gone;
  Rental snowRental, goneRental;
  Customer customer;
  
};


BOOST_FIXTURE_TEST_SUITE( videostorestatementsuite, VideoStoreStatementTestFixture )

// statement
BOOST_AUTO_TEST_CASE( teststatement2 ) {

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

  // The test:  
  string receipt= customer.statement();
  BOOST_CHECK_EQUAL( receipt, reference );

}

// htmlStatement
BOOST_AUTO_TEST_CASE( testhtmlStatement ) {

  string line1= "<H1>Rentals for <EM>Maria Grazia Pia</EM></H1><P>";
  string line2= "Snow White and the Seven Dwarfs: 1.5<BR>";
  string line3= "Gone with the Wind: 2<BR>";
  string line4= "<P>You owe <EM>3.5</EM><P>";
  string line5= "On this rental you earned <EM>2</EM> frequent renter points<P>";
  stringstream ss;
  ss << line1 << "\n"
     << line2 << "\n"
     << line3 << "\n"
     << line4 << "\n"
     << line5;
  string reference= ss.str();
  string htmlstmt= customer.htmlStatement();
  BOOST_CHECK_EQUAL( htmlstmt, reference );

}


BOOST_AUTO_TEST_SUITE_END()
