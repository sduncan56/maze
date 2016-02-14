
#pragma once

#include "Area.h"
#include <cmath>


struct node {
	int x, y;
	float F, G, H;
	bool walkable;
	node* parent;
	bool open, closed;

	node();
};

class Pathfinding
{
private:
	std::vector<std::vector<node> > searchSpace;
	Area* _area;

public:
	Pathfinding();
	void initSSpace(Area* area);
	int calcG(int x, int y, node* curNode);
	void calcFGH(int x, int y, node *childNode, node* curNode, node* goalNode);

	void getPath(std::vector<Point> *path, node *Node);
	std::vector<Point> search(Point start, Point goal);

	Point findRandWalkableNode();
	void reset();

	bool checkWalkable(Point tileCoords);

};