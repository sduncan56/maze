
#include "Pathfinding.h"

node::node()
{
	open = false;
	closed = false;
	parent = NULL;
	F = H = G = 0;
}


Pathfinding::Pathfinding()
{

}

void Pathfinding::initSSpace(Area* area)
{
	_area = area;

	Vec2 size = area->getSize();


	searchSpace.resize(size.y);
	for (int i = 0; i < size.y; i++)
	{
		searchSpace[i].resize(size.x);
	}

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			node Node = node();
			if (area->checkColTile(Point(j, i)))
			{
				Node.walkable = false;
			}
			else{
				Node.walkable = true;
			}
			Node.x = j;
			Node.y = i;


			searchSpace[j][i] = Node;
		}
	}

}

int Pathfinding::calcG(int x, int y, node* curNode)
{
	if (x != curNode->x && y != curNode->y)
	{
		return 1400;
	}
	else {
		return 10;
	}
}

void Pathfinding::calcFGH(int x, int y, node *childNode, node* curNode, node* goalNode)
{
	childNode->G = calcG(x, y, curNode);

	childNode->H = (std::abs(goalNode->x - x) + std::abs(goalNode->y - y)) * 10;
	childNode->F = childNode->G + childNode->H;
}


void Pathfinding::getPath(std::vector<Point> *path, node *Node)
{
	path->push_back(Point(Node->x, Node->y));

	if (Node->parent != NULL)
	{
		getPath(path, Node->parent);
	}

	return;
}

std::vector<Point> Pathfinding::search(Point start, Point goal)
{
	std::vector<node*> openList;
	std::vector<node*> closedList;
	std::vector<node*>::iterator i;

	std::vector<Point> path;

	

	node* curNode;
	node* childNode;

	node* startNode = &searchSpace[start.x][start.y];
	node* goalNode = &searchSpace[goal.x][goal.y];

	

	openList.push_back(startNode);
	startNode->open = true;

	while (true)
	{
		int savedF = -1;
		for (auto &node : openList)
		{
			if (node->F < savedF || savedF == -1)
			{
				curNode = node;
				savedF = node->F;
			}
		}

		if (curNode == goalNode)
		{
			break;
		}



		openList.erase(std::remove(openList.begin(), openList.end(), curNode), openList.end());
		curNode->closed = true;
		curNode->open = false;


		for (int x = curNode->x - 1; x < curNode->x + 2; x++)
		{
			for (int y = curNode->y - 1; y < curNode->y + 2; y++)
			{
				if (x == curNode->x && y == curNode->y)
					continue;

				if (x < 0 || y < 0)
					continue;

				childNode = &searchSpace[x][y];

				if (childNode->closed || !childNode->walkable)
					continue;

				if (childNode->open)
				{
					if (childNode->G > calcG(x, y, curNode))
					{
						childNode->parent = curNode;
						calcFGH(x, y, childNode, curNode, goalNode);
					}
				}
				else
				{
					openList.push_back(childNode);
					childNode->open = true;
					childNode->parent = curNode;
					calcFGH(x, y, childNode, curNode, goalNode);
				}
			}
		}
	}

	while (curNode->parent != NULL && curNode != startNode)
	{
		path.push_back(Point(curNode->x, curNode->y));
		curNode = curNode->parent;
	}

	reset();

	return path;
}

Point Pathfinding::findRandWalkableNode()
{
	node Node;
	
	while (true)
	{
        Node = searchSpace[rand() % searchSpace.size()][rand() % searchSpace.size()];

		if (Node.walkable)
			break;
	}

	return Point(Node.x, Node.y);
}

void Pathfinding::reset()
{
	for (int i = 0; i < searchSpace.size(); i++)
	{
		for (int j = 0; j < searchSpace[i].size(); j++)
		{
			searchSpace[i][j].F = searchSpace[i][j].G = searchSpace[i][j].H = 0;
			searchSpace[i][j].closed = searchSpace[i][j].open = false;
			searchSpace[i][j].parent = NULL;
		}
	}
}


bool Pathfinding::checkWalkable(Point tileCoords)
{
	//auto tileCoords = _area->posToTileCoord(mapCoords);

	if (searchSpace[tileCoords.x][tileCoords.y].walkable)
	{
		return true;
	}
	return false;
}
