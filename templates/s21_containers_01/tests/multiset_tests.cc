#include <gtest/gtest.h>

#include <initializer_list>
#include <iostream>
#include <set>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

TEST(MultisetConstructor, Default) {
  s21::Multiset<std::string> s;
  std::multiset<std::string> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(Iterator,
     initializer_list_operator_dereferencing_plusplus_minusminus_begin_end) {
  s21::Multiset<int> s = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  std::multiset<int> b = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  auto si = s.begin();
  auto bi = b.begin();
  for (; si != s.end() && bi != b.end(); ++si, ++bi) {
    EXPECT_EQ((*si), (*bi));
  }

  si = s.end();
  bi = b.end();
  -- --si;
  -- --bi;
  EXPECT_EQ((*si), (*bi));

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MultisetConstructors, Copy) {
  s21::Multiset<int> s_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  s21::Multiset<int>& cp_s_tree(s_tree);

  std::multiset<int> o_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};
  std::multiset<int> cp_o_tree = o_tree;

  auto si = cp_s_tree.begin();
  auto oi = cp_o_tree.begin();
  for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
  EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
}

TEST(MultisetConstructors, Move) {
  s21::Multiset<int> s_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};
  s21::Multiset<int> mv_s_tree = std::move(s_tree);

  std::multiset<int> o_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};
  std::multiset<int> mv_o_tree = std::move(o_tree);

  auto si = mv_s_tree.begin();
  auto oi = mv_o_tree.begin();
  for (; si != mv_s_tree.end() && oi != mv_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(mv_s_tree.size(), mv_o_tree.size());
  EXPECT_EQ(mv_s_tree.empty(), mv_o_tree.empty());

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MultisetConstructors, Operator_equal) {
  s21::Multiset<int> m1 = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  s21::Multiset<int>& m2 = m1;

  auto e = m1.end();
  --e;
  auto i = m1.end();
  do {
    ++i;
    EXPECT_EQ((*i), (*i));
  } while (i != e);

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Modifiers, Erase) {
  s21::Multiset<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                       {"four"},  {"five"}, {"six"}, {"seven"},
                                       {"eight"}, {"nine"}};

  std::multiset<std::string> o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                       {"four"},  {"five"}, {"six"}, {"seven"},
                                       {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();

  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  auto s_it = s_tree.end();
  auto o_it = o_tree.end();
  --s_it;
  --o_it;

  s_tree.erase(s_it);
  o_tree.erase(o_it);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  si = s_tree.begin();
  oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(MultisetLookup, Find) {
  s21::Multiset<std::string> s1 = {{"zero"},  {"one"},  {"two"}, {"three"},
                                   {"four"},  {"five"}, {"six"}, {"seven"},
                                   {"eight"}, {"nine"}};

  std::multiset<std::string> s2 = {{"zero"},  {"one"},  {"two"}, {"three"},
                                   {"four"},  {"five"}, {"six"}, {"seven"},
                                   {"eight"}, {"nine"}};

  EXPECT_EQ(*s1.find("zero"), *s2.find("zero"));
  EXPECT_EQ(*s1.find("seven"), *s2.find("seven"));
}

TEST(MultisetLookup, Contains) {
  s21::Multiset<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                       {"four"},  {"five"}, {"six"}, {"seven"},
                                       {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.contains("zero"), true);
  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

TEST(MultisetModifiers, Insert_clear) {
  s21::Multiset<double> v = {1, 1,  2, 1,  2,  -3, 20, -5,
                             1, -6, 8, 42, 26, 8,  8,  8};
  std::multiset<double> vc = {1, 1,  2, 1,  2,  -3, 20, -5,
                              1, -6, 8, 42, 26, 8,  8,  8};
  v.insert_m(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();

  for (; y != vc.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }

  v.clear();
  vc.clear();

  for (; y != vc.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Modifiers, Swap) {
  s21::Multiset<std::string> f_s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  s21::Multiset<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                         {"fourty"}, {"fifty"},  {"sixty"},
                                         {"seventy"}};

  std::multiset<std::string> f_o_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                         {"fourty"}, {"fifty"},  {"sixty"},
                                         {"seventy"}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  f_s_tree.swap(s_s_tree);
  f_o_tree.swap(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(Modifiers, Merge) {
  s21::Multiset<int> m1a{{1}, {5}, {10}};
  s21::Multiset<int> m1b{{2}, {4}, {5}, {8}};
  s21::Multiset<int> u1;

  std::multiset<int> m2a{{1}, {5}, {10}};
  std::multiset<int> m2b{{2}, {4}, {5}, {8}};
  std::multiset<int> u2;
  u1.merge(m1a);
  u2.merge(m2a);

  auto i1 = u1.begin();
  auto i2 = u2.begin();
  for (; i1 != u1.end() && i2 != u2.end(); ++i1, ++i2) {
    EXPECT_EQ((*i1), (*i2));
  }

  s21::Multiset<std::string> f_s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  s21::Multiset<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                         {"fourty"}, {"fifty"},  {"sixty"},
                                         {"seventy"}};

  std::multiset<std::string> f_o_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                         {"fourty"}, {"fifty"},  {"sixty"},
                                         {"seventy"}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  f_s_tree.merge(s_s_tree);
  f_o_tree.merge(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(Capacity, Max_size) {
  s21::Multiset<std::string> s = {{"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
                                  {"fifty"}, {"sixty"},  {"seventy"}};
  std::multiset<std::string> b = {{"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
                                  {"fifty"}, {"sixty"},  {"seventy"}};

  EXPECT_EQ(s.max_size(), b.max_size());
}

TEST(MultisetLookup, Count) {
  s21::Multiset<double> v = {1, 1,  2, 1,  2,  -3, 20, -5,
                             1, -6, 8, 42, 26, 8,  8,  8};
  std::multiset<double> vc = {1, 1,  2, 1,  2,  -3, 20, -5,
                              1, -6, 8, 42, 26, 8,  8,  8};

  EXPECT_EQ(v.count(1), vc.count(1));
  EXPECT_EQ(v.count(2), vc.count(2));
  EXPECT_EQ(v.count(8), vc.count(8));
  EXPECT_EQ(v.count(-6), vc.count(-6));
  EXPECT_EQ(v.count(-100), vc.count(-100));
}

TEST(MultisetLookup, Lower_bound) {
  s21::Multiset<double> v = {1, 1,  2, 1,  2,  -3, 20, -5,
                             1, -6, 8, 42, 26, 8,  8,  8};

  ASSERT_EQ(*(v.lower_bound(8)), 8);
  ASSERT_EQ(*(v.lower_bound(2)), 2);
  ASSERT_EQ(*(v.lower_bound(-3)), -3);
  ASSERT_EQ(*(v.lower_bound(20)), 20);

  ASSERT_EQ(*(v.lower_bound(-2)), 1);
  ASSERT_EQ(*(v.lower_bound(38)), 42);
  ASSERT_EQ(*(v.lower_bound(-12)), -6);
}

TEST(MultisetLookup, Upper_bound) {
  s21::Multiset<double> v = {1, 1,  2, 1,  2,  -3, 20, -5,
                             1, -6, 8, 42, 26, 8,  8,  8};

  ASSERT_EQ(*(v.upper_bound(-2)), 1);
  ASSERT_EQ(*(v.upper_bound(14)), 20);
  ASSERT_EQ(*(v.upper_bound(38)), 42);
  ASSERT_EQ(*(v.upper_bound(26)), 42);
}

TEST(MultisetLookup, Equal_range) {
  s21::Multiset<double> v = {1, 1,  2, 1,  2,  -3, 20, -5,
                             1, -6, 8, 42, 26, 8,  8,  8};

  ASSERT_EQ(*(v.equal_range(-2).first), 1);
  ASSERT_EQ(*(v.equal_range(-2).second), 1);

  ASSERT_EQ(*(v.equal_range(-3).first), -3);
  ASSERT_EQ(*(v.equal_range(-3).second), 1);

  ASSERT_EQ(*(v.equal_range(-5).first), -5);
  ASSERT_EQ(*(v.equal_range(-5).second), -3);
}

TEST(MultisetModifiers, Emplace) {
  s21::Multiset<double> v = {1, 1,  2, 1,  2,  -3, 20, -5,
                             1, -6, 8, 42, 26, 8,  8,  8};
  std::multiset<double> vc = {1, 1,  2, 1,  2,  -3, 20, -5,
                              1, -6, 8, 42, 26, 8,  8,  8};
  v.emplace(15);
  vc.emplace(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();

  for (; y != vc.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }

  v.clear();
  vc.clear();

  for (; y != vc.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
