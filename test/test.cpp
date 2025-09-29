#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "AVL.h"

// Name: Patrick Ouano
// UFID: 78418305

using namespace std;

// // Test Case 1: Testing invalid commands and data validation
// TEST_CASE("Test 1: Incorrect Commands", "[invalid]") {
//     // Redirect cout to a string stream to capture output
//     ostringstream oss;
//     streambuf* rdbuf = std::cout.rdbuf();
//     cout.rdbuf(oss.rdbuf());
//
//     AVLTree tree;
//
//     // Test 1: Insert with invalid UFID (too short)
//     tree.insert("StudentA", "12345");
//
//     // Test 2: Insert with invalid UFID (contains letters)
//     tree.insert("StudentB", "1234567a");
//
//     // Test 3: Insert with invalid name (contains numbers)
//     tree.insert("Student123", "88888888");
//
//     // Test 4: Remove a non-existent ID from an empty tree
//     tree.remove("99999999");
//
//     // Test 5: RemoveInorder N on an empty tree
//     tree.removeInOrderN(0);
//
//     // Restore cout and check the captured output
//     cout.rdbuf(rdbuf);
//     REQUIRE(oss.str() == "unsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\n");
// }
//
// // Test Case 2: Testing all four AVL rotation cases on insertion
// TEST_CASE("Test 2: All Four Rotation Cases", "[rotations]") {
//     // Redirect cout to a string stream to capture output
//     ostringstream oss;
//     streambuf* rdbuf = std::cout.rdbuf();
//     cout.rdbuf(oss.rdbuf());
//
//     // Test Right Rotation (Left-Left Case)
//     AVLTree ll_tree;
//     ll_tree.insert("C", "00000003");
//     ll_tree.insert("B", "00000002");
//     ll_tree.insert("A", "00000001");
//
//     // Test Left Rotation (Right-Right Case)
//     AVLTree rr_tree;
//     rr_tree.insert("A", "00000001");
//     rr_tree.insert("B", "00000002");
//     rr_tree.insert("C", "00000003");
//
//     // Test Left-Right Rotation (Left-Right Case)
//     AVLTree lr_tree;
//     lr_tree.insert("C", "00000003");
//     lr_tree.insert("A", "00000001");
//     lr_tree.insert("B", "00000002");
//
//     // Test Right-Left Rotation (Right-Left Case)
//     AVLTree rl_tree;
//     rl_tree.insert("A", "00000001");
//     rl_tree.insert("C", "00000003");
//     rl_tree.insert("B", "00000002");
//
//     // Restore cout and check the captured output
//     cout.rdbuf(rdbuf);
//     // Each of the 12 inserts (4 cases * 3 inserts) should be successful
//     REQUIRE(oss.str() == "successful\nsuccessful\nsuccessful\n"
//                            "successful\nsuccessful\nsuccessful\n"
//                            "successful\nsuccessful\nsuccessful\n"
//                            "successful\nsuccessful\nsuccessful\n");
// }


TEST_CASE("Edge Cases (Remove when tree is empty, remove node that doesn't exist, add node that exists", "[flag]"){
    // Redirect cout to a string stream to capture output
    ostringstream oss;
    streambuf* rdbuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    // Test 1: Remove from an empty tree
    tree.removeInOrderN(5);

    // Test 2: Successful insert
    tree.insert("Dylan Tran", "99363932");

    // Test 3: Remove a non-existent ID
    tree.remove("99363933");

    // Test 4: Insert a duplicate ID
    // FIX: Changed 99363932 to "99363932" to match function signature
    tree.insert("Charelion", "99363932");

    // Restore cout and check the captured output
    cout.rdbuf(rdbuf);
    REQUIRE(oss.str() == "unsuccessful\nsuccessful\nunsuccessful\nunsuccessful\n");
}
