#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(): traversal_(NULL) {
  /** @todo [Part 1] */
  END = true;


}

ImageTraversal::Iterator::Iterator(PNG image, Point start, double tol, ImageTraversal * trav) {
  image_ = image;
  start_ = start;
  current_ = start;
  tolerance_ = tol;
  traversal_ = trav;

  int width = (int)image_.width();
  int height = (int)image_.height();
  visited.resize(width);
  for(auto &y: visited) {
    y.resize(height);
  }

  for (int i = 0; i < (int)image_.width(); i++) {
    for (int j = 0; j < (int)image_.height(); j++) {
      visited[i][j] = false;
    }
  }


  //check if the point addable: tolerance, and out of bound?
  if (visitThisPoint_(start_, current_)) {
      visited[current_.x][current_.y] = (true);
  } else {
    END = true;
  }

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point left = Point(current_.x - 1, current_.y);
  Point right = Point(current_.x + 1, current_.y);
  Point above = Point(current_.x, current_.y - 1);
  Point below = Point(current_.x, current_.y + 1);


  std::vector<Point> temp;
  temp.push_back(right);
  temp.push_back(below);
  temp.push_back(left);
  temp.push_back(above);

  for (auto elem : temp) {
    if (visitThisPoint_(start_, elem)) { traversal_ -> add(elem);}
  }


  if (traversal_ -> empty()) {      //check if traversal is empty, END
    END = true;
    return *this;

  } else {    //  check if visited, if not, start = next, if so,  move to next
    Point next_ = traversal_ -> pop();
    while (visited[next_.x][next_.y]) {
      if (traversal_-> empty()) {
        END = true;
        return *this;
      }
      if (traversal_ == NULL) {
        END = true;
        return *this;
      }
      next_ = traversal_ -> pop();
    }
  //  cout << "here00000000" << endl;
    visited[next_.x][next_.y] = true;
    current_ = next_;
    return *this;
  }

}


bool ImageTraversal::Iterator::visitThisPoint_(Point start, Point a) {
  if (a.x >= image_.width() || a.y >= image_.height()) { return false; }
  HSLAPixel &startPixel = image_.getPixel(start.x, start.y);
  HSLAPixel &aPixel = image_.getPixel(a.x, a.y);
  if (calculateDelta(startPixel, aPixel) < tolerance_) { return true; }
  return false;

}



/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */

  /** @todo [Part 1] */
Point ImageTraversal::Iterator::operator*() {
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (this -> END != other.END) { return true; }
  return false;
}
