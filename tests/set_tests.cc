#include <set.h>
#include <gtest/gtest.h>
#include<iostream>

TEST(set_test, constructor_params) {
	my_set set{ 1 };
	ASSERT_EQ(set.get_root_value(), 1);
}

TEST(set_test, copy_constructor) {
	my_set set2{ 1,9,4 };
	ASSERT_TRUE(my_set(set2) == set2);
}

TEST(set_test, overloaded_equal) {
	my_set set2{ 1,9,4 };
	my_set set1 = set2;
	ASSERT_TRUE(set1 == set2);
}

TEST(set_test, contains_in_tree) {
	my_set set2{ 1,9,4 };
	ASSERT_TRUE(set2.contains(9));
}


TEST(set_test, erase_item_in_tail) {
	my_set set2{ 1,9,4 };
	set2.erase(4);
	my_set set1{ 1,9 };
	ASSERT_TRUE(set1 == set2);
}

TEST(set_test, erase_item_in_middle) {
	my_set set2{ 1,9,4 };
	set2.erase(9);
	my_set set1{ 1,4 };
	ASSERT_TRUE(set1 == set2);
}

TEST(set_test, erase_item_in_head) {
	my_set set2{ 1,9,4 };
	set2.erase(1);
	my_set set1{ 9,4 };
	ASSERT_TRUE(set1 == set2);
}

TEST(set_test, union_sets) {
	my_set set2{ 1,9,4 };
	my_set set1{ 9,4,3 };

	my_set result{ 9,1,4,3 };
	ASSERT_TRUE(result == union_of_sets(set1, set2));
}

TEST(set_test, union_null_sets) {
	ASSERT_TRUE(my_set() == union_of_sets(my_set(), my_set()));
}

TEST(set_test, union_with_null_set) {
	my_set set1{ 22,5,3 };
	my_set result(set1);
	ASSERT_TRUE(result == union_of_sets(set1, my_set()));
}

TEST(set_test, sym_difference_sets) {
	my_set set2{ 1,9,4 };
	my_set set1{ 9,4,3 };

	my_set result{ 1,3 };
	ASSERT_TRUE(result == symmetrical_difference(set2, set1));
}

TEST(set_test, sym_difference_with_null_first) {
	my_set set1{ 9,4,3 };
	ASSERT_TRUE(set1 == symmetrical_difference(my_set(), set1));
}

TEST(set_test, sym_difference_with_null_second) {
	my_set set1{ 9,4,3 };
	ASSERT_TRUE(my_set(set1) == symmetrical_difference(set1, my_set()));
}

TEST(set_test, sym_difference_with_null_sets) {
	ASSERT_TRUE(my_set() == symmetrical_difference(my_set(), my_set()));
}
