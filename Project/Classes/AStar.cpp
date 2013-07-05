/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This scene shows the user instructions on how to play.

==CHANGELOG==
2013-05-31 - Got the algorithm fully working. - Joseph
**/

#include "AStar.h"

// Pre-define the neighboring tiles checked by the A* algorithm.
static const int NUMBER_ADJACENT_TILES = 4;
static const int ADJACENT_TILES[4][2] = { {0,1}, {-1,0}, {1,0}, {0,-1} };
/**
 * Create a new autoreleased node at the given tile position.
 */
AStarNode* AStarNode::nodeAtPoint(cocos2d::CCPoint pos)
{
	AStarNode* tmp = new AStarNode();
	tmp->initAtPoint(pos);
	return tmp;
}

/**
 * Initialize the node at the given tile position;
 **/
AStarNode* AStarNode::initAtPoint(cocos2d::CCPoint pos)
{
	point = pos;
	x = pos.x;
	y = pos.y;
	return this;
}

// the calculated cost of the node.
int AStarNode::cost()
{
	return G + H;
}

AStar::AStar(cocos2d::CCTMXTiledMap* aTileMap, const char* name, const char* collide_prop_name, const char* collide_prop_value)
{
	tileMap = aTileMap;
	groundLayer = aTileMap->layerNamed(name);
	collideKey = collide_prop_name;
	collideValue = collide_prop_value;
	addCollideLayer(name);
	
	if(tileMap == NULL || groundLayer == NULL)
	{
		printf("ERROR! NULL ground layer.\n");
	}
}

AStarNode* AStar::findPathFrom(cocos2d::CCPoint src, cocos2d::CCPoint dst)
{
#ifdef DEBUGGING
	printf("Finding path from (%f, %f) to (%f, %f)\n", src.x, src.y, dst.x, dst.y);
#endif
	openNodes.clear();
	closedNodes.clear();
	
	src = tileCoordForPos(src);
	dst = tileCoordForPos(dst);
	

	if (isCollision(dst))
	{
		return NULL;
	}
	
	AStarNode *origin = AStarNode::nodeAtPoint(src);
	origin->parent = NULL;
	openNodes.insert(origin);

	AStarNode *closestNode = NULL;
	while (openNodes.size() != 0)
	{
		closestNode = lowCostNode();
		if (closestNode->point.x == dst.x && closestNode->point.y == dst.y)
		{
#ifdef DEBUGGING
			printf("Found path!\n");
#endif
			return closestNode;
		}
		openNodes.erase(closestNode);
		closedNodes.insert(closestNode);
		
		for (int i = 0; i < NUMBER_ADJACENT_TILES; i++)
		{
			int x = ADJACENT_TILES[i][0];
			int y = ADJACENT_TILES[i][1];

			AStarNode *adjacentNode = AStarNode::nodeAtPoint(ccp(x + closestNode->point.x, y + closestNode->point.y));
			adjacentNode->parent = closestNode;
			

			// Skip over this node if its already been closed.
			if (closedNodes.find(adjacentNode) != closedNodes.end())
			{
				continue;
			}

			// Skip over collide nodes, and add them to the closed set.
			if (isCollision(adjacentNode->point))
			{
				closedNodes.insert(adjacentNode);
				continue;
			}

			// Calculate G
			adjacentNode->G = 10 + closestNode->G;
			
			// If the node is already in the open set, check and see if going
			// through the current node is a better path.

			if (openNodes.find(adjacentNode) != openNodes.end())
			{
				AStarNode *otherNode = *openNodes.find(adjacentNode);
				int newCost = otherNode->G - otherNode->parent->G + closestNode->G;
				if (newCost < otherNode->G)
				{
					otherNode->G = newCost;
					otherNode->parent = closestNode;
				}
			}
			else
			{
				adjacentNode->H = (abs(adjacentNode->point.x - dst.x) + abs(adjacentNode->point.y - dst.y)) * 10;
				openNodes.insert(adjacentNode);
			}
		}
	}
	
	return NULL;
}

void AStar::getPath(cocos2d::CCPoint start, cocos2d::CCPoint end, std::list<cocos2d::CCPoint*>& paths)
{
	AStarNode *node = findPathFrom(start, end);
	std::vector<cocos2d::CCPoint*> nodesTemp;
	while(node != NULL)
	{
		cocos2d::CCPoint* tmp = node->createPoint();
		positionForTileCoord(*tmp);
		nodesTemp.push_back(tmp);
		node = node->parent;
	}
	
	for(int i = 0; i < nodesTemp.size(); i++)
	{
		paths.push_front(nodesTemp[i]);
	}
}

