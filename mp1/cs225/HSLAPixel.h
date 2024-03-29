/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
class HSLAPixel {

/* public attributes */
public:

    double h;
    double s;
    double l;
    double a;

/* Constructor */
    HSLAPixel();

    HSLAPixel(double hue, double saturation, double luminance);

    HSLAPixel(double hue, double saturation, double luminance, double alpha);


};
}


#endif