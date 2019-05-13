
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png; png.readFromFile("tests/fb3.png");

  FloodFilledImage image(png);
  DFS dfs(png, Point(200,200), 0.6);
  HSLAPixel color(240, 1, 0.5);
  SolidColorPicker solid(color);
  image.addFloodFill(dfs, solid);
//  Animation animation = image.animate(1000);


  DFS bfs(png, Point(300,300), 0.01);
  HSLAPixel color2(80, 1, 0.8);
  SolidColorPicker solid2(color2);
  image.addFloodFill(bfs, solid2);
  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
