
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"

using namespace cs225;
using namespace std;

int main()
{
 
	SquareMaze maze1;
	maze1.makeMaze(80,40);
	PNG * maze1_image = maze1.drawMazeWithSolution_creative();
    //maze1_image -> writeToFile("creative1" + string(".png"));

	SquareMaze maze2;
	maze2.makeMaze(40, 80);
	PNG * maze2_image = maze2.drawMazeWithSolution();
	//maze2_image -> writeToFile("creative2" + string(".png"));


	PNG out(800, 1200);
	for (unsigned x = 0; x < 800; x++) {
		for (unsigned y = 0; y < 400; y++) {
			out.getPixel(x,y) = maze1_image -> getPixel(x,y);
		}
	}
	for (unsigned x = 0; x < 400; x++) {
		for (unsigned y = 0; y < 800; y++) {
			out.getPixel(200 + x, 400 + y) = maze2_image -> getPixel(x,y);
		}
	}


	//optimize solution
	HSLAPixel red(0,1,0.5,1);
	HSLAPixel black(0,0,0);
	for (int i = 0; i < 10; i++) { out.getPixel(205, 400+i) = red; } 
	for (int j = 0; j < 200; j++) { out.getPixel(j, 400) = black; }
	for (int k = 600; k < 800; k++) { out.getPixel(k, 400) = black; }
	for (int l = 200; l < 600; l++) { out.getPixel(l, 1199) = black; }
	for (int m = 0; m < 400; m++) { out.getPixel(799, m) = black; }
	for (int n = 400; n < 1200; n++) { out.getPixel(600, n) = black; }

	out.writeToFile("creative" + string(".png"));

    return 0;
}
