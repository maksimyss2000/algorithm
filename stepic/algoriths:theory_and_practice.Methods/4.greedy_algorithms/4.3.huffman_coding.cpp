#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <map> 
#include <stack>

struct  Node {
    Node* left;
    Node* right;
    char  value;
    int   weight;
};

struct myComp {
    constexpr bool operator() (
        Node* const& a,
        Node* const& b)
        const noexcept
    {
        return a->weight > b->weight;
    }
};

class TreeHuffman {
    private:
        Node* tree;
        std::map<char, int> frequency_book;
        std::map<char, std::string> coding_book;
        std::priority_queue<Node*, std::vector<Node*>, myComp> haffman_queue;
    public:
        void calculateFrequencyChar(std::string& message) {
            for (const auto& elem: message) {
                frequency_book[elem] += 1;
            }
        }

        void makeStartPriorityQueue() {
                for (const auto &elem: frequency_book) {
                    haffman_queue.push(new Node{nullptr, nullptr, elem.first, elem.second});
                }
                /*
                while (!haffman_queue.empty()) {
                    std::cout << haffman_queue.top()->value << ' ' << haffman_queue.top()->weight << std::endl;
                    haffman_queue.pop();
                }
                */
                
        }

        void makeTree() {
            while (haffman_queue.size() > 1){
                auto first  = haffman_queue.top();  haffman_queue.pop();
                auto second = haffman_queue.top();  haffman_queue.pop();
                haffman_queue.push(new Node{first, second, '\0', first->weight + second->weight});   
            }
            tree = haffman_queue.top();  haffman_queue.pop(); /* After that we do not use the queue */
        }

        void print_node(Node* root, int space = 0) {
            for (int i = 5; i < space; i++) {
                std::cout << " ";
            }
            std::cout << root->value  <<":" << root->weight << "\n";
        }

        void printTreeRecursing(Node* root, int space = 0) {
            if (root == nullptr) {
                return;
            }
            space += 5;
            printTreeRecursing(root->right, space);
            print_node(root, space);
            printTreeRecursing(root->left, space);
        }

        void printTreeIterative(Node* root) {
            std::stack<std::pair<Node*,int>>  stack;
            std::pair<Node*, int> current(root, 0);
            while (current.first != nullptr || stack.empty() == false ) {
                while (current.first != nullptr) {
                    current.second += 5;
                    stack.push(current);
                    current.first = current.first -> right;
                }
                current = stack.top();
                stack.pop();
                print_node(current.first, current.second);
                current.first = current.first ->left;
            }
        }

        bool is_leaf(Node* root) {
                return root->left == nullptr && root->right == nullptr;
        }

        void makeBookCodingRecursing(Node* root, std::string code = "") { 
            if (is_leaf(root)) {
                coding_book[root->value] = code;
                return;
            }
            makeBookCodingRecursing(root->right, code + '1');
            makeBookCodingRecursing(root->left,  code + '0');
        }
    
        void makeBookCodingIterative(Node* root) {
            std::stack<std::pair<Node*, std::string>>  stack;
            std::pair<Node*, std::string> current(root, "");
            while (current.first != nullptr || stack.empty() == false ) {

                while (current.first != nullptr) {
                    stack.push(current);
                    current.first = current.first -> right;
                    current.second += '1';
                }

                current = stack.top();
                stack.pop();
                if (current.first != nullptr && is_leaf(current.first)) {
                    coding_book[current.first->value] = current.second;
                }
                current.first = current.first ->left;
                current.second += '0';
            }
        }

        void print_result_for_stepic(std::string& message) {
            std::string result = "";
            for (const auto& elem: message) {
                result += coding_book[elem];
            }
            std::cout << coding_book.size()  << " " << result.length() << std::endl;
            for(const auto & variable_name : coding_book){
                std::cout << variable_name.first << ": " << variable_name.second << std::endl; 
            }
            std::cout << result;
        }

        TreeHuffman(std::string& message) {
            calculateFrequencyChar(message);
            makeStartPriorityQueue();
            makeTree();
            //printTreeRecursing(tree);
            //printTreeIterative(tree);
            /* 
            * We must handle the trivial case where input string is a single character
            * It is a feature of this algorithm. It does not need to be reworked. 
            */
            if (tree->left == nullptr && tree->left == nullptr) {
                 coding_book[tree->value] = "0";
            } else {
                makeBookCodingIterative(tree);
            }

            print_result_for_stepic(message);
        }
};

int main() {
    std::string message;
    getline(std::cin, message);
    TreeHuffman algorithm(message);
    return 0;
}
