#include <memory>
#include <vector>


#include <error_handling/exceptions.hpp>

#ifndef USEFUL_DATA_STRUCTURES_TREE
#define USEFUL_DATA_STRUCTURES_TREE


namespace useful_data_structures {
    namespace collections {
        template <typename T> class DataStoreTreeNode {
            private:
            bool leaf;
            T value;

            public:
            std::shared_ptr<std::vector<std::shared_ptr<DataStoreTreeNode<T>>>> children;
            std::shared_ptr<DataStoreTreeNode<T>> parent;

            //protected:
            public:
            DataStoreTreeNode() = delete;
            DataStoreTreeNode(T value, bool leaf, const std::shared_ptr<DataStoreTreeNode> parent){
                this -> parent = parent;
                this -> leaf = leaf;
                this -> value = value;
                this -> children = std::shared_ptr<
                    std::vector<std::shared_ptr<DataStoreTreeNode<T>>>
                >(new std::vector<std::shared_ptr<DataStoreTreeNode<T>>>());
            }
             
            DataStoreTreeNode(DataStoreTreeNode&& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> leaf = input.leaf;
                this -> value = input.value;
            }

            DataStoreTreeNode(DataStoreTreeNode& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> leaf = input.leaf;
                this -> value = value;
            }

            bool is_leaf(){ return this -> leaf; }
            void addChild(std::shared_ptr<DataStoreTreeNode<T>> child){
                this -> children -> push_back(child);
            }

            T getValue() {
                return value;
            }
        };

        // T = externally expected API type.
        // U = internal representation type.
        // The two are not always the same.
        template <typename T, typename U> class Tree {
            protected:
            std::shared_ptr<DataStoreTreeNode<U>> root;

            public:
            Tree() {
                this -> root = std::shared_ptr<DataStoreTreeNode<char>>(
                    new DataStoreTreeNode<char>(
                        '\0',
                        false,
                        nullptr
                    )
                );
            }

            Tree(Tree&& input) {
                this -> root = input.root;
            }

            Tree(const T& input) {
                this -> add(input);
            }

            virtual std::shared_ptr<DataStoreTreeNode<U>> walk(
                __attribute__((unused)) const T& input
            ){
                throw new useful_data_structures::error_handling::NotImplementedException();
            };

            virtual bool contains(
                __attribute__((unused)) const T& input
            ) { 
                throw new useful_data_structures::error_handling::NotImplementedException();
            }

            virtual void add( __attribute__((unused)) const T& input){
                throw new useful_data_structures::error_handling::NotImplementedException();
            }
            virtual std::vector<std::string> to_string(){
                throw new useful_data_structures::error_handling::NotImplementedException();
            };
        };
    };
};
#endif
