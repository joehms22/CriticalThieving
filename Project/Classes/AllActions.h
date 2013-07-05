
/**
This file is part of Critical Thieving. Copyright 2013 - Joseph Lewis

DO NOT EDIT THIS FILE MANUALLY, IT IS AUTO GENERATED BY generate_all_actions.py
INSTEAD, EDIT actions.csv AND RE-RUN generate_all_actions.py

**/

#ifndef ALL_ACTIONS_H
#define ALL_ACTIONS_H
#include "Action.h"
#include "CharacterProperties.h"
#include "Sprite.h"

namespace SpriteActions
{

	class BuyHotDog : public Action
	{
		public:
			BuyHotDog(Sprite* owner)
			:Action(owner, NULL, "Buy Hot Dog")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -5);;
				_props->setValue(full, 20);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >= 5);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("full_up.mp3");
				display_bubble(actor,"rich-_full+.png");
			}
	};


	class BuyPizza : public Action
	{
		public:
			BuyPizza(Sprite* owner)
			:Action(owner, NULL, "Buy Pizza")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -20);;
				_props->setValue(full, 50);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >= 20);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("full_up.mp3");
				display_bubble(actor,"rich-_full+.png");
			}
	};


	class StealHotDog : public Action
	{
		public:
			StealHotDog(Sprite* owner)
			:Action(owner, NULL, "Steal Hot Dog")
			{
				_props = new CharacterProperties();
				_props->setValue(full, 20);;
				_props->setValue(moral, -10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.is(full) == false);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"full+_moral-.png");
			}
	};


	class StealPizza : public Action
	{
		public:
			StealPizza(Sprite* owner)
			:Action(owner, NULL, "Steal Pizza")
			{
				_props = new CharacterProperties();
				_props->setValue(full, 50);;
				_props->setValue(moral, -10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.is(full) == false);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"full+_moral-.png");
			}
	};


	class BuyEnergyDrink : public Action
	{
		public:
			BuyEnergyDrink(Sprite* owner)
			:Action(owner, NULL, "Buy Energy Drink")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -5);;
				_props->setValue(full, 10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >= 5);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("full_up.mp3");
				display_bubble(actor,"rich-_full+.png");
			}
	};


	class LightonFire : public Action
	{
		public:
			LightonFire(Sprite* owner)
			:Action(owner, NULL, "Light on Fire")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, -20);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.is(moral) == false) && (actor.value(full) >=20);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"moral-.png");
			}
	};


	class Punch : public Action
	{
		public:
			Punch(Sprite* owner)
			:Action(owner, NULL, "Punch")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, -5);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(full) >=20);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"moral-.png");
			}
	};


	class ShakeHand : public Action
	{
		public:
			ShakeHand(Sprite* owner)
			:Action(owner, NULL, "Shake Hand")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, 1);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(full) >=20);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"moral+.png");
			}
	};


	class StealWallet : public Action
	{
		public:
			StealWallet(Sprite* owner)
			:Action(owner, NULL, "Steal Wallet")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 5);;
				_props->setValue(moral, -5);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.is(rich) == false);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+_moral-.png");
			}
	};


	class GiveMoney : public Action
	{
		public:
			GiveMoney(Sprite* owner)
			:Action(owner, NULL, "Give Money")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -5);;
				_props->setValue(moral, 1);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >=5);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"rich-_moral+.png");
				Blackboard::getGlobalInstance()->setBool("GiveToPoor", true);
			}
	};


	class PassOutFreeCandy : public Action
	{
		public:
			PassOutFreeCandy(Sprite* owner)
			:Action(owner, NULL, "Pass Out Free Candy")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -5);;
				_props->setValue(moral, 1);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >=2);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"rich-_moral+.png");
			}
	};


	class BuyHaircut : public Action
	{
		public:
			BuyHaircut(Sprite* owner)
			:Action(owner, NULL, "Buy Haircut")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -10);;
				_props->setValue(moral, 5);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >=10);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"rich-_moral+.png");
			}
	};


	class StealScissors : public Action
	{
		public:
			StealScissors(Sprite* owner)
			:Action(owner, NULL, "Steal Scissors")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, -5);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.is(moral) == false) && (Blackboard::getGlobalInstance()->getBool("HasScissors", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"moral-.png");
				Blackboard::getGlobalInstance()->setBool("HasScissors", true);
			}
	};


	class RobatScissorpoint : public Action
	{
		public:
			RobatScissorpoint(Sprite* owner)
			:Action(owner, NULL, "Rob at Scissorpoint")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 20);;
				_props->setValue(moral, -10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(full) >=50) && (Blackboard::getGlobalInstance()->getBool("HasScissors", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+_moral-.png");
				Blackboard::getGlobalInstance()->setBool("HasScissors", false);
			}
	};


	class GiveHaircut : public Action
	{
		public:
			GiveHaircut(Sprite* owner)
			:Action(owner, NULL, "Give Haircut")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (Blackboard::getGlobalInstance()->getBool("HasScissors", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+.png");
			}
	};


	class GiveDonut : public Action
	{
		public:
			GiveDonut(Sprite* owner)
			:Action(owner, NULL, "Give Donut")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, 20);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (Blackboard::getGlobalInstance()->getBool("HasDonut", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"rich-_moral+.png");
				Blackboard::getGlobalInstance()->setBool("HasDonut", false);
			}
	};


	class StealTazer : public Action
	{
		public:
			StealTazer(Sprite* owner)
			:Action(owner, NULL, "Steal Tazer")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, -5);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.is(moral) == false) && (Blackboard::getGlobalInstance()->getBool("HasTazer", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"moral-.png");
				Blackboard::getGlobalInstance()->setBool("HasTazer", true);
			}
	};


	class TazeandRob : public Action
	{
		public:
			TazeandRob(Sprite* owner)
			:Action(owner, NULL, "Taze and Rob")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 20);;
				_props->setValue(moral, -10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(full) >=50) && (Blackboard::getGlobalInstance()->getBool("HasTazer", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+_moral-.png");
				Blackboard::getGlobalInstance()->setBool("HasTazer", false);
			}
	};


	class Hug : public Action
	{
		public:
			Hug(Sprite* owner)
			:Action(owner, NULL, "Hug")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, 1);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return true;
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"moral+.png");
			}
	};


	class TrimTree : public Action
	{
		public:
			TrimTree(Sprite* owner)
			:Action(owner, NULL, "Trim Tree")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, 5);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (Blackboard::getGlobalInstance()->getBool("HasScissors", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"moral+.png");
			}
	};


	class SaveKitten : public Action
	{
		public:
			SaveKitten(Sprite* owner)
			:Action(owner, NULL, "Save Kitten")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, 1);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return true;
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_up.mp3");
				display_bubble(actor,"moral+.png");
			}
	};


	class TazeKitten : public Action
	{
		public:
			TazeKitten(Sprite* owner)
			:Action(owner, NULL, "Taze Kitten")
			{
				_props = new CharacterProperties();
				_props->setValue(moral, -50);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (Blackboard::getGlobalInstance()->getBool("HasTazer", false) == true) && (Blackboard::getGlobalInstance()->getBool("HasCatMeat", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("moral_down.mp3");
				display_bubble(actor,"moral-.png");
				Blackboard::getGlobalInstance()->setBool("HasCatMeat", true);
				Blackboard::getGlobalInstance()->setBool("HasTazer", false);
			}
	};


	class RobBank : public Action
	{
		public:
			RobBank(Sprite* owner)
			:Action(owner, NULL, "Rob Bank")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 30);;
				_props->setValue(moral, -60);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(moral) >=60) && (Blackboard::getGlobalInstance()->getBool("BankRobbed", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+_moral-.png");
				Blackboard::getGlobalInstance()->setBool("BankRobbed", true);
			}
	};


	class SolicitCharity : public Action
	{
		public:
			SolicitCharity(Sprite* owner)
			:Action(owner, NULL, "Solicit Charity")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 50);;
				_props->setValue(moral, -40);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(moral) >=90) && (Blackboard::getGlobalInstance()->getBool("BankRobbed", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+_moral-.png");
				Blackboard::getGlobalInstance()->setBool("BankRobbed", true);
			}
	};


	class BuyDonut : public Action
	{
		public:
			BuyDonut(Sprite* owner)
			:Action(owner, NULL, "Buy Donut")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -10);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >=10);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_down.mp3");
				display_bubble(actor,"rich-.png");
				Blackboard::getGlobalInstance()->setBool("HasDonut", true);
			}
	};


	class BuyScissors : public Action
	{
		public:
			BuyScissors(Sprite* owner)
			:Action(owner, NULL, "Buy Scissors")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -20);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >=20) && (Blackboard::getGlobalInstance()->getBool("HasScissors", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_down.mp3");
				display_bubble(actor,"rich-.png");
				Blackboard::getGlobalInstance()->setBool("HasScissors", true);
			}
	};


	class BuyTazer : public Action
	{
		public:
			BuyTazer(Sprite* owner)
			:Action(owner, NULL, "Buy Tazer")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, -40);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (actor.value(rich) >=40) && (Blackboard::getGlobalInstance()->getBool("HasTazer", false) != true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_down.mp3");
				display_bubble(actor,"rich-.png");
				Blackboard::getGlobalInstance()->setBool("HasTazer", true);
			}
	};


	class RobinHoodBonus : public Action
	{
		public:
			RobinHoodBonus(Sprite* owner)
			:Action(owner, NULL, "Robin Hood Bonus")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 20);;
				_props->setValue(moral, 20);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (Blackboard::getGlobalInstance()->getBool("GiveToPoor", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+_moral+.png");
				Blackboard::getGlobalInstance()->setBool("GiveToPoor", false);
			}
	};


	class SellCatMeat : public Action
	{
		public:
			SellCatMeat(Sprite* owner)
			:Action(owner, NULL, "Sell Cat Meat")
			{
				_props = new CharacterProperties();
				_props->setValue(rich, 25);;
			}
			
			bool canTakeAction(Sprite& actor)
			{
				return (Blackboard::getGlobalInstance()->getBool("HasCatMeat", false) == true);
			}
			
			void act(Sprite* actor)
			{
				actor->apply(*_props);
				play_sound("rich_up.mp3");
				display_bubble(actor,"rich+.png");
				Blackboard::getGlobalInstance()->setBool("HasCatMeat", false);
			}
	};


}
#endif
