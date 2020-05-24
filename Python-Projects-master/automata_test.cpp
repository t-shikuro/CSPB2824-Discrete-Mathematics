#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include "automata.h"

using namespace std;

TEST_CASE("Cellular Automata: sanity check", "[sanity]") {
  REQUIRE(true);
}

TEST_CASE("Cellular Automata: get previous index", "[prev]") {
  REQUIRE(prev(4, 6) == 3);
  REQUIRE(prev(1, 6) == 0);
  REQUIRE(prev(0, 6) == 5);
  REQUIRE(prev(5, 6) == 4);    
}

TEST_CASE("Cellular Automata: get next index", "[next]") {
  REQUIRE(next(4, 6) == 5);
  REQUIRE(next(1, 6) == 2);
  REQUIRE(next(0, 6) == 1);
  REQUIRE(next(5, 6) == 0);
}

TEST_CASE("Cellular Automata: get neighborhood string", "[neighborhood]") {
  string in = " #  #   #   ##  # # ###  #";
  REQUIRE(get_neighborhood(in, 0) == "# #");
  REQUIRE(get_neighborhood(in, 1) == " # ");
  REQUIRE(get_neighborhood(in, 2) == "#  ");
  REQUIRE(get_neighborhood(in, 25) == " # ");   
}

TEST_CASE("Cellular Automata: get rule 90 value", "[rule90]") {
  REQUIRE(rule90("###", 1) == ' ');
  REQUIRE(rule90("## ", 1) == '#');
  REQUIRE(rule90("# #", 1) == ' ');
  REQUIRE(rule90("#  ", 1) == '#');
  REQUIRE(rule90(" ##", 1) == '#');
  REQUIRE(rule90(" # ", 1) == ' ');
  REQUIRE(rule90("  #", 1) == '#');
  REQUIRE(rule90("   ", 1) == ' ');
}

TEST_CASE("Cellular Automata: make next generation", "[generation]") {
  string in         = " #  #   #   ##  # # ###  #";
  string expected_1 = "  ## # # # #####    # ### ";
  string expected_2 = " ###       #   ##  #  # ##";
  size_t expected_length = in.length();
  string out;

  out = make_next_generation(in);
  REQUIRE(out.length() == expected_length);
  REQUIRE(out == expected_1);

  in = out;
  out = make_next_generation(in);
  REQUIRE(out.length() == expected_length);
  REQUIRE(out == expected_2);  
}
