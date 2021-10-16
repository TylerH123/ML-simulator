#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "unit_test_framework.h"

using std::pair;
using std::string;
using std::vector;

TEST(test_ctor) {
	Map<int, int> m;
	ASSERT_TRUE(m.empty());
}

TEST(test_copy_assignment) {
	Map<int, int> m;
	m.insert({2,1}); 
	Map<int, int> m2 = m;
	ASSERT_TRUE(m2[2] == 1);
	Map<int, int> m3;
	m.insert({5,6});
	m3 = m;
	ASSERT_TRUE(m3[2] == 1);
}

TEST(test_insert) {
	Map<string, int> m;
	std::pair<Map<string,int>::Iterator, bool> p = m.insert({"hi",1}); 
	string s = (*p.first).first; 
	int x = (*p.first).second; 
	ASSERT_TRUE(x == 1); 
	ASSERT_TRUE(s == "hi"); 
	ASSERT_TRUE(p.second)
	ASSERT_FALSE(m.insert({"hi",1}).second); 
}

TEST(test_find){
	Map<string, int> m;
	m.insert({"g", 12});
	m.insert({"f", 10});
	m.insert({"a", 11});
	m.insert({"c", 13});
	m.insert({"d", 15});
	m.insert({"e", 14});
	ASSERT_TRUE((*m.find("c")).first == "c" && (*m.find("c")).second == 13);
	ASSERT_TRUE(m.find("z") == m.end());
	ASSERT_TRUE((*m.begin()).first == "a");
}

TEST(test_bracket) {
	Map<string, int> m;
	m.insert({"hi",1}); 
	ASSERT_TRUE(m["hi"] == 1);
	ASSERT_TRUE(m["g"] == 0);
}

TEST_MAIN()
