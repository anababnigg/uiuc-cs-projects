/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    Node* &node = find(root, key);
    return node->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == nullptr || subtree->key == key) {return subtree;}
    if (key < subtree->key) {return find(subtree->left, key);} 
    else {return find(subtree->right, key);}
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // asking to find position, then add node...
    Node* &node = find(root, key);
    if(node == nullptr) {node = new Node(key, value);}
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // same deal as find() i think
    // check if null, then create new node in subtree, then use insert again
    if(subtree == NULL) {subtree = new Node(key, value);}
    else if (key > subtree->key) {insert(subtree->right, key, value);}
    else if (key < subtree->key) {insert(subtree->left, key, value);}
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // empty?
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    Node* &node = find(subtree, key);
    if (node == nullptr) {return;} 
    else if (node->right == nullptr) {
        Node* temp = node;
        node = node->left;
        delete temp; // no right, replace left
    }
    else if (node->left == nullptr) {
        Node* temp = node;
        node = node->right;
        delete temp; // no left, replace right
    } else { // for two children, use IOP.
        Node* iop = node->left;
        while (iop->right != nullptr) {
            iop = iop->right;
        }
        swap(node, iop); // use swap
        remove(node->left, iop->key); // finally use remove()
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // need to use .first and .second bc not pointer
    BST<K, V> bst;
    for (unsigned int i = 0; i < inList.size(); i++) {
        bst.insert(inList[i].first, inList[i].second);
    }
    return bst;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // make empty histogram for return
    std::vector<int> hist(inList.size(), 0);
    // hint says to use a sorted vector in order to use next_permuation
    std::sort(inList.begin(), inList.end()); //begin and end bc pair
    while (std::next_permutation(inList.begin(), inList.end())) {
        BST<K, V> bst;
        for (unsigned int i = 0; i < inList.size(); i++) {
            bst.insert(inList[i].first, inList[i].second);
        }
        if (bst.height() < (int)hist.size()) {
            hist[bst.height()]++;
        }
    }
    return hist;
}