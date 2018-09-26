#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

void path::BFS(){
	// initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
	
	queue<pair<int, int>> q;
	// mark first one as visited and enqueue it
	V[start.second][start.first] = true;
	q.push(start);
	P[start.second][start.first] = start;


	while (!q.empty()) {
		pair<int, int> parent = q.front();
		q.pop();
		// get all the neighbors
		vector<pair<int, int>> neighborhood = neighbors(parent);
		for (unsigned i = 0; i < neighborhood.size(); i++) {
			// if the neighbours are good, add them to the predecessor vector and the queue
			if (good(V, parent, neighborhood[i])) {
				P[neighborhood[i].second][neighborhood[i].first] = parent;
				q.push(neighborhood[i]);
				V[neighborhood[i].second][neighborhood[i].first] = true;
			}

		}
	}


	pathPts = assemble(P,start,end);
}

PNG path::render(){
	RGBAPixel red(255, 0, 0);

	for (int i = 0; i < pathPts.size(); i++) {
		RGBAPixel* pix = image.getPixel(pathPts[i].first, pathPts[i].second);
		*pix = red;
	}

	return image;

}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
	// next is not in the scope of the image
	if (!isInImage(next)) {
		return false;
	}
	// if already visited, return false
	if (v[next.second][next.first] == true) {
		return false;
	}
	RGBAPixel* currPix = image.getPixel(curr.first, curr.second);
	RGBAPixel* nextPix = image.getPixel(next.first, next.second);	
	// if the colours are close enough (implicitiy they must be in the image, and unvisited)
	if (closeEnough(*currPix, *nextPix)) {
		// close enough, return true
		return true;
	}
	else {
		// not close enough, return false
		return false;
	}

}

bool path::isInImage(pair<int, int> p) {
	if ((p.first >= 0 && p.first < image.width()) && (p.second >= 0 && p.second < image.height()))
		return true;
	else
		return false;
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;
	pair<int, int> above = pair<int, int>(curr.first, curr.second - 1);
	pair<int, int> below = pair<int, int>(curr.first, curr.second + 1);
	pair<int, int> left = pair<int, int>(curr.first - 1, curr.second);
	pair<int, int> right = pair<int, int>(curr.first + 1, curr.second);
	n.push_back(left);
	n.push_back(below);
	n.push_back(right);
	n.push_back(above);
	return n;
}


vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {	
	vector<pair<int, int>> path;
	// if end == start, then return the pixel

	// if there is no path, return the start
	if (p[e.second][e.first] == e) {
		path.push_back(s);
		return path;
	}
	// if one pixel, return the one
	if (e == s) {
		path.push_back(s);
		return path;
	}

	// initally, our current is equal to the end pixel
	pair<int, int> curr = e;
	stack<pair<int, int>> S;

	// else, traverse the vector p, starting with end, finding its predeceessor, all the way until we reach the start pixel
	while (curr != s) {
		S.push(curr);
		curr = p[curr.second][curr.first];
	}
	// push the start pixel once we have reached it
	S.push(s);

	while (!S.empty()) {
		pair<int, int> p = S.top();
		S.pop();
		path.push_back(p);
	}

	return path;


}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
