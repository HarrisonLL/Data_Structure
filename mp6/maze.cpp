/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <map>
using namespace cs225;

/* Default Constructor */
SquareMaze::SquareMaze () {

}

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    double total = width * height;
    while(total > 0) {
      Hori.push_back(true);
      Vertical.push_back(true);
      total -= 1.0;
    }

    // while not all ceils connected
    // generate two random number as x y coordinates
    // generate random bool (rand()%2) to decide which kind of wall to break
    // if right walls  Hori = false; union sets
    // if down walls   ..

    DisjointSets dsets;
    dsets.addelements(width * height);

    double workCt = width * height - 1.0;
    while(workCt > 0.0) {
        int Xcord = rand() % width;
        int Ycord = rand() % height;
        int rightws = rand() % 2;
        double heibound = height - 1;
        double widbound = width - 1;
        if (rightws == 0 && (int)heibound > Ycord){
        if(dsets.find(Ycord * width_ + Xcord) != dsets.find((Ycord + 1) * width_ + Xcord)) {
             Vertical[Ycord * width_ + Xcord] = false;
             dsets.setunion(Ycord * width_ + Xcord, (Ycord + 1) * width_ + Xcord);
             workCt -= 1.0;
        }
      }
        if(rightws == 1 && (int)widbound > Xcord){
        if(dsets.find(Ycord * width_ + Xcord) != dsets.find(Ycord * width_ + Xcord + 1)) {
          Hori[Ycord * width_ + Xcord] = false;
          dsets.setunion(Ycord * width_ + Xcord, Ycord * width_ + Xcord + 1);
          workCt -= 1.0;
        }
      }
    }

}



bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0 && x != width_ - 1) { // +1 to the x coordinate
      if(Hori[y * width_ + x]){
        return false;
      } else {
        return true;
      }
    }
    if (dir == 1 && y != height_ - 1) { //+1 to the y coordinate
      if(Vertical[y * width_ + x]){
        return false;
      } else {
        return true;
      }
    }
    if (dir == 2 && x != 0) { //-1 to the x coordinate

        if ( x - 1 < 0 || Hori[y * width_ + (x - 1)]) {
          return false;
        } else {
          return true;
        }

    } if (dir == 3 && y != 0) { // -1 to the y coordinate

        if ( y - 1 < 0 || Vertical[(y-1) * width_ + x]) {
          return false;
        }  else {
          return true;
        }

    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if(dir != 0) {
        Vertical[ y * width_ + x] = exists;
    } else{
      Hori[y * width_ + x] = exists;
    }
}


std::vector<int> SquareMaze::solveMaze() {
    std::vector<bool> visited(width_ * height_);
    std::vector<int> lastRow;
    std::map<int, int> steps_; // current, previous
    std::queue<std::pair<int,int>> q_;
    std::pair<int,int> start = std::make_pair(0,0);
    q_.push(start);
    while(!q_.empty()) {
        std::pair<int,int> current = q_.front();
        int x = current.first;
        int y = current.second;
        visited[y* width_ + x] = true;
        q_.pop();
        if (y == height_ - 1) { // bottom
            lastRow.push_back(current.second * width_ + current.first);
        }
        if (canTravel(x, y, 0)&& !visited[current.second * width_ + current.first + 1]) { // right
            visited[current.second * width_ + current.first + 1] = true;
            q_.push(std::make_pair(current.first+1,current.second));
            steps_.insert(std::pair<int, int>(current.second * width_ + current.first + 1, current.second * width_ + current.first));
        }
        if (canTravel(x, y, 1)&& !visited[current.second * width_ + current.first + width_]) {  // down
            visited[current.second * width_ + current.first + width_] = true;
            q_.push(std::make_pair(current.first,current.second + 1));
            steps_.insert(std::pair<int, int>(current.second * width_ + current.first + width_, current.second * width_ + current.first));
        }
        if (canTravel(x, y, 2)&& !visited[current.second * width_ + current.first - 1]) { // left
          visited[current.second * width_ + current.first - 1] = true;
          q_.push(std::make_pair(current.first-1,current.second));
          steps_.insert(std::pair<int, int>(current.second * width_ + current.first - 1, current.second * width_ + current.first));
        }
        if (canTravel(x, y, 3)&& !visited[current.second * width_ + current.first - width_]) { // up
          visited[current.second * width_ + current.first - width_] = true;
          q_.push(std::make_pair(current.first,current.second - 1));
          steps_.insert(std::pair<int, int>(current.second * width_ + current.first - width_, current.second * width_ + current.first));
        }

    }
    std::stack<int> reverseDirs =  backTraverse(lastRow, steps_);
        std::vector<int> dirs;
        while (!reverseDirs.empty()) {
            dirs.push_back(reverseDirs.top());
            reverseDirs.pop();
        }
        return dirs;
    }

    std::stack<int> SquareMaze::backTraverse(std::vector<int> lastRow, std::map<int, int> steps) {

        std::stack<int> reverseDirs;
        double current = lastRow[width_ - 1];
        while (current > 0) {
            double previous = steps[current];
            if ((int)previous == (int)current - 1) { reverseDirs.push(0); }
            else if ((int)previous == (int)current- width_) { reverseDirs.push(1); }
            else if ((int)previous  == (int)current + 1) { reverseDirs.push(2); }
            else if ((int)previous == (int)current+ width_) { reverseDirs.push(3); }
            current = previous;
        }
        return reverseDirs;

    }


