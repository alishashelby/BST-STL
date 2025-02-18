#include "../lib/BST.h"
#include <gtest/gtest.h>

class BSTTest : public ::testing::Test {
protected:
    BST<int> bst;
};

TEST_F(BSTTest, DefaultConstructor) {
    EXPECT_EQ(bst.size(), 0);
    EXPECT_TRUE(bst.empty());
}

TEST_F(BSTTest, CopyConstructor) {
    BST<int> bst1 = {20, 23, 28};
    BST<int> bst2(bst1);

    ASSERT_EQ(bst2.size(), bst1.size());
}

TEST_F(BSTTest, RangeConstructor) {
    BST<int> bst(6, 15);
    EXPECT_EQ(bst.size(), 9);
    for (int i = 6; i < 15; ++i) {
        EXPECT_TRUE(bst.find(i) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, ListConstructor) {
    BST<int> bst({20, 25, 13});
    EXPECT_EQ(bst.size(), 3);
    std::initializer_list<int> il = {20, 25, 13};
    for (const auto& val : il) {
        EXPECT_TRUE(bst.find(val) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, InitializerListConstructor) {
    std::initializer_list<int> il = {20, 25, 13, 15};
    BST<int> bst = il;
    EXPECT_EQ(bst.size(), 4);
    for (const auto& val : il) {
        EXPECT_TRUE(bst.find(val) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, AssignmentOperator) {
    BST<int> bst2 = {1, 5};
    BST<int> bst1(20, 25);
    std::initializer_list<int> il = {20, 21, 22, 23, 24};
    bst2 = bst1;
    EXPECT_EQ(bst2.size(), bst1.size());
    for (const auto& val : il) {
        EXPECT_TRUE(bst2.find(val) != bst2.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, SelfAssignmentOperator) {
    BST<int> bst1(20, 25);
    bst1 = bst1;
    EXPECT_EQ(bst1.size(), 5);
}

TEST_F(BSTTest, InitializerListAssignmentOperator) {
    BST<int> bst = {10, 4, 11};
    EXPECT_EQ(bst.size(), 3);

    bst = {3, 4, 5, 6};
    EXPECT_EQ(bst.size(), 4);

    for (int i = 3; i <= 6; ++i) {
        EXPECT_TRUE(bst.find(i) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, EmptyInitializerListAssignmentOperator) {
    BST<int> bst = {};
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
}

TEST_F(BSTTest, EqualTrueOperator) {
    BST<int> bst1({-1, 0, 1});
    BST<int> bst2(-1, 2);
    EXPECT_TRUE(bst1 == bst2);
    EXPECT_FALSE(bst1 != bst2);
}

TEST_F(BSTTest, EqualFalseOperator) {
    BST<int> bst1= {1, 5};
    BST<int> bst2(1, 2);
    EXPECT_FALSE(bst1 == bst2);
    EXPECT_TRUE(bst1 != bst2);
}

TEST_F(BSTTest, EmptyEqualOperator) {
    BST<int> bst1= {};
    BST<int> bst2;
    EXPECT_TRUE(bst1 == bst2);
    EXPECT_FALSE(bst1 != bst2);
}

TEST_F(BSTTest, merge) {
    BST<int> bst = {20, 23, 6, 2, 3, 9, 25};
    BST<int> bst2({40, 11, 2, 45});
    bst.merge(bst2);

    BST<int> expected_bst({20, 6, 2, 3, 9, 11, 23, 25, 40, 45});

    ASSERT_EQ(bst.size(), expected_bst.size());
    EXPECT_TRUE(bst2.empty());
    EXPECT_TRUE(expected_bst == bst);
}

TEST_F(BSTTest, swap) {
    BST<int> bst1(3, 10);
    std::initializer_list<int> il = {10, 14, 11};
    BST<int> bst2 = il;
    bst1.swap(bst2);
    EXPECT_EQ(bst1.size(), 3);
    EXPECT_EQ(bst2.size(), 7);

    for (int i = 3; i < 10; ++i) {
        EXPECT_TRUE(bst2.find(i) != bst2.end<TraverseTag::In>());
    }
    for (const auto& val : il) {
        EXPECT_TRUE(bst1.find(val) != bst1.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, EmptySwap) {
    BST<int> bst1(3, 10);
    BST<int> bst2;
    swap(bst1, bst2);
    EXPECT_EQ(bst1.size(), 0);
    EXPECT_EQ(bst2.size(), 7);

    EXPECT_TRUE(bst1.empty());
    for (int i = 3; i < 10; ++i) {
        EXPECT_TRUE(bst2.find(i) != bst2.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, clear) {
    BST<int> bst(1, 10);
    EXPECT_FALSE(bst.empty());

    bst.clear();
    EXPECT_TRUE(bst.empty());
    ASSERT_TRUE(bst.size() == 0);
}

TEST_F(BSTTest, insert_check) {
    auto it = bst.insert_check(3);
    EXPECT_TRUE(it.second);
    EXPECT_EQ(*it.first, 3);
    EXPECT_EQ(bst.size(), 1);

    it = bst.insert_check(3);
    EXPECT_FALSE(it.second);
    EXPECT_EQ(*it.first, 3);
    EXPECT_EQ(bst.size(), 1);

    it = bst.insert_check(2);
    EXPECT_TRUE(it.second);
    EXPECT_EQ(*it.first, 2);
    EXPECT_EQ(bst.size(), 2);

    it = bst.insert_check(4);
    EXPECT_TRUE(it.second);
    EXPECT_EQ(*it.first, 4);
    EXPECT_EQ(bst.size(), 3);

    for (int i = 2; i <= 4; ++i) {
        EXPECT_TRUE(bst.find(i) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, insert) {
    auto it = bst.insert(1);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(bst.size(), 1);

    it = bst.insert(2);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(bst.size(), 2);

    it = bst.insert(1);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(bst.size(), 2);

    for (int i = 1; i <= 2; ++i) {
        EXPECT_TRUE(bst.find(i) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, insertInitializerList) {
    bst.insert({20, 25, 13, 15});
    EXPECT_EQ(bst.size(), 4);

    std::initializer_list<int> il = {20, 25, 13, 15};
    for (const auto& val : il) {
        EXPECT_TRUE(bst.find(val) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, insertRange) {
    bst.insert(1, 15);
    EXPECT_EQ(bst.size(), 14);

    for (int i = 1; i < 15; ++i) {
        EXPECT_TRUE(bst.find(i) != bst.end<TraverseTag::In>());
    }
}

TEST_F(BSTTest, extract) {
    bst.insert(2);
    EXPECT_EQ(bst.size(), 1);
    bst.insert(1);
    EXPECT_EQ(bst.size(), 2);

    auto extracted = bst.extract(2);
    EXPECT_EQ(extracted.key, 2);
    
    EXPECT_EQ(bst.size(), 1);
    EXPECT_TRUE(bst.find(2) == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, eraseExisted) {
    bst.insert({13, 10, 140, 15});
    EXPECT_EQ(bst.size(), 4);

    size_t k = bst.erase(13);
    EXPECT_EQ(k, 1);
    EXPECT_EQ(bst.size(), 3);
    EXPECT_TRUE(bst.find(13) == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, eraseNotExisted) {
    bst.insert({13, 10, 140, 15});
    EXPECT_EQ(bst.size(), 4);

    size_t k = bst.erase(1);
    EXPECT_EQ(k, 0);
    EXPECT_EQ(bst.size(), 4);
    EXPECT_TRUE(bst.find(1) == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, eraseEmptyIterator) {
    auto it = bst.end<TraverseTag::In>();
    auto next = bst.erase(it);
    EXPECT_EQ(next, bst.end<TraverseTag::In>());
    EXPECT_EQ(bst.size(), 0);
}

TEST_F(BSTTest, eraseInIterator) {
    bst.insert(25);
    bst.insert(11);
    bst.insert(26);
    auto it = bst.find(11);
    auto next = bst.erase(it);
    EXPECT_EQ(next, bst.find(25));
    EXPECT_EQ(bst.size(), 2);
}

TEST_F(BSTTest, erasePreIterator) {
    bst = {20, 23, 1, 2, 3, 6, 9};
    auto it = bst.begin<TraverseTag::Pre>();
    auto expected = it;
    ++expected;
    auto next = bst.erase<TraverseTag::Pre>(it);
    EXPECT_EQ(next, expected);
    EXPECT_EQ(bst.size(), 6);
}

TEST_F(BSTTest, erasePostIterator) {
    bst.insert({10, 8, 15, 6, 9, 11, 20});
    auto it = bst.begin<TraverseTag::Post>();
    ++it;
    auto expected = it;
    ++expected;
    auto next = bst.erase<TraverseTag::Post>(it);
    EXPECT_EQ(next, expected);
    EXPECT_EQ(bst.size(), 6);
}

TEST_F(BSTTest, findExisted) {
    bst = {40, 11, 8, 45, 5};
    auto expected = bst.begin<TraverseTag::In>();
    auto it = bst.find(5);
    EXPECT_EQ(expected, it);
}

TEST_F(BSTTest, findNotExisted) {
    bst = {40, 11, 8, 45, 1};
    auto it = bst.find(2);
    EXPECT_TRUE(it == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, lower_boundExisted) {
    bst = {13, 45, -1, 3, 14};
    auto it = bst.lower_bound(3);
    EXPECT_EQ(*it, -1);
}

TEST_F(BSTTest, lower_boundExistedNullptr) {
    bst = {13, 45, -1, 3, 14};
    auto it = bst.lower_bound(-1);
    EXPECT_TRUE(it == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, lower_boundNotExisted) {
    bst = {13, 45, -1, 3, 14};
    auto it = bst.lower_bound(5);
    EXPECT_TRUE(it == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, upper_boundExisted) {
    bst = {13, 45, -1, 3, 14};
    auto it = bst.upper_bound(13);
    EXPECT_EQ(*it, 14);
}

TEST_F(BSTTest, upper_boundExistedNullptr) {
    bst = {13, 45, -1, 3, 14};
    auto it = bst.upper_bound(45);
    EXPECT_TRUE(it == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, upper_boundNotExisted) {
    bst = {13, 45, -1, 3, 14};
    auto it = bst.upper_bound(2);
    EXPECT_TRUE(it == bst.end<TraverseTag::In>());
}

TEST_F(BSTTest, beginAndcbeginIn) {
    bst = {20, 23, 1, 2, 3, 6, 9};
    auto it1 = bst.begin<TraverseTag::In>();
    EXPECT_EQ(*it1, 1);

    auto it2 = bst.cbegin<TraverseTag::In>();
    EXPECT_EQ(*it2, 1);

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, beginAndcbeginPre) {
    bst = {20, 23, 6, 2, 3, 1, 9};
    auto it1 = bst.begin<TraverseTag::Pre>();
    EXPECT_EQ(*it1, 20);

    auto it2 = bst.cbegin<TraverseTag::Pre>();
    EXPECT_EQ(*it2, 20);

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, beginAndcbeginPost) {
    bst = {20, 23, 6, 2, 3, 9, 25};
    auto it1 = bst.begin<TraverseTag::Post>();
    EXPECT_EQ(*it1, 3);

    auto it2 = bst.cbegin<TraverseTag::Post>();
    EXPECT_EQ(*it2, 3);

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, endAndcendInAndIncrement) {
    bst = {14, 12, 13, 17, 20, 18, 5, 4, 10};
    auto it1 = bst.begin<TraverseTag::In>();
    for (int i = 0; i < 9; ++i) {
        ++it1;
    }
    EXPECT_EQ(it1, bst.end<TraverseTag::In>());

    auto it2 = bst.cbegin<TraverseTag::In>();
    for (int i = 0; i < 9; ++i) {
        ++it2;
    }
    EXPECT_EQ(it2, bst.cend<TraverseTag::In>());

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, endAndcendPreAndIncrement) {
    bst = {14, 12, 13, 17, 20, 18, 5, 4, 10};
    auto it1 = bst.begin<TraverseTag::Pre>();
    for (int i = 0; i < 9; ++i) {
        ++it1;
    }
    EXPECT_EQ(it1, bst.end<TraverseTag::Pre>());

    auto it2 = bst.cbegin<TraverseTag::Pre>();
    for (int i = 0; i < 9; ++i) {
        ++it2;
    }
    EXPECT_EQ(it2, bst.cend<TraverseTag::Pre>());

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, endAndcendPostAndIncrement) {
    bst = {14, 12, 13, 17, 20, 18, 5, 4, 10};
    auto it1 = bst.begin<TraverseTag::Post>();
    for (int i = 0; i < 9; ++i) {
        ++it1;
    }
    EXPECT_EQ(it1, bst.end<TraverseTag::Post>());

    auto it2 = bst.cbegin<TraverseTag::Post>();
    for (int i = 0; i < 9; ++i) {
        ++it2;
    }
    EXPECT_EQ(it2, bst.cend<TraverseTag::Post>());

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, rbeginAndcrbeginIn) {
    bst = {20, 23, 1, 2, 3, 6, 9};
    auto it1 = bst.rbegin<TraverseTag::In>();
    EXPECT_EQ(*it1, 23);

    auto it2 = bst.crbegin<TraverseTag::In>();
    EXPECT_EQ(*it2, 23);

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, rbeginAndcrbeginPre) {
    bst = {20, 23, 21, 6, 2, 3, 25, 1, 9};
    auto it1 = bst.rbegin<TraverseTag::Pre>();
    EXPECT_EQ(*it1, 25);

    auto it2 = bst.crbegin<TraverseTag::Pre>();
    EXPECT_EQ(*it2, 25);

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, rbeginAndcrbeginPost) {
    bst = {20, 23, 6, 2, 3, 9, 25};
    auto it1 = bst.rbegin<TraverseTag::Post>();
    EXPECT_EQ(*it1, 20);

    auto it2 = bst.crbegin<TraverseTag::Post>();
    EXPECT_EQ(*it2, 20);

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, rendAndcrendInAndIncrement) {
    bst = {14, 12, 13, 17, 20, 18, 5, 4, 10};
    auto it1 = bst.rbegin<TraverseTag::In>();
    for (int i = 0; i < 9; ++i) {
        ++it1;
    }
    EXPECT_EQ(it1, bst.rend<TraverseTag::In>());

    auto it2 = bst.crbegin<TraverseTag::In>();
    for (int i = 0; i < 9; ++i) {
        ++it2;
    }
    EXPECT_EQ(it2, bst.crend<TraverseTag::In>());

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, rendAndcrendPreAndIncrement) {
    bst = {14, 12, 13, 17, 20, 18, 5, 4, 10};
    auto it1 = bst.rbegin<TraverseTag::Pre>();
    for (int i = 0; i < 8; ++i) {
        ++it1;
    }
    EXPECT_EQ(it1, bst.rend<TraverseTag::Pre>());

    auto it2 = bst.crbegin<TraverseTag::Pre>();
    for (int i = 0; i < 8; ++i) {
        ++it2;
    }
    EXPECT_EQ(it2, bst.crend<TraverseTag::Pre>());

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, rendAndcrendPostAndIncrement) {
    bst = {14, 12, 13, 17, 20, 18, 5, 4, 10};
    auto it1 = bst.rbegin<TraverseTag::Post>();
    for (int i = 0; i < 9; ++i) {
        ++it1;
    }
    EXPECT_EQ(it1, bst.rend<TraverseTag::Post>());

    auto it2 = bst.crbegin<TraverseTag::Post>();
    for (int i = 0; i < 9; ++i) {
        ++it2;
    }
    EXPECT_EQ(it2, bst.crend<TraverseTag::Post>());

    EXPECT_EQ(it1, it2);
}

TEST_F(BSTTest, Inorder) {
    bst = {15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0};
    std::stringstream expected;
    expected << "0 3 5 6 7 8 9 10 11 12 13 15 16 17 18 ";

    std::stringstream output;
    for (auto it = bst.begin<TraverseTag::In>(); it != bst.end<TraverseTag::In>(); ++it) {
        output << *it << " ";
    }
    EXPECT_EQ(bst.size(), 15);
    EXPECT_EQ(expected.str(), output.str());

    std::stringstream c_output;
    for (auto it = bst.cbegin<TraverseTag::In>(); it != bst.cend<TraverseTag::In>(); ++it) {
        c_output << *it << " ";
    }
    EXPECT_EQ(expected.str(), c_output.str());
}

TEST_F(BSTTest, ReversedInorder) {
    bst = {15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0};
    std::stringstream expected;
    expected << "18 17 16 15 13 12 11 10 9 8 7 6 5 3 0 ";

    std::stringstream output;
    for (auto it = bst.rbegin<TraverseTag::In>(); it != bst.rend<TraverseTag::In>(); ++it) {
        output << *it << " ";
    }
    EXPECT_EQ(bst.size(), 15);
    EXPECT_EQ(expected.str(), output.str());

    std::stringstream c_output;
    for (auto it = bst.crbegin<TraverseTag::In>(); it != bst.crend<TraverseTag::In>(); ++it) {
        c_output << *it << " ";
    }
    EXPECT_EQ(expected.str(), c_output.str());
}

TEST_F(BSTTest, Preorder) {
    bst = {15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0};
    std::stringstream expected;
    expected << "15 5 3 0 8 7 6 11 9 10 12 13 16 18 17 ";

    std::stringstream output;
    for (auto it = bst.begin<TraverseTag::Pre>(); it != bst.end<TraverseTag::Pre>(); ++it) {
        output << *it << " ";
    }
    EXPECT_EQ(bst.size(), 15);
    EXPECT_EQ(expected.str(), output.str());

    std::stringstream c_output;
    for (auto it = bst.cbegin<TraverseTag::Pre>(); it != bst.cend<TraverseTag::Pre>(); ++it) {
        c_output << *it << " ";
    }
    EXPECT_EQ(expected.str(), c_output.str());
}

TEST_F(BSTTest, ReversedPreorder) {
    bst = {15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0};
    std::stringstream expected;
    expected << "17 18 16 13 12 10 9 11 6 7 8 0 3 5 ";

    std::stringstream output;
    for (auto it = bst.rbegin<TraverseTag::Pre>(); it != bst.rend<TraverseTag::Pre>(); ++it) {
        output << *it << " ";
    }
    EXPECT_EQ(bst.size(), 15);
    EXPECT_EQ(expected.str(), output.str());

    std::stringstream c_output;
    for (auto it = bst.crbegin<TraverseTag::Pre>(); it != bst.crend<TraverseTag::Pre>(); ++it) {
        c_output << *it << " ";
    }
    EXPECT_EQ(expected.str(), c_output.str());
}

TEST_F(BSTTest, Postorder) {
    bst = {15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0};
    std::stringstream expected;
    expected << "0 3 6 7 10 9 13 12 11 8 5 17 18 16 15 ";

    std::stringstream output;
    for (auto it = bst.begin<TraverseTag::Post>(); it != bst.end<TraverseTag::Post>(); ++it) {
        output << *it << " ";
    }
    EXPECT_EQ(bst.size(), 15);
    EXPECT_EQ(expected.str(), output.str());

    std::stringstream c_output;
    for (auto it = bst.cbegin<TraverseTag::Post>(); it != bst.cend<TraverseTag::Post>(); ++it) {
        c_output << *it << " ";
    }
    EXPECT_EQ(expected.str(), c_output.str());
}

TEST_F(BSTTest, ReversedPostorder) {
    bst = {15, 5, 16, 18, 17, 8, 3, 11, 7, 9, 6, 12, 13, 10, 0};
    std::stringstream expected;
    expected << "15 16 18 17 5 8 11 12 13 9 10 7 6 3 0 ";

    std::stringstream output;
    for (auto it = bst.rbegin<TraverseTag::Post>(); it != bst.rend<TraverseTag::Post>(); ++it) {
        output << *it << " ";
    }
    EXPECT_EQ(bst.size(), 15);
    EXPECT_EQ(expected.str(), output.str());

    std::stringstream c_output;
    for (auto it = bst.crbegin<TraverseTag::Post>(); it != bst.crend<TraverseTag::Post>(); ++it) {
        c_output << *it << " ";
    }
    EXPECT_EQ(expected.str(), c_output.str());
}
