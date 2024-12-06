#ifndef USEFUL_DATA_STRUCTURES_TRIE
#define USEFUL_DATA_STRUCTURES_TRIE

//Includes:
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tree.hpp>

//Type definitions:
namespace useful_data_structures {
    namespace collections {

class CharStringTrie : public Tree<std::string, char> {

    private:
    struct WalkResult{
        unsigned long char_match_count;
        std::shared_ptr<DataStoreTreeNode<char>> end_tree_node;
        WalkResult(
            unsigned long char_match_count,
            std::shared_ptr<DataStoreTreeNode<char>> end_node
        ){
            this -> char_match_count = char_match_count;
            this -> end_tree_node = end_node;
        }
    };

    private:
    int entry_count;

    //Methods:
    protected:
    WalkResult trie_walk(const std::string& input, bool allow_prefix_match);

/*
    void insert(
        const std::string& input,
        std::string::const_iterator input_start,
        std::shared_ptr<DataStoreTreeNode<char>> node_start    
    );
*/
    public:
    CharStringTrie();
    CharStringTrie(const std::string& input);
    CharStringTrie(CharStringTrie&& old);

    std::shared_ptr<DataStoreTreeNode<char>> walk(const std::string& input) override;
    bool contains(const std::string& input) override;
    void add(const std::string& new_input) override;
    std::vector<std::string> to_string() override;
    int get_entry_count(){ return this -> entry_count; }
};

    };
};
#endif
