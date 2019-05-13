#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <iostream>



using namespace cs225;

// The following functions use this as pointer to point to the PNG instance, same as "this" in java

void Image::lighten () {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;

            }

          }

      }

}

void Image::lighten (double amount) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;

            }

          }

      }

}

void Image::darken() {
    PNG image;
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            pixel.l -= 0.1;
            if (pixel.l < 0 ) {
                pixel.l = 0;
            }


        }
    }
}

void Image::darken(double amount) {
    PNG image;
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            pixel.l -= amount;
            if (pixel.l < 0 ) {
                pixel.l = 0;

            }

            }

        }

}

void Image::saturate() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            if (pixel.s >= 0 && (pixel.s + 0.1) <= 1){
                pixel.s += 0.1;

            }

            }

        }

}

void Image::saturate (double amount) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            if (pixel.s >= 0 && (pixel.s + amount) <= 1){
                pixel.l += amount;

            }
          }

        }
}

void Image::desaturate () {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            if ((pixel.s - 0.1) >= 0 && pixel.s  <= 1){
                pixel.s -= 0.1;

            }
          }
    }
}

void Image::desaturate (double amount) {

    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            if ((pixel.s - amount) >= 0 && pixel.s  <= 1){
                pixel.s -= amount;
            }
          }
      }
}

void Image::grayscale () {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor	(double degrees) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);
                pixel.h += degrees;
                if (pixel.h > 360) {
                    pixel.h = pixel.h - 360;
                }
                if (pixel.h < 0) {
                    pixel.h = 360 + pixel.h;
                }


        }
    }
}

void Image::illinify () {
    int ILorange = 11;
    int ILblue = 216;

    for (unsigned x = 0; x < this ->width(); x++) {
        for (unsigned y = 0; y < this ->height(); y++) {
            HSLAPixel & pixel = this ->getPixel(x,y);
          if (294 < pixel.h || pixel.h < 113) {
            pixel.h = ILorange;
          } else {
           pixel.h = ILblue;
          }
        }
    }
}

void Image::scale(double factor) {

    unsigned int New_width = (this -> width()) * factor;
    unsigned int New_height = (this -> height()) * factor;
    Image Out;
    Out.resize(New_width,New_height);

    if (factor > 1 ) {
        for (unsigned x = 0; x < this ->width(); x++) {
            for (unsigned y = 0; y < this -> height(); y++) {
                HSLAPixel & pixel0 = this -> getPixel(x, y);
                int i = 0;
                unsigned int x_bound = x * factor + (factor - 1);
                unsigned int y_bound = y * factor + (factor - 1);
                while (i < factor && (x_bound < Out.width()) && (y_bound < Out.height())) {
                    Out.getPixel(factor*x + i, factor*y + i) = pixel0;
                    i++;
                }
                //if (((2*x + 1) < this -> width()) && ((2*y + 1) < this -> height())) {
                //    this -> getPixel(2*x, 2*y) = pixel0;
                //    this -> getPixel(2*x + 1, 2*y) = pixel0;
                //    this -> getPixel(2*x, 2*y + 1) = pixel0;
                //    this -> getPixel(2*x + 1, 2*y + 1) = pixel0;
                //}

            }
        }
    }

    if (factor < 1) {
        for (unsigned x = 0; x < Out.width(); x++) {
            for (unsigned y = 0; y < Out.height(); y++) {
                unsigned int xCord = (x/factor + x/factor + (1/factor-1))/2;
                unsigned int yCord = (y/factor + y/factor + (1/factor-1))/2;
                if((xCord < this -> width()) && (yCord < this -> height())) {
                    HSLAPixel & pixel0 = this -> getPixel(xCord, yCord);
                    Out.getPixel(x, y) = pixel0;
                }

            }
        }

    }

    *this = Out;
}

void Image::scale(unsigned w, unsigned h) {

    double factorA = w/(this -> width());
    double factorB = h/(this -> height());
    double factor = std::min(factorA, factorB);

    unsigned int New_width = (this -> width()) * factor;
    unsigned int New_height = (this -> height()) * factor;
    Image Out;
    Out.resize(New_width,New_height);

    if (factor > 1 ) {
        for (unsigned x = 0; x < this ->width(); x++) {
            for (unsigned y = 0; y < this -> height(); y++) {
                HSLAPixel & pixel0 = this -> getPixel(x, y);
                int i = 0;
                unsigned int x_bound = x * factor + (factor - 1);
                unsigned int y_bound = y * factor + (factor - 1);
                while (i < factor && (x_bound < Out.width()) && (y_bound < Out.height())) {
                    Out.getPixel(factor*x + i, factor*y + i) = pixel0;
                    i++;
                }
            }
        }
    }
    if (factor < 1) {
        for (unsigned x = 0; x < Out.width(); x++) {
            for (unsigned y = 0; y < Out.height(); y++) {
                unsigned int xCord = (x/factor + x/factor + (1/factor-1))/2;
                unsigned int yCord = (y/factor + y/factor + (1/factor-1))/2;
                if((xCord < this -> width()) && (yCord < this -> height())) {
                    HSLAPixel & pixel0 = this -> getPixel(xCord, yCord);
                    Out.getPixel(x, y) = pixel0;
                }

            }
        }

    }
    *this = Out;

}
