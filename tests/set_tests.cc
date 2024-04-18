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