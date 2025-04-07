#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class BSTree
{
public:
    BSTree() : root(nullptr) {}

    void insert(const T &value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            return;
        }
        Node *current = root;
        Node *parent = nullptr;
        while (current != nullptr)
        {
            parent = current;
            if (Compare()(value, current->data))
            {
                current = current->left;
            }
            else if (Compare()(current->data, value))
            {
                current = current->right;
            }
            else
            {
                // Value already exists in the tree, do not insert duplicates
                return;
            }
        }

        if (Compare()(value, parent->data))
        {
            parent->left = new Node(value);
        }
        else
        {
            parent->right = new Node(value);
        }
    }

    void remove(const T &value)
    {
        if (root == nullptr)
            return;
        Node *current = root;
        Node *parent = nullptr;
        while (current != nullptr && current->data != value)
        {
            parent = current;
            if (Compare()(value, current->data))
            {
                current = current->left;
            }
            else if (Compare()(current->data, value))
            {
                current = current->right;
            }
            else
            {
                // Value found, proceed to remove it
                break;
            }
        }
        if (current == nullptr)
            return; // Value not found

        if (current->left != nullptr && current->right != nullptr)
        {

            Node *pre = current->left;
            Node *parent = current;

            while (pre->right != nullptr)
            {
                parent = pre;
                pre = pre->right;
            }
            current->data = pre->data;
            current = pre;
        }

        Node *child = (current->left != nullptr) ? current->left : current->right;

        if (current == root)
        {
            root = child;
        }
        else if (parent->left == current)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }

    bool find(const T &value)
    {
        Node *current = root;
        while (current != nullptr)
        {
            if (Compare()(value, current->data))
            {
                current = current->left;
            }
            else if (Compare()(current->data, value))
            {
                current = current->right;
            }
            else
            {
                return true; // Value found
            }
        }
        return false; // Value not found
    }

private:
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        Node(T value = T()) : data(value), left(nullptr), right(nullptr) {}
    };
    Node *root;
};

int main()
{
    BSTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    std::cout << "Find 3 " << tree.find(3) << std::endl;
    tree.remove(3);
    std::cout << "Find 3 " << tree.find(3) << std::endl;
    return 0;
}
