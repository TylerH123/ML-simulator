// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std; 

TEST(test_insert_and_size) {
    BinarySearchTree<int> tree;

    tree.insert(5);

    ASSERT_TRUE(tree.size() == 1);
}

TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
}

TEST(test_height_size) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    ASSERT_TRUE(tree.size() == 4);
    ASSERT_TRUE(tree.height() == 3);
}

TEST(test_copy) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    BinarySearchTree<int> tree2 = tree;
    BinarySearchTree<int> tree3;
    tree3.insert(7);
    tree3.insert(12);
    tree3.insert(122);
    tree3 = tree; 
    ASSERT_TRUE(tree3.to_string() == tree.to_string());
}

TEST(test_find) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    ASSERT_TRUE(*(tree.find(2)) == 2);
}

TEST(test_find_2) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    ASSERT_TRUE(tree.find(3) == tree.end());
}

TEST(test_find_3) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(3);
    b.insert(2);
    b.insert(4);
    b.insert(6);
    b.insert(7);
    ASSERT_TRUE(*(b.find(6)) == 6);
}

TEST(test_min_max) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    ASSERT_TRUE(*tree.min_element() == 1);
    ASSERT_TRUE(*tree.max_element() == 7); 
}

TEST(test_traverse_inorder) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "1 2 5 7 "); 
}

TEST(test_traverse_preorder) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    //cout << tree.to_string() << endl; 
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    //cout << oss_preorder.str() << endl;
    ASSERT_TRUE(oss_preorder.str() == "5 2 1 7 ");
}

TEST(test_invariant) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_invariant_2) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_invariant_3) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    b.insert(3);
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_invariant_4) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(3);
    b.insert(2);
    b.insert(4);
    b.insert(6);
    b.insert(7);
    *++++b.begin() = 1;
    //cout << b.to_string() << endl; 
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_invariant_5) {
    BinarySearchTree<int> b;
    b.insert(4);
    b.insert(2);
    b.insert(1);
    b.insert(3);
    b.insert(7);
    *++++b.begin() = 5;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_invariant_6) {
    BinarySearchTree<int> b;
    b.insert(4);
    b.insert(2);
    b.insert(1);
    *++b.begin() = 1;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_min_greater_than) {
    BinarySearchTree<int> tree;
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(36);
    tree.insert(39); 
    ASSERT_TRUE(*tree.min_greater_than(35) == 36);
}

TEST(test_min_greater_than_2) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(3); 
    ASSERT_TRUE(*tree.min_greater_than(2) == 3);
}

TEST(test_min_greater_than_3) {
    BinarySearchTree<int> tree;
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(34);
    tree.insert(39); 
    ASSERT_TRUE(*tree.min_greater_than(35) == 39);
}

TEST(test_min_greater_than_4) {
    BinarySearchTree<int> tree;
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(36);
    tree.insert(37); 
    ASSERT_TRUE(*tree.min_greater_than(38) == 40);
}

TEST(test_min_greater_than_5) {
    BinarySearchTree<int> tree;
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(36);
    tree.insert(37); 
    ASSERT_TRUE(tree.min_greater_than(60) == tree.end());
}

TEST_MAIN()