/**
void AStar::moveSprite:(CCSprite*)sprite
				 from:(cocos2d::CCPoint)src to:(cocos2d::CCPoint)dst atSpeed:(float)speed
{

	NSArray *nodes = [self getPath:src to:dst];
	if ([nodes count] == 0)
		return;

	NSMutableArray *actionList = [NSMutableArray array];

	int tileWidthOffset = [tileMap tileSize].width / 2;
	int tileHeightOffset = [tileMap tileSize].height / 2;

	for(AStarNode *node in nodes)
	{
		cocos2d::CCPoint p1 = [groundLayer
			positionAt:node->point];
		p1.x = p1.x + tileWidthOffset;
		p1.y = p1.y + tileHeightOffset;
		
		CCAction *move = [CCMoveTo actionWithDuration: speed position: p1];
		[actionList addObject:move];
	}
	[sprite runAction:[CCSequence actionsWithArray:actionList]];
}**/
/**
void AStar::addCollideLayer(const char* name)
{
	cocos2d::CCTMXLayer *layer = tileMap->layerNamed(name);
	if (layer != NULL)
	{
		collideLayers.insert(layer);
	}
}

void AStar::removeCollideLayer(const char* name)
{
	cocos2d::CCTMXLayer *layer = tileMap->layerNamed(name);
	if(layer != NULL)
	{
		collideLayers.erase(layer);
	}
}
**/
bool AStar::isCollision(cocos2d::CCPoint point)
{
	if (point.x >= groundLayer->getLayerSize().width || point.x < 0)
	{
		printf("x out of bounds %f %f\n", point.x, groundLayer->getLayerSize().width);
		return true;
	}			
			
	if (point.y >= groundLayer->getLayerSize().height || point.y < 0)
	{
		printf("y out of bounds\n");
		return true;
	}
	
	std::set<cocos2d::CCTMXLayer*>::iterator it;
	for(it = collideLayers.begin(); it != collideLayers.end(); it++)
	{
		cocos2d::CCTMXLayer *collideLayer = *it;
		// Check for a tile in the collide layer.
		unsigned int tileGid = collideLayer->tileGIDAt(point);
		if (tileGid != 0)
		{
			//printf("checking if collide.\n");
			// If a tile exists, see if collide is enabled on the entire layer.
			cocos2d::CCString* ldict = collideLayer->propertyNamed(collideKey);
			if (ldict != NULL)
			{
				//printf("Collide enabled\n");
				return true;
			}
			// If not, then check the tile for the collide property.
			cocos2d::CCDictionary *dict = tileMap->propertiesForGID(tileGid);
			if (dict != NULL)
			{
				const cocos2d::CCString *collide = dict->valueForKey(collideKey);
				if (collide != NULL && collide->compare(collideValue) == 0)
				{
								//printf("tile collide enabled\n");
					return true;
				}
			}
		}
	}
	return false;
}

AStarNode* AStar::lowCostNode()
{
	AStarNode* lowCostNode = NULL;
	
	for(std::set<AStarNode*>::iterator it = openNodes.begin();
		it != openNodes.end();
		it++)
	{
		AStarNode* otherNode = *it;
		
		if(lowCostNode == NULL)
		{
			lowCostNode = *it;
			continue;
		}
		
		if(	otherNode->cost() < lowCostNode->cost() || 
			(otherNode->cost() == lowCostNode->cost() && otherNode->H < lowCostNode->H))
		{
			lowCostNode = otherNode;
		}
	}
	return lowCostNode;
}

cocos2d::CCPoint AStar::tileCoordForPos(cocos2d::CCPoint position)
{
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return ccp(x, y);
}
void AStar::positionForTileCoord(cocos2d::CCPoint& tileCoord) {
	tileCoord.x = (tileCoord.x * tileMap->getTileSize().width) + tileMap->getTileSize().width/2;
	tileCoord.y = (tileMap->getMapSize().height * tileMap->getTileSize().height) - (tileCoord.y * tileMap->getTileSize().height) - tileMap->getTileSize().height/2;
}
