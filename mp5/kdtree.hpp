/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <stack>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] < second[curDim]) { return true; }
     if (first[curDim] > second[curDim]) { return false; }
     return first < second;
     //return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

      double distance1_sq = distance(currentBest, target);
      double distance2_sq = distance(potential, target);
     if (distance1_sq > distance2_sq) { return true; }
     if (distance1_sq < distance2_sq) { return false;}
     return (potential < currentBest);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     //points_ = newPoints;
     if (newPoints.size() == 0) {
       root = NULL;
       return;
     }
     vector<Point<Dim>> points(newPoints);
     root = buildTree(points, 0, newPoints.size()-1, 0);
     size = newPoints.size();


}

template <int Dim>
 typename KDTree<Dim>::KDTreeNode*  KDTree<Dim>::buildTree(vector<Point<Dim>> & Points, int begin, int end, int dim) {
  if (begin > end ) { return NULL; }
  if (Points.empty()) { return NULL; }
  int mid = (begin + end) / 2;
  quickSelect(Points, begin, end, mid, dim);
  KDTreeNode *node = new KDTreeNode(Points[mid]);
  node -> left = buildTree(Points, begin, mid-1, (dim+1)%Dim);
  node -> right = buildTree(Points, mid+1, end, (dim+1)%Dim);
  return node;

}

template <int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>> & Points, int begin, int end, int k, int dim) {
  if (begin == end) { return; }
  if (begin > end) { return; }
  if (Points.empty()) { return; }
  int partIDX = partition(Points, begin, end, (begin + end)/2, dim);
  if ( partIDX == k) { return; }
  else if ( partIDX > k) { return quickSelect(Points, begin, partIDX - 1, k, dim); } // kth smallest (mid) is on the left
  else if ( partIDX < k) { return quickSelect(Points, partIDX + 1, end, k, dim); } //kth smallest is on the right

}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & Points, int begin, int end, int pivotIDX, int dim) {
  Point<Dim> pivot =  Points[pivotIDX];
  int partIDX = begin;
  std::swap( Points[pivotIDX],  Points[end]);
  for (int j = begin; j < end; j++) {
    if (smallerDimVal( Points[j], pivot, dim)) {
      std::swap( Points[partIDX],  Points[j]);
      partIDX++;
    }
  }
  std::swap(Points[partIDX], Points[end]);
  return partIDX;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other)
{
	//@todo Implement this function!
  root = _copy(other.root);
	size = other.size();
}

//helper function - _copy
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::_copy(KDTreeNode * subroot) {
    if (subroot == NULL) { return NULL; }
    KDTreeNode newNode = new KDTreeNode(subroot -> point);
      newNode -> left = _copy(subroot -> left);
      newNode -> right = _copy(subroot -> right);
    return newNode;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != &rhs) {
     _destroy(root);
     root = _copy(rhs.root);
     size = rhs.size();
  //   points_ = rhs.points_;
   }

   return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */

   _destroy(this -> root);
   root = NULL;

}
template <int Dim>
void KDTree<Dim>::_destroy(KDTreeNode * subroot) {
  if (subroot == NULL) { return; }

  _destroy(subroot -> left);
  _destroy(subroot -> right);
  delete subroot;


}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     if (root -> left == NULL && root -> right == NULL) { return root -> point; }
     Point<Dim> childResult;
     Point<Dim> currentBest;
    Point<Dim> TheBest = findNearestNeighbor_(root, query, 0, childResult, currentBest);
    return TheBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor_(const KDTreeNode * subroot, const Point<Dim> target, int dim, Point<Dim> childResult, Point<Dim> currentBest) const{
  // Point<Dim> childResult;
  // Point<Dim> currentBest;
  // Point<Dim> TheBest;
  // Point<Dim> rightResult;
  // Point<Dim> leftResult;
  if(smallerDimVal(target, subroot -> point, dim))
  {
      if (subroot -> left == NULL) {
        childResult = subroot -> point;
        //return childResult;
      } else {
        childResult = findNearestNeighbor_(subroot->left, target, (dim+1)%Dim, childResult, currentBest);
      }

      currentBest = shouldReplace(target, subroot -> point, childResult)? childResult : subroot -> point;

      if (subroot -> right != NULL && distance(target, currentBest) >= std::pow(target[dim] - subroot->point[dim], 2)) {
          childResult = findNearestNeighbor_(subroot->right, target, (dim+1)%Dim, childResult, currentBest);
          currentBest = shouldReplace(target, currentBest, childResult)? childResult : currentBest;
      }
      //else { TheBest = currentBest; }
  }
  else
  {

      if (subroot -> right == NULL) {
        childResult = subroot -> point;
        //return childResult;
      } else {
        childResult = findNearestNeighbor_(subroot->right, target, (dim+1)%Dim, childResult, currentBest);
      }

      currentBest = shouldReplace(target, subroot -> point, childResult)? childResult : subroot -> point;

      if (subroot -> left != NULL && distance(target, currentBest) >= std::pow(target[dim]- subroot->point[dim], 2)) {
          childResult  = findNearestNeighbor_(subroot->left, target, (dim+1)%Dim, childResult, currentBest);
          currentBest = shouldReplace(target, currentBest, childResult)? childResult  : currentBest;
      }
      //else { TheBest = currentBest; }
  }

return  currentBest;

}

template<int Dim>
double KDTree<Dim>:: distance(const Point<Dim>& target, const Point<Dim>& current) const{
  double retdistance = 0.0;
  for (int i=0; i < Dim; i++) {
    retdistance += std::pow(target[i]-current[i], 2);
  }
  return retdistance;
}