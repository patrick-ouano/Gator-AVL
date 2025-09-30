#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "AVL.h"

// Name: Patrick Ouano
// UFID: 78418305

using namespace std;

// Test Case 1: tests at least five incorrect commands/inputs
TEST_CASE("Test 1: Incorrect Commands", "[flag]") {
    // redirects a stringstream to cout - taken from https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    // short ufid
    tree.insert("Patrick", "12345");

    // ufid too long
    tree.insert("Eric", "123456789");

    // ufid contains letters
    tree.insert("Nate", "abcdefgh");

    // name contains symbol
    tree.insert("Joh3n", "00000000");

    // invalid characters in name
    tree.searchName("Isaiah$");

    cout.rdbuf(rdbuf);
    REQUIRE(oss.str() == "unsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\n");
}

// Test Case 2: tests three edge cases
TEST_CASE("Test 2: Edge Cases", "[edge_cases]") {
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    // Test 1: removes node from non-existent tree
    tree.remove("12345678");

    // Test 2: inserts duplicate IDs
    tree.insert("Patrick", "12345678");
    tree.insert("Johan", "12345678");

    // Test 3: removes node that doesn't exist
    tree.remove("87654321");

    cout.rdbuf(rdbuf);
    REQUIRE(oss.str() == "unsuccessful\nsuccessful\nunsuccessful\nunsuccessful\n");
}

// Test Case 3: tests all four rotation cases
TEST_CASE("Rotation Cases", "[flag]") {
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    // tests right rotation - left-left case
    AVLTree rrTree;
    rrTree.insert("C", "00000003");
    rrTree.insert("B", "00000002");
    rrTree.insert("A", "00000001");

    // tests left rotation - right-right case
    AVLTree llTree;
    llTree.insert("A", "00000001");
    llTree.insert("B", "00000002");
    llTree.insert("C", "00000003");

    // tests left-right rotation - right-left case
    AVLTree lrTree;
    lrTree.insert("C", "00000003");
    lrTree.insert("A", "00000001");
    lrTree.insert("B", "00000002");

    // tests right-left rotation - left-right case
    AVLTree rlTree;
    rlTree.insert("A", "00000001");
    rlTree.insert("C", "00000003");
    rlTree.insert("B", "00000002");

    cout.rdbuf(rdbuf);
    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\n"
                           "successful\nsuccessful\nsuccessful\n"
                           "successful\nsuccessful\nsuccessful\n"
                           "successful\nsuccessful\nsuccessful\n");
}

// Test Case 4: tests all three deletion cases
TEST_CASE("Deletion Cases", "[flag]") {
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;
    tree.insert("D", "00000004");
    tree.insert("B", "00000002");
    tree.insert("F", "00000006");
    tree.insert("A", "00000001");
    tree.insert("C", "00000003");
    tree.insert("E", "00000005");
    tree.insert("G", "00000007");

    // Test 1: removes node with no children
    tree.remove("00000001");

    // Test 2: removes node with one child
    tree.remove("00000006");

    // Test 3: removes node with two children
    tree.remove("00000004");

    cout.rdbuf(rdbuf);
    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n"
                           "successful\nsuccessful\nsuccessful\n");
}

// Test Case 5: inserts 100 nodes, removes 10 and checks if in order
TEST_CASE("Insert 100, Remove 10, and Verify In-Order", "[avl_custom]") {

}

// Test Case 6: tests all traversals and printlevelcount
TEST_CASE("Printing Traversals and Level", "[flag]") {
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;
    tree.insert("D", "00000004");
    tree.insert("B", "00000002");
    tree.insert("F", "00000006");
    tree.insert("A", "00000001");
    tree.insert("C", "00000003");
    tree.insert("E", "00000005");
    tree.insert("G", "00000007");

    tree.printInOrder();
    tree.printPreOrder();
    tree.printPostOrder();
    tree.printLevelCount();

    cout.rdbuf(rdbuf);

    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n"
                         "A, B, C, D, E, F, G\n"
                         "D, B, A, C, F, E, G\n"
                         "A, C, B, E, G, F, D\n"
                         "3\n");
}

// Test 7: tests removeInOrder
TEST_CASE("Test removeInOrderN", "[flag]") {
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;
    tree.insert("D", "00000004");
    tree.insert("B", "00000002");
    tree.insert("F", "00000006");
    tree.insert("A", "00000001");
    tree.insert("C", "00000003");
    tree.insert("E", "00000005");
    tree.insert("G", "00000007");

    // Test 1: removes the 0th element
    tree.removeInOrderN(0);
    tree.printInOrder();

    // Test 2: removes the 5th element
    tree.removeInOrderN(5);
    tree.printInOrder();

    // Test 3: removes the 2nd element
    tree.removeInOrderN(2);
    tree.printInOrder();

    // Test 4: out of bounds index
    tree.removeInOrderN(10);

    // Test 5: negative index
    tree.removeInOrderN(-1);

    cout.rdbuf(rdbuf);

    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n"
                         "successful\nsuccessful\nB, C, D, E, F, G\n"
                         "successful\nsuccessful\nB, C, D, E, F\n"
                         "successful\nsuccessful\nB, C, E, F\n"
                         "unsuccessful\n"
                         "unsuccessful\n");
}

// Test 8: tests search for name and id
TEST_CASE("Test Search", "[flag]") {
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;
    tree.insert("Patrick", "00000001");
    tree.insert("Chun", "00000002");
    tree.insert("Johan", "00000003");
    tree.insert("Patrick", "00000007");
    tree.insert("Isaiah", "00000004");
    tree.insert("Nate", "00000005");
    tree.insert("Johann", "00000006");

    // Test 1: search for existing ID
    tree.searchID("00000001");

    // Test 2: search for ID that does not exist
    tree.searchID("12345678");

    // Test 3: search for root node
    tree.searchID("00000004");

    // Test 4: search for name that appears once
    tree.searchName("Chun");

    // Test 5: search for name that appears multiple times
    tree.searchName("Patrick");

    // Test 6: search for name that does not exist
    tree.searchName("Ethan");

    cout.rdbuf(rdbuf);

    REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n"
                         "Patrick\n"
                         "unsuccessful\n"
                         "Isaiah\n"
                         "00000002\n"
                         "00000001\n"
                         "00000007\n"
                         "unsuccessful\n"
                         );
}