
#include <list>
#include "cocos2d.h"

#ifndef ASTAR_H
#define ASTAR_H


/**
* A structure for storing a A* node
*/
class AStarNode
{
	public:
		int x;
		int y;
  		AStarNode *parent;
  		cocos2d::CCPoint point;
		int F;
		int G;
		int H;
		
		/**
		 * Create a new autoreleased node at the given tile position.
		 */
		static AStarNode* nodeAtPoint(cocos2d::CCPoint pos);
		
		/**
		 * Initialize the node at the given tile position;
		 **/
		AStarNode* initAtPoint(cocos2d::CCPoint pos);
		
		// the calculated cost of the node.
		int cost();
		
		
		cocos2d::CCPoint* createPoint() const
		{
			cocos2d::CCPoint* pt = new cocos2d::CCPoint(point);
			pt->retain(); // Don't kill this!
			
			return pt;
		}
};

struct astarnode_compare {
    bool operator() (AStarNode* lhs, AStarNode* rhs) const{
        int one = lhs->x * 10000 + lhs->y;
        int two = rhs->x * 10000 + rhs->y;
        
        return one < two;
    }
};

/**
 * AStar provides the the ability to animate sprites around
 * a CCTMXTiledMap along an A* path calcuated by suppied source
 * and destination tiles.
 **/
class AStar
{
	public:
		/**
		* Initialize the object with a CCTMXTileMap and the name of
		* the layer which contains your collision tiles.
		*
		* The default collide property name is COLLIDE,
		* which is checked for the default value of 1. Use setCollideKey
		* and setCollideValue to customize.
		*/
		AStar(cocos2d::CCTMXTiledMap* aTileMap, const char* name, const char* collide_prop_name, const char* collide_prop_value);

		

		void addCollideLayer(const char* name)
		{
			collideLayers.insert(tileMap->layerNamed(name));
		}
		
		//void removeCollideLayer(const char* name);
		void getPath(cocos2d::CCPoint start, cocos2d::CCPoint end, std::list<cocos2d::CCPoint*>& paths);
	private:
		AStarNode* lowCostNode();
		bool isCollision(cocos2d::CCPoint point);
		AStarNode * findPathFrom(cocos2d::CCPoint src,cocos2d::CCPoint dst);
		
		cocos2d::CCTMXTiledMap *tileMap;
		cocos2d::CCTMXLayer *groundLayer;
		std::set<cocos2d::CCTMXLayer*> collideLayers;
		std::set<AStarNode*, astarnode_compare> openNodes;
		std::set<AStarNode*, astarnode_compare> closedNodes;
		const char* collideKey;
		const char* collideValue;
		cocos2d::CCPoint tileCoordForPos(cocos2d::CCPoint position);
		void positionForTileCoord( cocos2d::CCPoint& tileCoord);
};

#endif
