//Julie Kirwin
//CSCI330
//FALL 2012
//PROGRAM 5
//GAME MASTER

#include "p5.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <algorithm>


using namespace GameFiles;

void GameSetUp(QueueType & pQueue, ArsenalType & arsenal, MapSquadType & squadMap, VecSetType & squadSetVec);
//Function: Calls appropriate set up functions.
//Pre: none
//Post: game is set up for play.

vector<Player *> BoardSet();
//Function: Creates the board.
//Pre: none
//Post: A board is created.

VecPlayerType LoadPlayer(VecSetType & squadSetVec, MapSquadType & squadMap);
//Function: Loads the players into appropraite contairers and sets them on the board
//Pre: none
//Post: Players are placed on board, put in containers. A vector of player pointers are returned.

SetType SetSquad(ifstream & fin, VecPlayerType & pVec,int num, MapSquadType & squadMap);
//Function: Loads the players into appropraite contairers and sets them on the board, reutrns set of players. 
//Pre: none
//Post: Players are placed on board, put in containers. A set of players are returned.

Player * CreaterPlayer(string pName,char type);
//Function: Creates a player pointer based on type and returns it.
//Pre: SetSquad was call and player type was read in by file;
//Post: player pointer is returned

void LoadQueue(QueueType & pQueue, vector<Player *> bugs, vector<Player *> squad);
//Function: Loads the queue of players in alphabetical order
//Pre: all players are stored in vectors
//Post: Queue is set.

vector<Player *> SortAll(vector<Player *> bugs, vector<Player *> squad);
//Function: Sorts vector of all players.
//Pre: vector os bugs and players sent in.
//Post: vector of sorted players returned.

bool Compare(Player * p1, Player * p2);
//Function: Compares two players by name.
//Pre: 2 player sent in
//Post: Bool is returned whether p1 is < p2;

void LoadWeapons(ArsenalType & arsenal);
//Function: Loads weapons into map of weapons for all the squads.
//Pre: none
//Post: Weapons for each squad in map.

void Game(QueueType & pQueue, ArsenalType & arsenal, MapSquadType & squadMap, VecSetType & squadSetVec);
//Function: Prints game begin data. Loops through turns till game ends.
//Pre: none
//Post: Game plays through till game is over.

bool Turn(QueueType & pQueue, VecSetType & squadSetVec, MapSquadType & squadMap, ArsenalType & arsenal);
//Function: Process through a turn of a player.
//Pre: It is not the end of the game.
//Post: Returns bool if game is over or not.

bool HumanTurn(MapSquadType & squadMap, ArsenalType & arsenal, Player * p);
//Function: Takes in selections for the user and call correct player choice for the turn.
//Pre: Human is being processed.
//Post: Reutrns if player is alive and active.

bool BugTurn(MapSquadType & squadMap, ArsenalType & arsenal, Player * p);
//Function: Moves the bug if its active.
//Pre: Bug is being processed.
//Post: Reutrns if player is alive and active.

void HMove(char direction, int units, Player * p);
//Function: Moves human player.
//Pre: Direction and units to move  and player are paseed in 
//Post: Player is moved.

void HWep(char w, int level, Player * p, ArsenalType & arsenal, MapSquadType & squadMap);
//Function: Changes the weapon.
//Pre: Takes in weapon and lavel. 
//Post: Updates the weapon.

bool DeletePlayers(QueueType & pQueue, VecSetType & squadSetVec, MapSquadType & squadMap);
//Function: Removers players from squad sets if dead.
//Pre: none
//Post: If deletes player returns true.

bool CheckOver(VecSetType & squadSetVec);
//Function: Checks for one or less squads left in the game.
//Pre: none
//Post:Returns true if 1 or less squads are left, false otherwise.

void End(QueueType & pQueue, ArsenalType & arsenal, MapSquadType & squadMap, VecSetType & squadSetVec);
//Function: Calls GameOver and clears queue.
//Pre: Game is over.
//Post: queue is cleared.

//*********************************************************
int main(){
  QueueType  pQueue;
  ArsenalType arsenal;
  MapSquadType squadMap;
  VecSetType squadSetVec;
  //Dice::ReadRollsFromFile();
  
  GameSetUp(pQueue, arsenal, squadMap, squadSetVec);
  Game(pQueue, arsenal, squadMap, squadSetVec);
  
  //Dump(cout, pQueue, squadSetVec, squadMap, arsenal);
  
  return 0;
}

///********************************************************
///                BEFORE PLAY SET UP
///********************************************************


