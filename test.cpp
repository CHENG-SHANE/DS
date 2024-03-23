#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool endOfWord;

    TrieNode() : endOfWord(false) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }

    int countChildren() {
        int count = 0;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (children[i]) {
                count++;
            }
        }
        return count;
    }
};

class Trie {
private:
    TrieNode* root;

    void preorder(TrieNode* node, int level, bool isFirstChild) {
        if (node) {
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    if(level == 0 && node!=nullptr){
                        cout << endl << endl ;
                    }
                    if (level != 0 && (node->countChildren() >= 2)) {
                        cout << endl;
                        for (int j = 0; j < level * 2; ++j) {
                            cout << " ";
                        }
                    }
                    cout << char(i + 'a');
                    preorder(node->children[i], level + 1, i == 0);
                }
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string key) {
        TrieNode* node = root;
        for (char c : key) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->endOfWord = true;
    }

    bool search(string key) {
        TrieNode* node = root;
        for (char c : key) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return node != nullptr && node->endOfWord;
    }

    void preorder() {
        preorder(root, 0, true);
    }
};

int main() {
    Trie trie;
    string command, value;
    while (true) {
        cin >> command;
        if (command == "insert") {
            cin >> value;
            trie.insert(value);
        }
        else if (command == "search") {
            cin >> value;
            if (trie.search(value))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        }
        else if (command == "print") {
            trie.preorder();
        }
        else if (command == "exit") {
            break;
        }
    }
    return 0;
}
