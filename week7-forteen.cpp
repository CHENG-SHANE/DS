#include <iostream>
#include <string>
#include <stack>

using namespace std;

class TreeNode {
public:
    string value;
    TreeNode *left, *right;

    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// 
class ExpressionTree {
private:
    TreeNode *root;
    // 用於構建表達式樹
    TreeNode* constructTree(const string& exp) {
        stack<TreeNode*> st;
        string numberBuffer;  // 用於暫存數字字符串
        // 遍歷表達式字符串
        for (char ch : exp) {
            if (isdigit(ch) || ch == '.') {
                numberBuffer += ch;  // 添加數字或小數點到緩衝區
            } 
            else if (ch == ' ' && !numberBuffer.empty()) {
                // 如果遇到空格且緩衝區有數字，則創建一個新節點
                st.push(new TreeNode(numberBuffer));
                numberBuffer.clear();  // 清空緩衝區以用於下一個數字
            }
            else if (isOperator(ch)) {// 如果遇到運算符
                if (st.size() < 2) {
                    cout << "Invalid expression!" << endl;
                    return nullptr;
                }
                TreeNode *right = st.top();//1
                st.pop();

                TreeNode *left = st.top();//2
                st.pop();

                TreeNode *node = new TreeNode(string(1, ch)); // 創建一個新的節點，其值為當前的運算符//3

                node->left = left;//1
                node->right = right;//2
                st.push(node);// 將運算符節點推入/ /3
            }
        }
        return st.empty() ? nullptr : st.top();
    }

    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

//       *
//      / \
//     +   /
//    / \ / \
//   5  3 6  2
    //((5 + 3 )* (6 / 2 ))
    void inorder(TreeNode* node) {// 左回印
        if (node == nullptr) return;
        bool isOperator = node->value == "+" || node->value == "-" || node->value == "*" || node->value == "/";
        if (isOperator) cout << "(";
        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
        if (isOperator) cout << ")";
    }

    //((5 3 + )(6 2 / )* )
    void preorder(TreeNode* node) {// 遇到節點就印
        if (node == nullptr) return;
        bool isOperator = node->value == "+" || node->value == "-" || node->value == "*" || node->value == "/";
        if (isOperator) cout << "(";
        cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
        if (isOperator) cout << ")";
    }

    //(* (+ 5 3 )(/ 6 2 ))
    void postorder(TreeNode* node) {// 右回印
        if (node == nullptr) return;
        bool isOperator = node->value == "+" || node->value == "-" || node->value == "*" || node->value == "/";
        if (isOperator) cout << "(";
        postorder(node->left);
        postorder(node->right);
        cout << node->value << " ";
        if (isOperator) cout << ")";
    }

    // 用於計算表達式樹的值
    double evaluate(TreeNode* node) {
        if (node == nullptr) return 0;
        // 如果是葉子節點(數字)
        if (!node->left && !node->right){
            return stod(node->value);//stod()將string轉換成double
        }
        double leftVal = evaluate(node->left);//遞迴 左邊
        double rightVal = evaluate(node->right);
        if (node->value == "+") return leftVal + rightVal;
        if (node->value == "-") return leftVal - rightVal;
        if (node->value == "*") return leftVal * rightVal;
        if (node->value == "/") return leftVal / rightVal;
        return 0;
    }
//       *
//      / \
//     +   /
//    / \ / \
//   5  3 6  2
public:
    ExpressionTree(string exp) {
        root = constructTree(exp);
    }
    void inorder() {
        inorder(root);
        cout << endl;
    }
    void postorder() {
        postorder(root);
        cout << endl;
    }
    void preorder() {
        preorder(root);
        cout << endl;
    }
    double evaluate() {
        return evaluate(root);
    }
};

int main() {
    string expression = "5 3 + 6 2 / *";
    ExpressionTree tree(expression);

    cout << "Inorder Traversal: ";
    tree.inorder();
    cout << endl;

    cout << "Preorder Traversal: ";
    tree.preorder();
    cout << endl;

    cout << "Postorder Traversal: ";
    tree.postorder();
    cout << endl;

    cout << "Evaluated Result: " << tree.evaluate() << endl;
    cout << endl;





    string decimalExpression = "5.3 3 + 6 2 / *";
    ExpressionTree Tree(decimalExpression);

    cout << "Inorder Traversal (Decimal): ";
    Tree.inorder();
    cout << endl;

    cout << "Preorder Traversal (Decimal): ";
    Tree.preorder();
    cout << endl;

    cout << "Postorder Traversal (Decimal): ";
    Tree.postorder();
    cout << endl;

    cout << "Evaluated Result (Decimal): " << Tree.evaluate() << endl;

    return 0;
}