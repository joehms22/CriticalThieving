/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This layer shows the user current relevant information.

==CHANGELOG==
2013-06-01 - Initial Implementation - Joseph
**/


#include "cocos2d.h"
#include "Action.h"

#ifndef ACTION_MENU_H
#define ACTION_MENU_H

const int MAX_ACTIONS_PER_MENU = 8;
const int MAX_STRING_LENGTH = 500;

class ActionMenu : public cocos2d::CCLayer
{
	public:
		virtual bool init();
		void OnMenu(CCObject* pSender);
		
		static ActionMenu* getInstance();
		void requestAction(std::vector<Action*> &actions, char* blackboard_location);
		
		void onEnter();

		CREATE_FUNC(ActionMenu);
	private:
		cocos2d::CCMenuItemLabel  *_cancel;
		cocos2d::CCMenuItemLabel *_menuitems[MAX_ACTIONS_PER_MENU];
		int _currentActionsOffset; // what item are we displaying in _currentActions
		std::vector<Action*> _currentActions;
		char _blackboard_action_location[MAX_STRING_LENGTH]; // the place to store the action after it's chosen
		
		void refreshMenu(); // shows and draws the menu.
		void onPageChange(CCObject* pSender);
		void onSelectItem(CCObject* pSender);
};

#endif
