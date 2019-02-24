#include <iostream>
#include <vector>
#include <array>
#include <memory>

using namespace std;

struct Node {
    array<unique_ptr<Node>, 26> list;
    bool is_word = false;
};

class TrieTree {
public:
    TrieTree() {
        root = make_unique<Node>();      
    }

    void insert(const string& item) {
        auto cur =root.get();
        for(const auto& c : item) {
            int i = c - 'a';
            if(!cur->list[i]) {
                cur->list[i] = make_unique<Node>();
            }
            cur = cur->list[i].get();    
        }
        cur->is_word = true;
    }


    bool is_in(const string& item) {
        auto cur = root.get();
        for(const auto& c : item) {
            int i = c - 'a';
            if (!cur->list[i]) return false;
            cur = cur->list[i].get();
        }    
        return cur && cur->is_word;
    }


    void print_tree() {
        string word;
        vector<string> res;
        print_tree_helper(root.get(), word, res);
        for(const auto& w : res) {
            cout << w  << endl;
        }
    }

private:
    void print_tree_helper(const Node* n, string& word, vector<string>& res) {
        if(n && n->is_word) {
            res.push_back(word);
            return;
        }
        for(int i = 0; i < n->list.size(); ++i) {
            if (n->list[i]) {
                word.push_back('a' + i);
                cout << word << endl;
                print_tree_helper(n->list[i].get(), word, res);
                word.pop_back();
            }
        }
    }
    unique_ptr<Node> root;
};

int main() {
    TrieTree t;
    t.insert("abc");
    t.insert("abcd");
    t.insert("abcde");
    cout << "abcde: " << (t.is_in("abcde") ? "True" : "False") << endl;
    t.print_tree();
    return 0;
}
