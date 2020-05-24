#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include "many_functions.h"

using namespace std;

TEST_CASE("Many Functions: sanity check", "[sanity]") {
  REQUIRE(true);
}

TEST_CASE("Many Functions: echo", "[echo]") {
  REQUIRE(echo(3) == 3);
  REQUIRE(echo(13) == 13);
  REQUIRE(echo(0) == 0);
}

TEST_CASE("Many Functions: add four", "[add_four]") {
  REQUIRE(add_four(-4) == 0);
  REQUIRE(add_four(-2) == 2);
  REQUIRE(add_four(0) == 4);
  REQUIRE(add_four(13) == 17);
  REQUIRE(add_four(130) == 134);
}

TEST_CASE("Many Functions: count odds", "[count_odds]") {
  REQUIRE(count_odds(1, 3) == 2);
  REQUIRE(count_odds(1, 1) == 1);
  REQUIRE(count_odds(4, 8) == 2);
  REQUIRE(count_odds(4, 9) == 3);
  REQUIRE(count_odds(3, 9) == 4);    
}

TEST_CASE("Many Functions: is prime", "[is_prime]") {
  REQUIRE(is_prime(5));
  REQUIRE(is_prime(13));
  REQUIRE(is_prime(41));

  REQUIRE_FALSE(is_prime(4));
  REQUIRE_FALSE(is_prime(9));  
  REQUIRE_FALSE(is_prime(12));
  REQUIRE_FALSE(is_prime(100));
  REQUIRE_FALSE(is_prime(14));
}

TEST_CASE("Many Functions: quadratic", "[quadratic]") {
  REQUIRE(quadratic(0, 0, 8, 1234234) == 8.0);
  REQUIRE(quadratic(0, 1, 8, 123) == 131.0);
  REQUIRE(quadratic(1, 0, 0, 4) == 16.0);
  REQUIRE(quadratic(1, 1, 0, 4) == 20.0);
  REQUIRE(quadratic(1, 1, 2, 4) == 22.0);
  REQUIRE(quadratic(3, 7, 4, 2) == 30.0);
}

TEST_CASE("Many Functions: floating point tolerance", "[ftol]") {
  REQUIRE_FALSE(ftol(14.001, 14.0, 0.00001));
  REQUIRE(ftol(14.001, 14.0, 0.01));
  REQUIRE(ftol(10.0, 11.0, 2.0));
  REQUIRE_FALSE(ftol(10.0, 11.0, 0.2));  
}

TEST_CASE("Many Functions: bleep", "[bleep]") {
  REQUIRE(is_bleep(3));
  REQUIRE(is_bleep(6));
  REQUIRE(is_bleep(7));
  REQUIRE(is_bleep(19));
  REQUIRE(is_bleep(21));

  REQUIRE_FALSE(is_bleep(2));
  REQUIRE_FALSE(is_bleep(5));
  REQUIRE_FALSE(is_bleep(10));
  REQUIRE_FALSE(is_bleep(20));
  REQUIRE_FALSE(is_bleep(22));
}

TEST_CASE("Many Functions: blop", "[blop]") {
  // this is a different way of writing tests than the bleep one.
  int yes[] = { 4, 8, 12, 44, 45 };
  for (int i=0; i < 5; i++) {
    REQUIRE(is_blop(yes[i]));
  }
  int no[] = { 3, 6, 35, 42 };
  for (int i=0; i < 4; i++) {
    REQUIRE_FALSE(is_blop(no[i]));
  }
}

TEST_CASE("Many Functions: bleebleblam", "[bleebleblam]") {
  int yes[] = { 12, 16, 24, 45, 48 };
  int no[] =  { 4,   7,  9, 20, 34 };
  for (int i=0; i < 5; i++) {
    REQUIRE(is_bleebleblam(yes[i]));
    REQUIRE_FALSE(is_bleebleblam(no[i]));
  }
}
