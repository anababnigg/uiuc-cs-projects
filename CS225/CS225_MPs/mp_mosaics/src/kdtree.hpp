/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    
    if (curDim >= Dim || curDim < 0) {return false;}
    if (first[curDim] == second[curDim]) {return first < second;}
    return first[curDim] < second[curDim]; 
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double currDistance = 0;
    double potentialDistance = 0;

    for (unsigned int i = 0; i < Dim; i++) {
      double cbDiff = currentBest[i] - target[i];
      double pDiff = potential[i] - target[i];

      currDistance += cbDiff * cbDiff;
      potentialDistance += pDiff * pDiff;
    }

    if (potentialDistance < currDistance) {return true;}
    if (potentialDistance == currDistance) {return potential < currentBest;}
    return false;
}


// *** CONSTRUCTOR + HELPERS ***
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::quickSelect(vector<Point<Dim>>& points, int left_idx,
                                int right_idx, int med, int d) {
    //quickselect to find median to serve as root of KDTree
    if (points.empty() || left_idx > right_idx) {return NULL;}
    if (left_idx == right_idx) {return new KDTreeNode(points.at(left_idx));} //base case

    //finding pivot index with standard alg
    int pivot_idx = ((right_idx - left_idx) / 2) + left_idx;
    Point<Dim> pivotValue = points.at(pivot_idx);
    std::swap(points[pivot_idx], points[right_idx]);
    int temp_idx = left_idx;
    for (int i = left_idx; i < right_idx; i++) {
        if (smallerDimVal(points.at(i), pivotValue, d)) {
            std::swap(points[temp_idx], points[i]);
            temp_idx++;
        }
    }
    std::swap(points[temp_idx], points[right_idx]);
    pivot_idx = temp_idx;

    // recursive building of subtrees of two halves based on pivot and basic quickselect alg
    if (med == pivot_idx) {
      return new KDTreeNode(points.at(med));
    } else if (med < pivot_idx) {
      return quickSelect(points, left_idx, pivot_idx - 1, med, d);
    } else {
      return quickSelect(points, pivot_idx + 1, right_idx, med, d);
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int left_idx,
                                int right_idx, int d) {
    if (points.empty() || left_idx > right_idx) {return NULL;}
    if (left_idx == right_idx) {return new KDTreeNode(points.at(left_idx));}

    int pivot_idx = ((right_idx - left_idx) / 2) + left_idx;
    KDTreeNode * qs_root = quickSelect(points, left_idx, right_idx, pivot_idx, d);
    qs_root->left = buildTree(points, left_idx, pivot_idx - 1, (d + 1) % Dim);
    qs_root->right = buildTree(points, pivot_idx + 1, right_idx, (d + 1) % Dim);

    return qs_root;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> tempPoints = newPoints;
    size = tempPoints.size();
    root = NULL;
    if (!tempPoints.empty()) {
        root = buildTree(tempPoints, 0, tempPoints.size() - 1, 0);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  root = copyKD(this->root, other.root);
}

template <int Dim>
void KDTree<Dim>::copyKD(KDTreeNode* lhs, KDTreeNode* rhs) {
    lhs = new KDTreeNode();
    lhs->point = rhs->point;
    copyKD(lhs->left, rhs->right);
    copyKD(lhs->right, rhs->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  root = copyKD(root, rhs);
  size = rhs.size;

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* node) { //might be *&
  if (!node) {return;}
  clear(node->left);
  clear(node->right);
  delete node;
}


template <int Dim>
Point<Dim> KDTree<Dim>::nearestNeighborHelper(const Point<Dim>& query, KDTreeNode * curr, int d) const {
    // assume proper KDTree is inputted
    // check for leaf
    if (!curr->left && !curr->right)
        return curr->point;

    Point<Dim> curr_best = curr->point;
    KDTreeNode* next_node = nullptr;
    KDTreeNode* meow = nullptr;

    // first left
    if (smallerDimVal(query, curr->point, d)) {
        next_node = curr->left;
        meow = curr->right;
    } else {
        next_node = curr->right;
        meow = curr->left;
    }

    if (next_node) {
        Point<Dim> temp_best = nearestNeighborHelper(query, next_node, (d + 1) % Dim);
        if (shouldReplace(query, curr_best, temp_best)) {
            curr_best = temp_best;
        }
    }

    if (meow) {
        Point<Dim> check_closer = query;
        check_closer[d] = curr->point[d];
        if (shouldReplace(query, curr_best, check_closer)) {
            Point<Dim> temp_best = nearestNeighborHelper(query, meow, (d + 1) % Dim);
            if (shouldReplace(query, curr_best, temp_best))
                curr_best = temp_best;
        }
    }

    return curr_best;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return nearestNeighborHelper(query, root, 0);
}


template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    //quickselect to find median to serve as root of KDTree
    if (start == end) {return;}

    //finding pivot index with standard alg
    RandIter pivot_idx = start + (end - start) / 2;
    // assign the value at pivot_idx
    typename std::iterator_traits<RandIter>::value_type pivotValue = *pivot_idx; 
    std::swap(*pivot_idx, *(end - 1));
    RandIter temp_idx = start;
    for (RandIter i = start; i < end - 1; i++) {
        // compare the values not  iterators
        if (cmp(*i, pivotValue)) { 
            std::swap(*temp_idx, *i);
            temp_idx++;
        }
    }
    std::swap(*temp_idx, *(end - 1));
    pivot_idx = temp_idx;

    // recursive building of subtrees of two halves based on pivot and basic quickselect alg
    if (k == pivot_idx)
        return;
    else if (k < pivot_idx)
        select(start, pivot_idx, k, cmp);
    else
        select(pivot_idx + 1, end, k, cmp);
}