PNG* SquareMaze::drawMaze() const {
    PNG *image = new PNG(10*width_+1, 10*height_+1);
    for(int i = (int)image -> width() - 1; i > 9; i--) {
        (image -> getPixel(i,0)).l = 0.0;
    }
    for(int i = (int)image -> height() - 1; i > -1; i--) {
        (image -> getPixel(0,i)).l = 0.0;
    }
    for(int size = 0; size < width_ * height_; size++){
      int Ycord = size/width_;
      int Xcord = size%width_;
      if (Hori[size]) {
          for(int k = 0; k <= 10; k++) {
              (image -> getPixel((Xcord+1)*10, Ycord*10+k)).l = 0.0;
          }
      }

      if (Vertical[size]) {
          for (int k = 0; k <= 10; k++) {
              (image -> getPixel(Xcord*10+k, (Ycord+1)*10)).l = 0.0;
          }
      }
    }
    return image;
}


PNG* SquareMaze::drawMazeWithSolution() {
    PNG * unsolved = drawMaze();
    std::vector<int> solution = solveMaze();

    int x = 5;
    int y = 5;
    HSLAPixel red(0,1,0.5,1);

    for (unsigned i = 0; i < solution.size(); i++) {
      switch (solution[i])
      {

      case 0:

        	for(int j = 0; j <= 10; j++)
            {
              HSLAPixel &pixel = unsolved -> getPixel(x+j,y);
              pixel = red;
        	}
        		x += 10;
        		break;

      case 1:

            for(int j = 0; j <= 10; j++)
            {
                HSLAPixel &pixel = unsolved -> getPixel(x,y+j);
                pixel = red;
            }
            y+=10;
        		break;

      case 2:

            for(int j = 0; j <= 10; j++)
            {
                HSLAPixel &pixel = unsolved -> getPixel(x-j,y);
                pixel = red;
            }
            x-=10;
        		break;

      case 3:

            for(int j = 0; j <= 10; j++)
            {
                HSLAPixel &pixel = unsolved -> getPixel(x,y-j);
                 pixel = red;
            }
            y-=10;
        		break;

      }
    }

    x = x/10;
    y += 5;
    for (int k = 1; k <= 9; k++) {
        HSLAPixel &pixel = unsolved -> getPixel(x*10+k, y);
        pixel.l = 1;
    }

        return unsolved;
}    


std::vector<int> SquareMaze::solveMaze_creative() {

    std::vector<bool> visited(width_ * height_);
    for (unsigned i = 0; i < visited.size(); i++) {
        visited[i] = false;
    }

    std::map<int, int> steps_; // current, previous
    std::queue<int> q_;
    q_.push(0);
    
    while(!q_.empty()) {

        int temp = q_.front();
        visited[temp] = true;
        q_.pop(); 
        int x = temp % width_;
        int y = temp / width_;

        if (canTravel(x, y, 0) && !visited[temp + 1]) { // right
            visited[temp + 1] = true;
            q_.push(temp + 1);
            steps_.insert(std::pair<int, int>(temp + 1, temp));
        }
        if (canTravel(x, y, 1) && !visited[temp + width_]) {  // down
            visited[temp + width_] = true;
            q_.push(temp + width_);
            steps_.insert(std::pair<int, int>(temp + width_, temp));
        }
        if (canTravel(x, y, 2) && !visited[temp - 1]) { // left  
            visited[temp - 1] = true;
            q_.push(temp - 1);
            steps_.insert(std::pair<int, int>(temp - 1, temp));
        }
        if (canTravel(x, y, 3) && !visited[temp - width_]) { // up
            visited[temp - width_] = true;
            q_.push(temp - width_);
            steps_.insert(std::pair<int, int>(temp - width_, temp));
        }

    }
    std::vector<int> dirs;
    int current = width_ * (height_ - 1) + (width_ / 4) ;

    while (current > 0) {
        int previous = steps_[current];
        if (previous + 1 == current) { dirs.push_back(0); }
        else if (previous + width_ == current) { dirs.push_back(1); }
        else if (previous - 1 == current) { dirs.push_back(2); }
        else if (previous - width_ == current) { dirs.push_back(3); }
        current = previous;
    }
    reverse(dirs.begin(), dirs.end());
    return dirs;
}




 PNG* SquareMaze::drawMazeWithSolution_creative() {
    PNG * unsolved = drawMaze();
    std::vector<int> solution = solveMaze_creative();

    int x = 5, y = 5;
    HSLAPixel red(0,1,0.5,1);
    
    for (unsigned i = 0; i < solution.size(); i++) {
      switch (solution[i])
      {

      case 0:

        	for(int j = 0; j <= 10; j++) { unsolved -> getPixel(x+j,y) = red; }
        	x += 10;
        	break;

      case 1:

            for(int j = 0; j <= 10; j++) { unsolved -> getPixel(x,y+j) = red; }
            y+=10;
        	break;

      case 2:

            for(int j = 0; j <= 10; j++) { unsolved -> getPixel(x-j,y)  = red; }
            x-=10;
        	break;

      case 3:

            for(int j = 0; j <= 10; j++) { unsolved -> getPixel(x,y-j) = red; }
            y-=10;
        	break;

      }
    }

    for (int k = 0; k < 10 && y + k < 10*height_; k++) { unsolved -> getPixel(x, y + k) = red; }

    x = x/10;
    y += 5;

    for (int k = 1; k <= 9; k++) { (unsolved -> getPixel(x*10+k, y)).l = 1; }

    return unsolved;
 }