//*********************************************************
void GameSetUp(QueueType & pQueue, ArsenalType & arsenal, MapSquadType & squadMap, VecSetType & squadSetVec){
  vector<Player *> squad;
  vector<Player *> bugs;
  
  bugs= BoardSet();
  squad= LoadPlayer(squadSetVec, squadMap);
  LoadQueue(pQueue, bugs, squad);
  LoadWeapons(arsenal);
  
  squad.clear();
  bugs.clear();
  return;
}

//*********************************************************  
vector<Player *> BoardSet(){
  vector<Player *> bugs;
  
  //MAKE CONST FOR THIS!!!!
  bugs= BoardClass::CreateBoard(NUMROWS,NUMCOLS);
  return bugs;
}

//*********************************************************
VecPlayerType LoadPlayer(VecSetType & squadSetVec, MapSquadType & squadMap){
  ifstream fin;
  fin.open (PLAYERS_FILE.c_str() , ios::app);
  VecPlayerType pVec;
  
  for (int i= ALPHA; i <= DELTA; i++)
  {
    squadSetVec.push_back(SetSquad(fin, pVec, i, squadMap));
  }
  
  fin.close();
  return pVec;
}

//*********************************************************
SetType SetSquad(ifstream & fin, VecPlayerType & pVec,int num, MapSquadType & squadMap){
  char type;
  string pName= "";
  int pRow;
  int pCol;
  char direction;
  SetType squad;
  Player * p;
  BoardClass * bd= BoardClass::GetBd();
  
  fin>> type;
  while(type != 'q' && fin){
    fin>> pName;
    fin>> pRow;
    fin>> pCol;
    fin>> direction;
    p= CreaterPlayer(pName, type);
    bd->BoardClass::PlacePlayer(p, pRow, pCol);
    p->Active();
    p->ResetMomentum();
    p->DropWeapon();
    p->SetDir(direction);
    pVec.push_back(p);
    squad.insert(pName);
    squadMap.insert(make_pair(p->Name(), SquadType(num)));
    fin>> type;
  }
  return squad;
}

//*********************************************************
Player * CreaterPlayer(string pName,char type){
  
  Player * p;
  p= NULL;
  switch (toupper(type))
  {
    case 'E': p= new Player(pName, Player::EXPLORER); break;
    case 'W': p= new Player(pName, Player::WARRIOR); break;
    case 'H': p= new Player(pName, Player::HORNET); break;
    case 'K': p= new Player(pName, Player::KILLERANT); break;
    case 'S': p= new Player(pName, Player::SPIDER); break;
  }
return p;
}

//*********************************************************
void LoadQueue(QueueType & pQueue, vector<Player *> bugs, vector<Player *> squad){
  vector<Player *> all;
  all= SortAll(bugs, squad);
  int len= all.size();
  
  for (int i= 0; i < len; i++)
  {
    pQueue.push(all[i]);
  }
  
  all.clear();
  return;
}

//*********************************************************
vector<Player *> SortAll(vector<Player *> bugs, vector<Player *> squad){
  int lenS= squad.size();
  for (int i= 0; i < lenS; i++)
  {
    bugs.push_back(squad[i]);
  }
  sort(bugs.begin(), bugs.end(), Compare);
  return bugs;
}

//*********************************************************

bool Compare(Player * p1, Player * p2){
 return(*p1 < *p2);
}

//*********************************************************
void LoadWeapons(ArsenalType & arsenal){
  ifstream fin;
  fin.open(WEAPONS_FILE.c_str());
  
  MapWpnType squadWeps;
  char type;
  int num;
  
  while(fin)
  {
    for (int i= 0; i< 4; i++)
    {
      fin>> type;
      fin>> num;  

      squadWeps.insert(make_pair(WpnClass::WpnType(i), num));
    }
    arsenal.push_back(squadWeps);
    squadWeps.clear();
  }
  
  fin.close();
  return;
}

///********************************************************
///                 PLAYING THE GAME
///********************************************************

//*********************************************************
void Game(QueueType & pQueue, ArsenalType & arsenal, MapSquadType & squadMap, VecSetType & squadSetVec){
  BeginGame(pQueue, squadSetVec, squadMap, arsenal);
  //Turn(pQueue, squadSetVec, squadMap, arsenal);
  while (!Turn(pQueue, squadSetVec, squadMap, arsenal))
  {
    Turn(pQueue, squadSetVec, squadMap, arsenal);  
  }
  End(pQueue, arsenal, squadMap, squadSetVec); 
}

