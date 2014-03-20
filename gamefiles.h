// gamefiles.h

//Read and write to and from the game files

#ifndef _GAMEFILES
#define _GAMEFILES

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

#include "wpn.h"

class Player;

using namespace std;

namespace GameFiles
{

//*****************************************************************************  
// Named constants  

  const bool KEYBD = true;
  const int NUMROWS = 12;
  const int NUMCOLS = 5;

  const string RANGE_WPNS_FILE = "range.in";
  const string MELEE_WPNS_FILE = "melee.in";
  const string DICE_FILE = "dice.in";
  const string BOARD_FILE = "board.in";
  const string WEAPONS_FILE = "weapons.in";
  const string PLAYERS_FILE = "players.in";
  const string TESTOUTFILE = "zimmer5.out";
  
  const string LINE1 = "*************************************************\n";    
  const char DEL = '#';


//*****************************************************************************  
// Named Datatypes  

  enum SquadType { ALPHA, BRAVO, CHARLIE, DELTA, ECHO};
  // enum for sqad
  
  typedef vector<Player *> VecPlayerType;   // vector of Player *
  typedef queue<Player *> QueueType;        // queue of Player *
  typedef set<string> SetType;		    // set of living players in squad
  typedef vector<SetType> VecSetType;	    // vector of sets of living players
  typedef map<WpnClass::WpnType,int> MapWpnType;  // map of wpn arsenal for a squad
  typedef vector<MapWpnType> ArsenalType;	// vector of wpn maps
  typedef map<string,SquadType> MapSquadType;  // map of players and squads

  // struct for the menu selection for human player interface
  struct MenuRec
  {
    char mm;
    char data1;
    int data2;
  };


//*****************************************************************************  
// Functions for enum  
  
  string SquadToStr(SquadType squad );
  // Converts the squad enum to a string
  
  SquadType StrToSquad(string str);
  // Converts the string squad name to squad enum

//*****************************************************************************  
// Function creating uppercase string  
  
  string Ucase(string str);
  // Converts str to uppercase
  // pre: str is a string
  // post: returns the uppercase version of str


//*****************************************************************************  
// Functions for Game Play  

  void PrintTest(ostream & out, string test="");
  // Prints the test label
  // pre:  out is open and test is prefix for test
  //       if test is new then testnumber is reset
  // post: test label is printed

  void BeginGame(const QueueType& players, const VecSetType & alive, 
              const MapSquadType & squadList,const ArsenalType& wpns );
  // Print data after everything is loaded and game play is ready to begin
  // Pre:  
  //        players is the queue of players in the game
  //        alive is the vector of all the squad sets (only one has players)
  //        squadlist is the list of player's squads
  //        wpns is the vector of all the wpn aresenals
                        
  MenuRec BeforeTurn(Player * p, string squad, const MapWpnType& wpns);
  MenuRec BeforeTurn(Player * p);  // bugs with no squad
  // Print data before the player's turn - both bug and human
  // pre: p points to player whose turn it is
  //      wpns contains the arsenal for the player p's squad
  //      squad is the name of the player p's squad
  // post: Human player will send back the menu selection sel complete
                        
  
  void AfterTurn(Player * p, string squad, const MapWpnType& wpns, MenuRec sel);
  void AfterTurn(Player * p);  // bugs with no squad
  // Print data after the player's turn - both bug and human
  // pre: p points to player that just finished the turn
  //      squad is the name of the player p's squad
  //      wpns contains the arsenal for the player p's squad
  //      sel contains the menu selection (this will be "empty" for bugs
  // post: output for end of turn is printed
  
  void GameOver(const QueueType& players, const VecSetType & alive,
            const MapSquadType & squadList, const ArsenalType & wpns );
  // Print data when the game is over
  // Pre:  
  //        players is the queue of players in the game
  //        alive is the vector of all the squad sets (only one has players)
  //        squadlist is the list of player's squads
  //        wpns is the vector of all the wpn aresenals

//*****************************************************************************  
// Function to print containers  
  void DisplayFields(ostream & out, const Player * p);
  // Displays the fields of the player
  // pre: out is open, p points to the player
  // post: player fields are printed
  //
  
  void PrintVectorOfSquads(ostream & out, const VecSetType & alive );
  // Displays the vector of squads
  
  void PrintVectorOfPlayers(ostream & out, const VecPlayerType & vec);
  // Prints the vector of players
  
  void PrintQueue(ostream & out, QueueType q);
  // Prints the queue of players
  
  void PrintActiveQueue(ostream & out, QueueType q);
  // Prints the active players in the queue only
  
  void PrintArsenal(ostream & out, string s,  const MapWpnType & wpn);
  // Prints the map of weapons for a squad
  
  void PrintAllArsenals(ostream & out, const ArsenalType & wpns );
  // Prints all the weapon arsenals for all of the squads
  
  void Dump(ostream & out, const QueueType& players, const VecSetType & alive,
            const MapSquadType & squadList, const ArsenalType & wpns );

  // Prints all the contains contents
  
  
//*****************************************************************************  
// File I/O for dice

  void WriteDel(ostream& stream);
  // Writes the delimiter to the output stream
  // pre: stream is open and in good condition
  // post: delimiter has been written
  
  bool ReadNum(istream& stream, int& num,int min,int max);
  // Reads a number, validates range, if valid reads del and returns true
  // pre: stream is open and in good cond, min and max indicate boundaries for num
  // post: valid: returns num, reads passed delimiter (includes \n), returns true
  //       invalid: stops reading and returns false
   
  bool ReadStr(istream& stream, string& str);    
  // Reads string through del, returns true if string length>0 && stream
  // pre: stream is open and in good cond.
  // post: reads str and delimiter (includes \n).  if string length >0 return true
  //		otherwise returns false
  
  bool ReadDel(istream& stream);
  // Reads Del (includes '\n')
  // pre: stream is open and in good cond.
  // post: delimiter is read and stream status is returned
  
};


#endif

