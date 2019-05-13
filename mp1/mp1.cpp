#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <time.h>
#include <math.h>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
PNG png1;
png1.readFromFile(inputFile);

int widIDX = png1.width() - 1;
int heiIDX = png1.height() - 1;
PNG png2 = PNG(png1.width(), png1.height());

  for (unsigned x = 0; x < png1.width(); x++) {
    for (unsigned y = 0; y < png1.height(); y++) {
       HSLAPixel & pixel = png1.getPixel(x, y);
       HSLAPixel & pixel2 = png2.getPixel(widIDX - x , heiIDX - y);
       pixel2 = pixel;

      // png2.getPixel(widIDX - x, heiIDX - y) = pixel;
    }
  }
png2.writeToFile(outputFile);

}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  //background
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
    HSLAPixel & pixel = png.getPixel(x,y);
    pixel.h = 340 - (0.1 * y + 0.1 * x);
    pixel.s = 1;
    pixel.l = 0.5;
    pixel.a = 1;
    }
  }
 
//first two large squares 

  for (unsigned x = png.width()*(0.25); x < png.width()*(0.5); x++) {
    for (unsigned y = png.height()*(0.25); y < png.height()*(0.5);y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 330 - (0.1 * y + 0.1 * x);
      pixel.s = 1;
      pixel.l = 0.5;
      pixel.a = 1;
    }
  }

 for (unsigned x = png.width()*(0.5); x < png.width()*(0.75);x++) {
    for (unsigned y = png.height()*(0.5); y < png.height()*(0.75);y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 220 + (0.05 * y + 0.05 * x);
      pixel.s = 1;
      pixel.l = 0.5;
      pixel.a = 1;
    }
  }
 //underneath circle 
  double radius = (0.25) * png.width();
  double centerX = (0.5) * png.width();
  double centerY = (0.5) * png.height();
 for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel& pixel = png.getPixel(x,y);
      double distance = sqrt((x - centerX)*(x - centerX) +(y - centerY)*(y - centerY));
      if (distance <= radius) {
        pixel.h = 200 + 0.05 * y;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }
    }
  }
//next two smaller squares 
  for (unsigned x = png.width()*(0.5); x < png.width()*(0.625); x++) {
    for (unsigned y = png.height()*(0.375); y < png.height()*(0.5);y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 200;
      pixel.s = 0.8;
      pixel.l = 1;
      pixel.a = 1;
    }
  }
 for (unsigned x = png.width()*(0.375); x < png.width()*(0.5);x++) {
    for (unsigned y = png.height()*(0.5); y < png.height()*(0.625);y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.h = 200;
      pixel.s = 0.8;
      pixel.l = 1;
      pixel.a = 1;
    }
  }


  return png;
}
