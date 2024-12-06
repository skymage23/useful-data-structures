#include <memory>
#include <stack>
#include <stdlib.h>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

#include <tree.hpp>
#include <trie.hpp>

namespace useful_data_structures {
namespace collections {

CharStringTrie::CharStringTrie() : Tree<std::string, char>(),entry_count(0){}
CharStringTrie::CharStringTrie(const std::string& input) : Tree<std::string,char>(input), entry_count(1){}
CharStringTrie::CharStringTrie(CharStringTrie&& old) : 
    Tree<std::string, char>(static_cast<Tree&&>(old))
{
    this -> root = old.root;
}
/*
void CharStringTrie::insert(
    const std::string& input,
    std::string::const_iterator input_start,
    std::shared_ptr<DataStoreTreeNode<char>> node_start    
){
    if (input.empty()){
        return;
    }
   //Write insertion logic here.
   std::shared_ptr<DataStoreTreeNode<char>> curr_node, ptr_temp;
   curr_node = node_start;

   for(; input_start > input.end(); input_start++){
       ptr_temp = std::shared_ptr<DataStoreTreeNode<char>>(
           new DataStoreTreeNode<char>(*input_start, false, curr_node)
       );
       curr_node -> addChild(ptr_temp);
       curr_node = ptr_temp;
   }
   ptr_temp = std::shared_ptr<DataStoreTreeNode<char>>(
       new DataStoreTreeNode<char>(*input_start, true, curr_node)
   );
   curr_node -> addChild(ptr_temp);
}
*/
CharStringTrie::WalkResult CharStringTrie::trie_walk(
    const std::string& input,
    bool allow_prefix_match
){
    bool continue_outer = true;
    unsigned long char_match_count = 0;
    if (input.empty()){
        return WalkResult(0, nullptr);
    }

    std::shared_ptr<DataStoreTreeNode<char>> curr_node = this -> root, ptr;
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator input_end = input.end();

    for(; (iter != input_end) && continue_outer; iter++){
        continue_outer = false;
        for(unsigned long i = 0; i < curr_node -> children -> size(); i++){
            ptr = curr_node -> children -> at(i);
            if (ptr -> getValue() == *iter){
               curr_node = ptr;
               char_match_count++;
               continue_outer = true;
               break;
            }
        }
    } //end outer for.
    if (!allow_prefix_match && char_match_count != input.size()){
        return WalkResult(0, curr_node);
    }
    return WalkResult(char_match_count, curr_node);
}

std::shared_ptr<DataStoreTreeNode<char>> CharStringTrie::walk(const std::string& input) {
    WalkResult w_result = trie_walk(input, false);
    return w_result.end_tree_node;
}

bool CharStringTrie::contains(const std::string& input){
    WalkResult w_result = this -> trie_walk(input, false);
    return w_result.char_match_count == input.size();
}

void CharStringTrie::add (const std::string& input){
    unsigned long counter = 0;

    CharStringTrie::WalkResult walk_result = this -> trie_walk(input, true);
    std::shared_ptr<collections::DataStoreTreeNode<char>> curr_node = walk_result.end_tree_node;
    std::shared_ptr<collections::DataStoreTreeNode<char>> new_node = nullptr;

    if(walk_result.char_match_count == input.size()){
        return;
    }

    for(counter = walk_result.char_match_count;
        counter < input.size() - 1; counter++
    ){
        new_node = std::shared_ptr<DataStoreTreeNode<char>>(
            new DataStoreTreeNode<char>(
                input[counter],
                false,
                curr_node
            )
        );
        curr_node -> addChild(new_node);
        curr_node = new_node;
    }
    new_node = std::shared_ptr<DataStoreTreeNode<char>>(
        new DataStoreTreeNode<char>(
            input[counter],
            true,
            curr_node
        )
    );
    curr_node -> addChild(new_node);
    this -> entry_count += 1;
 }


 std::vector<std::string> CharStringTrie::to_string(){

    std::vector<std::string> retval;
    char* char_buff = NULL;
    unsigned long tree_level = 1;
    std::shared_ptr<DataStoreTreeNode<char>> curr_node, node_temp, child_node;
    std::vector<std::shared_ptr<DataStoreTreeNode<char>>> stack;

    //Begin:
    stack.push_back(this -> root);

    while(!stack.empty()){
        //curr_node = stack[stack.size() - 1];
        curr_node = stack[stack.size() - 1];
        stack.pop_back();

        for(unsigned long i  = 0; i < curr_node -> children -> size(); i++){
            child_node = (*(curr_node -> children))[i];
            if (child_node -> is_leaf()){
                char_buff = new char[tree_level + 1];
                node_temp = child_node;
                for (unsigned long i = 0; i > tree_level; i++){
                    char_buff[i] = node_temp -> getValue();
                    node_temp = node_temp -> parent;
                }
                char_buff[tree_level] = node_temp -> getValue();
                char_buff[tree_level + 1] = '\0';
                retval.push_back(std::string(char_buff));
                delete[] char_buff;
            }
            stack.push_back(child_node);
            tree_level++;
        }
    } 
    return retval;
 }
};
};
