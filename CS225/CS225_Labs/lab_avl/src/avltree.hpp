/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = temp;
    temp = NULL;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = temp;
    temp = NULL;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    // 4 cases: LL, LR, RR, RL
    if(!subtree) {return;}
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;

    // find diff of height between subtrees
    int diff = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);

    // LL, LR, RR, RL
    if (diff > 1) {
        if(heightOrNeg1(subtree->left->left) >= heightOrNeg1(subtree->left->right)) {
            rotateRight(subtree);
        } else if (heightOrNeg1(subtree->left->left) < heightOrNeg1(subtree->left->right)) { /*(heightOrNeg1(subtree->left->left) < heightOrNeg1(subtree->left->right)*/
            rotateLeftRight(subtree);
        }
    } else if (diff < -1) {
        if(heightOrNeg1(subtree->right->right) >= heightOrNeg1(subtree->right->left)) {
            rotateLeft(subtree);
        } else if (heightOrNeg1(subtree->right->right) < heightOrNeg1(subtree->right->left)) { /*(heightOrNeg1(subtree->right->right) < heightOrNeg1(subtree->right->left))*/
            rotateRightLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (!subtree) {subtree = new Node(key, value);}
    else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    } else { //if key exists
        subtree->value = value;
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) {return;}
    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* temp = subtree->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            Node* temp = subtree;
            if (subtree->left) {subtree = subtree->left;}
            else if (subtree->right) {subtree = subtree->right;}
            delete temp;
        }
        // your code here
    }
    if (subtree == NULL) {return;}
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    rebalance(subtree);
}
