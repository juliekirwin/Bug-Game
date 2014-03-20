// phc.h
//  Player - handleclass for PlayerClass hierarchy

#ifndef _HPLAYER
#define _HPLAYER

#include "human.h"
#include "bug.h"
#include <typeinfo>

using namespace std;

class Player
{
  public:

  enum PlayerType {EXPLORER, WARRIOR, HORNET, KILLERANT, SPIDER};
  // enumerated type for creating the player
  
  Player( );
  // default constructor - no player, just a shell
  	
  Player(const string name, PlayerType type=EXPLORER);
  // parameterized constructor that creates a player
  		
  Player(const Player& p);
  // copy constructor - does a deep copy of object
  
  Player(PlayerClass * ptr);
  // parameterized constructor that creates a player from playerclass ptr.
  // no copy is made - just encapsulated the pointer.
  	
  ~Player( ) ;
  // destructor
  		
  Player& operator=(const Player & p);
  // Assignment operator that creates a deep copy
  
  void Display(ostream& out) const;
  // Displays the player
  
  bool Active();
  //Function: Looks to see if player is alive. If they are, it will set 
  //active to false, else it sets active to true. It returns the bool value of active.
  //Pre: none
  //Post: False is returned if health or willpower is equal to zero. Else true is returned.
  
  bool InActive();
  //Function: Sets the value of active to false then returns true.
  //Pre: none
  //Post: The value of active should always be set to false. True should always be returned.
  
  bool Dead();
  //Function: Sets the value of health to 0, willpower to 0, and active to false then returns.
  //Pre: none
  //Post: Health should now be set to 0, along with willpower and active.
  
  bool Heal();
  //Fuction: When it is a valid player and they are alive the function
  //sets the currentspeed to maxspeed and add 10 to health. If health is than greater than
  //the players maxhealth, health is set to maxhealth. The function returns true if the
  //player is valid and not dead, otherwise is returns false.
  //Pre: none
  //Post: If type is not NOPLAYER and health is greater than 0 it is true. Else it is false.
  
  int ResetMomentum();
  //Function: Sets the players momentum to the currentspeed and returns momentum.
  //Pre: none
  //Post: Momentum is now set to the currentspeed and returned.
  
  int UseMomentum(int num);
  //Function: Updates momentum used in move by taking the momentum the played had at 
  //the start of the turn and subtracts the momentum used during the turn that is passed 
  //into the function. The function returns the updated momentum.
  //Pre: An interger num is passed into the function.
  //Post: The momentum is updated. 
  
  string Name() const;
  //Function: Returns the name of a player.
  //Pre: none
  //Post: Returns the name of the player. If it has no name an empty string is returned.
  
  int Row() const;
  //Function: Returns the cell row value where the player is located.
  //Pre: none
  //Post: Returns the row of the player. If it has no row, 0 is returned.
  
  int Column() const;
  //Function: Returns the cell column value where the player is located.
  //Pre: none
  //Post: Returns the cell of the player. If it has no cell, 0 is returned.

  char Direction() const;
  //Function: Returns the direction value where the player is located.
  //Pre: none
  //Post: Returns the direction of the player.
  
  int Health() const;
  //Function: Returns the health of a player.
  //Pre: none
  //Post: Returns the health of the player. If it has no health, 0 is returned.
  
  int WillPower() const;
  //Function: Returns the willpower of a player.
  //Pre: none
  //Post: Returns the willpower of the player. If it has no willpower, 0 is returned.
  
  int MaxSpeed() const;
  //Function: Returns the max speed of a player.
  //Pre: none
  //Post: Returns the maxspeed of the player. If it has no maxspeed, 0 is returned.
  
  int CurrentSpeed() const;
  //Funtion: Returns the current speed of a player.
  //Pre: none
  //Post: Returns the currentspeed of the player. If it has no currentspeed, 0 is returned. 
  
  int Power() const;
  //Function: Returns the power of the player.
  //Pre: none
  //Post: Returns the power of the player. If it has no power, 0 is returned.
  
  int Armor() const;
  //Function: Returns the armor value of the player.
  //Pre: none
  //Post: Returns the armor value of the player. If it has no armor value, 0 is returned.
  
  int Momentum() const;
  //Function: Returns the current momentum of the player.
  //Pre: none
  //Post: none
  
