#include <cstdlib>
#include <future>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

#include <trie.hpp>

const std::string test_string = "pothead";
const std::string test_string_2 = "tweaker";
const std::string test_string_control = "goon";
bool infinite_loop_detected = false;

class TrieUnitTests : public ::testing::Test{
    protected:
    bool enable_skip = true;

    public:
    void SetUp(){
        char* env_check = getenv("DISABLE_GTEST_SKIP"); 
        enable_skip = (env_check == NULL);
    }
};

TEST(trie_tests, test_insert){
    useful_data_structures::collections::CharStringTrie trie;
    trie.add(test_string);
    ASSERT_TRUE(trie.contains(test_string));
    ASSERT_FALSE(trie.contains(test_string_control));
    
}

TEST_F(TrieUnitTests, test_dump_no_inf_loop){
    bool result;
    useful_data_structures::collections::CharStringTrie object;
    std::promise<std::vector<std::string>> promisedFinished;
    auto futureResult = promisedFinished.get_future();
    std::thread([](std::promise<std::vector<std::string>>& finished,
    useful_data_structures::collections::CharStringTrie & obj) {
       std::vector<std::string> ret = obj.to_string();
       finished.set_value(ret);
    }, std::ref(promisedFinished), std::ref(object)).detach(); 

    result = (
        futureResult.wait_for(std::chrono::milliseconds(100))!= std::future_status::timeout
    );

    infinite_loop_detected = !result;
    EXPECT_TRUE(result);
}


TEST_F(TrieUnitTests, test_dump){
    if((this -> enable_skip) && infinite_loop_detected){
        GTEST_SKIP() << "Infinite loop was detected. This test is pointless until such is fixed.";
    }
    std::unordered_set<std::string> str_set;
    useful_data_structures::collections::CharStringTrie trie;


    trie.add(test_string);
    str_set.insert(test_string);
    trie.add(test_string_2);
    str_set.insert(test_string_2);

    std::vector<std::string> trie_dump = trie.to_string();
//    ASSERT_EQ(trie_dump.size(), str_set.size());

    std::cout << "Trie dump: \n";
    for (auto elem : trie_dump){
        std::cout << elem << "\n";
        ASSERT_TRUE(str_set.contains(elem));
    }

}


TEST_F(TrieUnitTests, test_multistring_insert){
    useful_data_structures::collections::CharStringTrie trie;
    trie.add(test_string);
    trie.add(test_string_2);
    int word_count = trie.get_entry_count();
    ASSERT_EQ(word_count, 2);
    ASSERT_TRUE(trie.contains(test_string));
    ASSERT_TRUE(trie.contains(test_string_2));
    ASSERT_FALSE(trie.contains(test_string_control));
}

