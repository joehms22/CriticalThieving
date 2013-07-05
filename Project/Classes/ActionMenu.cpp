/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This layer shows the user current relevant information.

==CHANGELOG==
2013-06-01 - Initial Implementation - Joseph
**/


#include "ActionMenu.h"
#include "Blackboard.h"
#include "AppMacros.h"
USING_NS_CC;


const int MENU_WIDTH = 640;
const int MENU_HEIGHT = 640;

const int MENU_SPACING_PX = 10;

bool ActionMenu::init()
{
	if(! CCLayer::init())
	{	
		return false;
	}
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenu *itemMenu = CCMenu::menuWithItems(NULL);
	itemMenu->setContentSize(CCSizeMake(MENU_WIDTH, MENU_HEIGHT));
	itemMenu->setPosition(ccp(winSize.width  / 2, (winSize.height / 2)));
	setTouchEnabled(true);
	
	// Create out items.
	/**_next = CCMenuItemFont::create("Next >", this, menu_selector(ActionMenu::onPageChange));
	_next->setEnabled(true);
	_next->setPosition(ccp(	0,0));
	itemMenu->addChild(_next);**/

	_cancel = CCMenuItemFont::create("Cancel", this, menu_selector(ActionMenu::onPageChange));
	_cancel->setEnabled(true);
	_cancel->setPosition(ccp(0, 400));
	itemMenu->addChild(_cancel);
	
	/**_prev = CCMenuItemFont::create("< Last", this, menu_selector(ActionMenu::onPageChange));
	_prev->setEnabled(true);
	_prev->setPosition(ccp(0, 300));
	itemMenu->addChild(_prev);**/
	
	
	for(int i = 0; i < MAX_ACTIONS_PER_MENU; i++)
	{
		 _menuitems[i] = CCMenuItemFont::create("Item", this, menu_selector(ActionMenu::onSelectItem));
		 itemMenu->addChild(_menuitems[i]);
	}
	
	_currentActionsOffset = 0;
	this->addChild(itemMenu);
	
	this->setVisible(false);
	return true;
}

void ActionMenu::onPageChange(CCObject* pSender)
{
	printf("Page changing\n");
	
	if(pSender == _cancel)
	{
		this->setVisible(false);
	}
}

void ActionMenu::refreshMenu()
{
	// make the menu visible
	this->setVisible(true);
	
	// set and draw each of the items
	
	for(int i = 0; i < MAX_ACTIONS_PER_MENU; i++)
	{
		if(_currentActionsOffset + i < _currentActions.size())
		{
			_menuitems[i]->setString(_currentActions[_currentActionsOffset + i]->getName());
			_menuitems[i]->setEnabled(true);
		}
		else
		{
			_menuitems[i]->setEnabled(false);
		}
		
		_menuitems[i]->setPosition(ccp(0, _menuitems[i]->getContentSize().height * i));
	}
}

void ActionMenu::onEnter()
{
	CCNode::onEnter();
}

void ActionMenu::onSelectItem(CCObject* pSender)
{
	for(int i = 0; i < MAX_ACTIONS_PER_MENU; i++)
	{
		if(pSender == _menuitems[i])
		{
			int actual_position = _currentActionsOffset + i;
			
			Blackboard::getGlobalInstance()->setAction(_blackboard_action_location, _currentActions[actual_position]);	
			this->setVisible(false);
			return;
		}
	}
	
	printf("ActionMenu: Error, the selected item wasn't in the menu!\n");
}


void ActionMenu::requestAction(std::vector<Action*>& actions, char* blackboard_location)
{
	if(actions.size() == 0)
	{
		return;
	}
	
	// set the actions vector
	_currentActions.clear();
	for(int i = 0; i < actions.size(); i++)
	{
		_currentActions.push_back(actions[i]);
	}
	
	// set page to 0
	_currentActionsOffset = 0;
	
	// set location to be blackboard_location
	strcpy(_blackboard_action_location, blackboard_location);
	
	refreshMenu();
}


ActionMenu* ActionMenu::getInstance()
{
	static ActionMenu* _instance = 0;
	if(_instance == 0)
	{
		_instance = ActionMenu::create();
	}
	return _instance;	
}
