// human.h
// HumanClass, ExplorerClass, WarriorClass

#ifndef _HUMAN
#define _HUMAN

#include <iostream>
#include <string>
#include <cstring>
#include "gamefiles.h"
#include "dice.h"
#include "player.h"
#include "wpn.h"

using namespace std;
using namespace GameFiles;


class HumanClass:public PlayerClass
{

public: 
  
  HumanClass(const HumanClass& human);
  // copy constructor - deep copy of object
  
  ~HumanClass();
  // destructor
  
  HumanClass& operator=(const HumanClass& human);
  // assignment operator for deep copy
  
  int Damage() const;
  //Returns the damage inflicted by a player
  //pre:  player is active, must link with the dice files
  //post: the damage value returned is:
  //      the player's power if the player has no weapon
  //      the players weapon damage + the weaponskill if he has a weapon
  
  int Impact() const;
  //Returns the impact of a critical wound inflicted by a player
  //pre:  player is active, must link with the dice files
  //post: returns an impact value calculated from the impact table using
  //      either the weapon power or the player's power
  
  string WeaponName() const;
  //Returns the weapon name
  //pre: none
  //post: returns the name of the weapon or and empty string if the player has not weapon
  
  int WeaponSkill() const;
  //Returns the weapon skill
  //pre: none
  //post: returns the weapon skill of the player (zero if no weapon)
  
  bool DropWeapon();
  //Drops the weapon and leaves the player with no weapon being carried
  //pre:  player is active
  //post: if the player is human, their weapon is removed and the function returns true
  //      non-humans and inactive players return false
  
  bool HasWeapon() const;
  //reports whether or not the player has a weapon
  //pre: none
  //post: returns true if the player has a weapon, false otherwise
  
  bool GrabWeapon(string newweapon, int skill);
  //Drops the wepaon being carried and grabs the new weapon
  //pre: player is active; the newweapon is not "", and skill is greater than 0
  //post: If the new weapon data is invalid or the player is a bug, false is returned
  //      otherwise, the weapon and weaponskill of the player are set to the newweapon and skill sent in

  void Display(ostream& out) const;
  // Displays the player
  
  bool Move( );
  // moves the player one unit forward
    
protected:
  HumanClass(const string name, const string wpnName, int wpnSkill,
           const int initSTATS[], const int initStats[]); 
  // constructor
  //the appropriate function to set the data.
  //Pre: the char type and string str have already been set by the user
 
  HumanClass *Clone( ) const;
  // Create a clone of the object


private:

  WpnClass* wpn; 
  int skill;

  void CopyIntoMe(const HumanClass & );  
  // for deep copying

};


class WarriorClass: public HumanClass
{
 public:
  WarriorClass(const string name);
  // public constructor
  
  void Display(ostream & out) const;
  // Display a warrior
  
  bool Move();
  // Move a warrior one cell forward
  
 protected:
  WarriorClass* Clone( ) const; 
  // to create a clone of the object
   
 private:
  // Initial settings for a Warrior
  static const char WPN_NAME[15];
  static const int WPN_SKILL;
  static const int INIT_STATS[5];
  static const int INIT_stats[8];

};


class ExplorerClass: public HumanClass
{
 public:
  ExplorerClass(const string name);
  // public constructor
  
  void Display(ostream & out) const;
  // Display Explorer
    
  bool Move();
  // Move an explorer one cell forward
  
 protected:
  ExplorerClass* Clone( ) const; 
  // to create a clone of the object

 private:
  // Initial settings for a Explorer
  static const char WPN_NAME[15];
  static const int WPN_SKILL;
  static const int INIT_stats[8];
  static const int INIT_STATS[5];

};

#endif
