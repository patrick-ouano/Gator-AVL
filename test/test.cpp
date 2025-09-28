#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "AVL.h"

// Name: Patrick Ouano
// UFID: 78418305

using namespace std;

//Test Case 1
// TEST_CASE("Invalid Command Inputs", "[invalid]"){
// 	string input = R"(3
// insert "A11y" "45679999"
// insert "Johan Diaz" "12345678"
// insert "Duplicate Person" "12345678"
// )";
// 	string output = R"(successful,
// successful,
// unsuccessful)";
// 	string actualOutput;
// 	REQUIRE(actualOutput == output);
// }

TEST_CASE("Successful Insertions", "[insert]") {
    AVLTree tree;
    bool duplicateID = false; // The insert function requires this parameter

    string name1 = "Johan Diaz";
    string ufid1 = "12345678";

    string name2 = "Zoe";
    string ufid2 = "87654321";

    // REQUIRE that a valid insertion returns true
    REQUIRE(tree.insert(name1, ufid1, duplicateID) == true);

    // REQUIRE that another valid insertion also returns true
    REQUIRE(tree.insert(name2, ufid2, duplicateID) == true);
}

TEST_CASE("Unsuccessful Insertions", "[insert]") {
    AVLTree tree;
    bool duplicateID = false;

    // First, insert a valid student to test against
    string name1 = "Johan Diaz";
    string ufid1 = "12345678";
    tree.insert(name1, ufid1, duplicateID);

    SECTION("Duplicate UFID") {
        string name2 = "Duplicate Person";
        string ufid2 = "12345678"; // Same UFID as before
        // REQUIRE that inserting a duplicate UFID returns false
        REQUIRE(tree.insert(name2, ufid2, duplicateID) == false);
    }

    SECTION("Invalid Name (contains numbers)") {
        string name_invalid = "A11y";
        string ufid_valid = "45679999";
        // REQUIRE that inserting an invalid name returns false
        REQUIRE(tree.insert(name_invalid, ufid_valid, duplicateID) == false);
    }

    SECTION("Invalid UFID (too short)") {
        string name_valid = "Bob";
        string ufid_short = "12345";
        // REQUIRE that inserting an invalid UFID returns false
        REQUIRE(tree.insert(name_valid, ufid_short, duplicateID) == false);
    }

    SECTION("Invalid UFID (contains letters)") {
        string name_valid = "Charlie";
        string ufid_letters = "1234567a";
        // REQUIRE that inserting an invalid UFID returns false
        REQUIRE(tree.insert(name_valid, ufid_letters, duplicateID) == false);
    }
}
