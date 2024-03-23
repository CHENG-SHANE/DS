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
};

class Trie {
private:
    TrieNode* root;

    void preorder(TrieNode* node, int level) {
        if (node) {
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    for (int j = 0; j < level * 2; ++j) {
                        cout << " ";
                    }
                    cout << char(i + 'a') << endl;
                    preorder(node->children[i], level + 1);
                }
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
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

    void insert(string value) {
        TrieNode* node = root;
        for (char c : value) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->endOfWord = true;
    }

    void preorder() {
        preorder(root, 0);
    }
};


int main()
{
	Trie *trie = new Trie();
	string command, key, value;
	while(1)
	{
		cin>>command;
		if(command == "insert")
		{
			cin>>value;
			trie->insert(value);
		}
		else if(command == "search")
		{
			cin>>key;
			if(trie->search(key))
				cout << "exist" << endl;
			else
				cout << "not exist" << endl;
		}
		else if(command == "print")
		{
			trie->preorder();
		}
		else if(command == "exit")
		{
			break;
		}
	}
    return 0;
}