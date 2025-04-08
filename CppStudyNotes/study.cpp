#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
#include <queue>

template <typename T>
class AVLTree
{
public:
private:
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        int height;
        Node(T value = T()) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    Node *root;

    // 右旋转操作 ，参数y为旋转的轴，返回旋转后的根节点

    Node *rightRotate(Node *father)
    {
        Node *child = father->left;
        father->left = child->right;
        child->right = father;

        father->height = std::max(getHeight(father->left), getHeight(father->right)) + 1;
        child->height = std::max(getHeight(child->left), getHeight(child->right)) + 1;

        return child;
    }
    // 左旋转操作 ，参数y为旋转的轴，返回旋转后的根节点
    Node *leftRotate(Node *father)
    {
        Node *child = father->right;
        father->right = child->left;
        child->left = father;

        father->height = std::max(getHeight(father->left), getHeight(father->right)) + 1;
        child->height = std::max(getHeight(child->left), getHeight(child->right)) + 1;

        return child;
    }

    // 左平衡操作
    Node *leftBalance(Node *node)
    {

        node->left = leftRotate(node->left);
    }
};

int main()
{
}
