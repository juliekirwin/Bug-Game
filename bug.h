//bug.h
// Declares BugClass, HornetClass, KillerAnt, SpiderClass


#ifndef _BUG
#define _BUG

#include <iostream>
#include <string>
#include <cstring>
#include "gamefiles.h"
#include "dice.h"
#include "player.h"

using namespace std;
using namespace GameFiles;


class BugClass:public PlayerClass
{

public: 
  
  void Display(ostream& out) const;
  // Displays the bug
  
protected:
  BugClass(const string name, const int initSTATS[], const int initStats[]); 
  //the appropriate function to set the data.
  //Pre: the char type and string str have already been set by the user
  
  void Turn();
  // Turns the player in a clockwise direction

  BugClass * Clone() const;
  // Create a clone of the object
  
};


//************************************************************
class HornetClass: public BugClass
{
 public:
  HornetClass(const string name);
  // Constructor for creating a Hornet
  
  void Display(ostream & out) const;
  // Displays the object
  
  bool Move();
  // Moves the Hornet using the Hornet algorithm
  // The move stops when the Hornet runs out of momentum, 
  // becomes inactive, cannot move in any direction

 protected:
  HornetClass * Clone() const;
  // Create a clone of the object
  
 private:
  // Initial settings for a Hornet
  static const int INIT_stats[8];
  static const int INIT_STATS[5];

};



//************************************************************
class KillerAntClass: public BugClass
{
 public:
  KillerAntClass(const string name);
  // Constructor for creating a KillerAnt
  
  void Display(ostream & out) const;
  // Displays the object
  
  bool Move();
  // Moves the KillerAnt using the KillerAnt algorithm
  // The move stops when the player runs out of momentum, 
  // becomes inactive, cannot move in any direction

 protected:
  KillerAntClass * Clone() const;
  // Create a clone of the object

 private:
  // Initial settings for a KillerAnt
  static const int INIT_stats[8];
  static const int INIT_STATS[5];

};

//************************************************************
class SpiderClass: public BugClass
{
 public:
  SpiderClass(const string name);
  // Constructor to create the object
  
  void Display(ostream & out) const;
  // Displays the object
  
  bool Move();
  // Moves the Spider using the Spider algorithm
  // The move stops when the player runs out of momentum, 
  // becomes inactive, cannot move in any direction
  

 protected:
  SpiderClass * Clone() const;
  // Create a clone of the object

 private:
   // Initial settings for a KillerAnt
  static const int INIT_stats[8];
  static const int INIT_STATS[5];

};


#endif