//*********************************************************
bool Turn(QueueType & pQueue, VecSetType & squadSetVec, MapSquadType & squadMap, ArsenalType & arsenal){
  bool over= false;
  Player * p;
  p= pQueue.front();
  pQueue.pop();
  

  p->ResetMomentum();
    
  if( p->IsHuman())
  {
    HumanTurn(squadMap, arsenal, p);
  }
  else
  {
    BugTurn(squadMap, arsenal, p); 
  }
    
  pQueue.push(p);  
  
  DeletePlayers(pQueue, squadSetVec, squadMap);
  over= CheckOver(squadSetVec);
  
  
  return over;
}

//*********************************************************
bool DeletePlayers(QueueType & pQueue, VecSetType & squadSetVec, MapSquadType & squadMap){
  Player * p;
  int qSize= pQueue.size();
  bool del= false;
  for (int i= 0; i < qSize; i++)
  {
    p= pQueue.front();
    pQueue.pop();
    
    if (p->IsDead())
    {
      if (squadSetVec[squadMap[p->Name()]].count(p->Name()))
      {
	squadSetVec[squadMap[p->Name()]].erase(p->Name());
	del= true;
      }
      //PrintVectorOfSquads(cout , squadSetVec); 
    }
 
    pQueue.push(p);
  }
  
  return del;
}
 
//********************************************************
bool CheckOver(VecSetType & squadSetVec){
  int count= 0;
  int over= false;

  for (int i= ALPHA; i<= DELTA; i++)
  {
   if (squadSetVec[i].size() >= 1)
     count ++;
   //cout << "DA COUNT! " << count << endl;
  }
  
  if (count < 2)
  {
    over= true;
  }
  //cout << "IS IT DONE?! " << over << endl;
  return over;
}

//********************************************************
bool HumanTurn(MapSquadType & squadMap, ArsenalType & arsenal, Player * p){
  MenuRec menu;
  string sname= SquadToStr(squadMap[p->Name()]);
  menu= BeforeTurn(p, sname, arsenal[squadMap[p->Name()]]);
  
  if (p->IsActive())
  {   
    switch (menu.mm)
    {
      case 'h': p->Heal();  break;
      case 'm': HMove(menu.data1, menu.data2, p);  break;
      case 'w': HWep(menu.data1, menu.data2, p, arsenal, squadMap);
    }
  }
  AfterTurn(p, sname, arsenal[squadMap[p->Name()]], menu); 
  return (p->IsActive());
}

//*********************************************************
void HMove(char direction, int units, Player * p){
   if (p->IsActive())
   {
     p->SetDir(direction);
     while (units > 0)
     {
       p->Move();
       units--;
     }
   }
   return;
}

//*********************************************************
void HWep(char w, int level, Player * p, ArsenalType & arsenal, MapSquadType & squadMap){
  string wep= ""; 
  WpnClass::WpnType wpn;
  
  if (p->HasWeapon())
  {
    WpnClass::WpnType oldWpn= WpnClass::StrToWpnType(p->WeaponName());
    if (oldWpn != WpnClass::GRENADE)
    {
    arsenal[squadMap[p->Name()]][oldWpn]++;
    }
    p->DropWeapon();  
  }
    
  switch (w)
  {
    case 'g': wpn= WpnClass::GRENADE;  break;
    case 'h': wpn= WpnClass::HVYWPN; break;
    case 'p': wpn= WpnClass::PISTOL; break;
    case 'r': wpn= WpnClass::RIFLE; break;
  }
  wep= WpnClass::WpnTypeToStr(wpn);
  
  MapWpnType locMap;
  locMap= arsenal[squadMap[p->Name()]];

  if (locMap.count(wpn) != 0)
  {
    p->GrabWeapon(wep, level);
    arsenal[squadMap[p->Name()]][wpn]--;
  }
  
  return;
}


//*********************************************************
bool BugTurn(MapSquadType & squadMap, ArsenalType & arsenal, Player * p){

    MenuRec menu;
    
    if(squadMap.count(p->Name()))
    {
      string sname= SquadToStr(squadMap[p->Name()]);
      BeforeTurn(p, sname, arsenal[squadMap[p->Name()]]);
      if (p->IsActive())
	  p->Move();
      AfterTurn(p, sname, arsenal[squadMap[p->Name()]], menu);
    }
    else
    {
      BeforeTurn(p);
      if (p->IsActive())
	  p->Move();
      AfterTurn(p);
    }  

  
  return (p->IsActive());
}

//*********************************************************
void End(QueueType & pQueue, ArsenalType & arsenal, MapSquadType & squadMap, VecSetType & squadSetVec){
  GameOver(pQueue, squadSetVec, squadMap, arsenal);
  int qSize= pQueue.size();
  Player * p;
  for (int i= 0; i < qSize; i++)
  {
    p= pQueue.front(); 
    pQueue.pop();
    delete p;
  }
  return;
}