  bool IsAlive() const;
  //Function: If the player's health is 0 or lower it retuns false,
  //else it returns true. 
  //Pre: none
  //Post: Returns true if player has health greater than 0, else returns false.
  
  bool IsDead() const;
  //Function: If the player's health is 0 or lower it returns true,
  //else it returns false.
  //Pre: none
  //Post: Returns false if player has health greater than 0, else returns true. 
  
  bool IsActive() const;
  //Function: If the player is active it returns true, else it returns false.
  //Pre: none
  //Post: Returns true if active; if active is false, returns false.
 
  bool SetCell(int newRow, int newCol);
  //sets the coordinates of a player to newRow and newCol
  //pre:  newRow and newCol are not negative
  //post: Coordinates have been set, returns true if new coordinates are valid

  bool SetDir(char dir);
  //sets the directions of a player 
  //pre:  dir must be n,s,e,w
  //post: Direction has been set, returns true if new dir are valid
  
  int SlowDown(int hazard);
  //Subtracts hazard from a player's currentspeed and reduces momentum if currentspeed becomes less than momentum
  //pre: Player is active and hazard is greater than or equal to zero
  //post: currentspeed has been reduced (if hazard>currenspeed then currentspeed = 0). 
  //    Updated currentspeed is returned
  
  int ResetCurrentSpeed();
  //Resets the player's current speed to max speed
  //pre: player is active
  //post: currentspeed is set to maxspeed
  
  int Wounded(int damage);
  //Updates and returns the player's health
  //pre: damage is greater than or equal to zero and the player is active
  //post: damage is subtracted from health (player is declared dead if health is reduced to 0 or less
  //      the updated health is returned
  
  int RollPhysicalDamage() const;
  //Returns the roll for the physical damage of a player
  //pre:  must link with the dice files
  //post: physical damage is calculated and that value is returned
  
  virtual int Damage() const;
  //Returns the damage inflicted by a player
  //pre:  player is active, must link with the dice files
  //post: the damage value returned is:
  //      the player's power if the player has no weapon
  //      the players weapon damage + the weaponskill if he has a weapon
  
  virtual int Impact() const;
  //Returns the impact of a critical wound inflicted by a player
  //pre:  player is active, must link with the dice files
  //post: returns an impact value calculated from the impact table using
  //      either the weapon power or the player's power
  
  bool CriticalWound();
  //Updates the player's current speed, willpower, and health based on a critical wound
  //pre: player is active, must link with the dice files
  //post: The player's health is reduced by 10 and the current speed decreased by half
  //      If the player lives through that, then the critical wound table is used to
  //      determine whether the player takes willpower damage or dies
  //      True is returned if the player is alive after all this, false if he doesn't make it

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
  //Drops the weapon being carried and grabs the new weapon
  //pre: player is active; the newweapon is not "", and skill is greater than 0
  //post: If the new weapon data is invalid or the player is a bug, false is returned
  //      otherwise, the weapon and weaponskill of the player are set to the newweapon and skill sent in
  
  bool Move();  
  // Move the player
  //pre:  None
  //post: Player has moved

  bool CanRun();
  // Determines if the player can run one space north
  // pre:  none
  // post: returns true if player can run
  
  bool Run( );
  // Excutes a run north
  // pre:  none
  // post: returns true if the player successfully runs north one space
    
  bool IsMyEnemy(const Player & player) const;
  // detemines if the player is an enemy
  // pre:  player has a value
  // post: Based on the game rules determines whether player is an enemy
  //       returns true if player is an enemy and false otherwise

  bool IsHuman( ) const;
  // determines if this object is a human
  // pre:  none
  // post: Returns true if human, false otherwise
  
  // Relational operators
  bool operator==(const Player& p) const;  
  bool operator!=(const Player& p) const;
  bool operator<=(const Player& p) const;  
  bool operator>=(const Player& p) const;
  bool operator<(const Player& p) const;  
  bool operator>(const Player& p) const;
    

  private:

	
   PlayerClass * Create(const string name, Player::PlayerType type);
   // Create an object
   
   void CopyIntoMe(const Player &p);
   // Deep copy the object
   
   PlayerClass *p;  // encapsulated pointer
};

#endif



