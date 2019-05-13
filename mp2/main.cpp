#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using namespace std;

//#include "cs225/catch/catch.hpp"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma; alma.readFromFile("tests/alma.png");

  Image pineapple; pineapple.readFromFile("tests/pineapple.png");
  pineapple.scale(0.1);
  Image apple; apple.readFromFile("tests/apple.png");
  apple.scale(0.1);
  Image pencil; pencil.readFromFile("tests/pencil.png");
  pencil.scale(0.08);
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(pineapple, 300, 10);
  sheet.addSticker(apple, 540, 10);
  sheet.addSticker(pencil, 350, 200);
  sheet.render().writeToFile("myImage.png");
  return 0;
  
 
}
