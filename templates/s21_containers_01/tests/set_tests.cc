#include <gtest/gtest.h>

#include <initializer_list>
#include <iostream>
#include <set>
#include <vector>

#include "../s21_containers.h"

TEST(SetConstructor, Default) {
  s21::Set<std::string> s;
  std::set<std::string> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(SetIterator,
     initializer_list_operator_dereferencing_plusplus_minusminus_begin_end) {
  s21::Set<int> s = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  std::set<int> b = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

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

TEST(SetConstructors, Copy) {
  s21::Set<int> s_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  s21::Set<int>& cp_s_tree(s_tree);

  std::set<int> o_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};
  std::set<int> cp_o_tree = o_tree;

  auto si = cp_s_tree.begin();
  auto oi = cp_o_tree.begin();
  for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
  EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
}

TEST(SetConstructors, Move) {
  s21::Set<int> s_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};
  s21::Set<int> mv_s_tree = std::move(s_tree);

  std::set<int> o_tree = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};
  std::set<int> mv_o_tree = std::move(o_tree);

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

TEST(SetConstructors, Operator_equal) {
  s21::Set<int> m1 = {{10}, {20}, {30}, {40}, {50}, {60}, {70}};

  s21::Set<int>& m2 = m1;

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
  s21::Set<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  std::set<std::string> o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
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

TEST(SetLookup, Find) {
  s21::Set<std::string> s1 = {{"zero"},  {"one"},  {"two"}, {"three"},
                              {"four"},  {"five"}, {"six"}, {"seven"},
                              {"eight"}, {"nine"}};

  std::set<std::string> s2 = {{"zero"},  {"one"},  {"two"}, {"three"},
                              {"four"},  {"five"}, {"six"}, {"seven"},
                              {"eight"}, {"nine"}};

  EXPECT_EQ(*s1.find("zero"), *s2.find("zero"));
  EXPECT_EQ(*s1.find("seven"), *s2.find("seven"));
}

TEST(SetLookup, Contains) {
  s21::Set<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.contains("zero"), true);
  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

TEST(SetModifiers, Insert) {
  s21::Set<std::string> s_tree
      // ;
      = {{"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
         {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::set<std::string> o_tree
      // ;
      = {{"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
         {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  s_tree.clear();
  o_tree.clear();

  auto s_pr = s_tree.insert({"one"});
  auto o_pr = o_tree.insert("one");
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"ten", 10});
  o_pr = o_tree.insert({"ten", 10});
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"twelve", 20});
  o_pr = o_tree.insert({"twelve", 20});
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"thirty", 30});
  o_pr = o_tree.insert({"thirty", 30});
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(Modifiers, Swap) {
  s21::Set<std::string> f_s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  s21::Set<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  std::set<std::string> f_o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  std::set<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
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
  s21::Set<int> m1a{{1}, {5}, {10}};
  s21::Set<int> m1b{{2}, {4}, {5}, {8}};
  s21::Set<int> u1;

  std::set<int> m2a{{1}, {5}, {10}};
  std::set<int> m2b{{2}, {4}, {5}, {8}};
  std::set<int> u2;
  u1.merge(m1a);
  u2.merge(m2a);

  auto i1 = u1.begin();
  auto i2 = u2.begin();
  for (; i1 != u1.end() && i2 != u2.end(); ++i1, ++i2) {
    EXPECT_EQ((*i1), (*i2));
  }

  s21::Set<std::string> f_s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  s21::Set<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  std::set<std::string> f_o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  std::set<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
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

TEST(SetCapacity, Max_size) {
  s21::Set<std::string> s = {{"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
                             {"fifty"}, {"sixty"},  {"seventy"}};
  std::set<std::string> b = {{"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
                             {"fifty"}, {"sixty"},  {"seventy"}};

  EXPECT_EQ(s.max_size(), b.max_size());
}

TEST(SetModifiers, Emplace) {
  s21::Set<std::string> s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  std::set<std::string> o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                  {"four"},  {"five"}, {"six"}, {"seven"},
                                  {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto v = s_tree.emplace("eleven", "twelve", "nine", "thirteen");

  auto p0 = o_tree.emplace("eleven");
  auto p1 = o_tree.emplace("twelve");
  auto p2 = o_tree.emplace("nine");
  auto p3 = o_tree.emplace("thirteen");

  EXPECT_EQ((*(v[0].first)), (*(p0.first)));
  EXPECT_EQ(v[0].second, p0.second);

  EXPECT_EQ((*(v[1].first)), (*(p1.first)));
  EXPECT_EQ(v[1].second, p1.second);

  EXPECT_EQ((*(v[2].first)), (*(p2.first)));
  EXPECT_EQ(v[2].second, p2.second);

  EXPECT_EQ((*(v[3].first)), (*(p3.first)));
  EXPECT_EQ(v[3].second, p3.second);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
