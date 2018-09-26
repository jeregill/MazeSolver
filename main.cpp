
// File:        main.cpp
// Author:      cheeren
// Date:        2018-03-31
// Description: Partial test of PA4 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "path.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{
	
	PNG origIm1;
	origIm1.readFromFile("images/snake.png");

	
	pair<int,int> start1(2,2);
    pair<int,int> end1(637,477);
	path snake(origIm1,start1,end1);
	PNG out1 = snake.render();
	out1.writeToFile("images/snakePath.png");
	cout << "snake size is " << snake.length() << endl;
	
	PNG origIm2;
	origIm2.readFromFile("images/maze.png");
	pair<int,int> start2(3,10);
    pair<int,int> end2(637,477);
	path maze(origIm2,start2,end2);
	PNG out2 = maze.render();
	out2.writeToFile("images/mazePath.png");
	cout << "maze size is " << maze.length() << endl;
	
	PNG origIm3;
	origIm3.readFromFile("images/sunshine.png");
	pair<int,int> start3(320,420);
    pair<int,int> end3(100,100);
	path sunshine(origIm3,start3,end3);
	PNG out3 = sunshine.render();
	out3.writeToFile("images/sunshinePath.png");
	cout << "sunshine size is " << sunshine.length() << endl;
	
	PNG origIm4;
	origIm4.readFromFile("images/maze1.png");
	pair<int, int> start4(791, 1);
	pair<int, int> end4(808, 1601);
	path maze1(origIm4, start4, end4);
	PNG out4 = maze1.render();
	out4.writeToFile("images/maze1path.png");

	PNG origIm5;
	origIm5.readFromFile("images/maze2.png");
	pair<int, int> start5(145, 145);
	pair<int, int> end5(10, 145);
	path maze2(origIm5, start5, end5);
	PNG out5 = maze2.render();
	out5.writeToFile("images/maze2path.png");

	PNG origIm6;
	origIm6.readFromFile("images/flag.png");
	pair<int, int> start6(1, 1);
	pair<int, int> end6(220, 220);
	path flag(origIm6, start6, end6);
	PNG out6 = flag.render();
	out6.writeToFile("images/flagpath.png");
	cout << "flag size is " << flag.length() << endl;

	

  return 0;
}
