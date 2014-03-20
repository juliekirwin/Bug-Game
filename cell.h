// cell.h

#ifndef _CELL
#define _CELL

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "phc.h"

using namespace std;

//enum TrapType {NO_TRAP, BUG_HOLE, LAND_MINE, SINK_HOLE};

void Combat(Player * attacker, Player * target);

class CellClass
{
 public:
  enum LandType {CLEAR, MNT, ROCKY, SWAMP};
  virtual ~CellClass( );  
  CellClass(int r, int c, LandType land=CLEAR);
  char Terrain( ) const;
  static  char TerrToChar(LandType terr) ;
  static LandType CharToTerr(char c);
  
//  TrapType Trap( ) const;
  virtual bool EnterCell(Player *p);
  bool ExitCell(Player *p);
  int EnterCost( ) const;
  bool AddOcc(Player *p);
  void ProcEnemies(Player *p);
  vector<Player *> Occupants( ) const;
  vector<Player *> Enemies(const Player *) const;     
  vector<Player *> Friends(const Player *) const;     
  bool InCell(Player *p) const;
  
  bool IsClear( ) const;
  bool IsMnt( ) const;
  bool IsRocky( ) const;
  bool IsSwamp( ) const;

  virtual void Display(ostream& ) const ;

  protected:
    int row, col;
    //virtual void Trigger(Player * );

  private:
    CellClass( );
    CellClass(const CellClass&);
    CellClass& operator=(const CellClass&);
    LandType terr;
    vector<Player *> occ;
    //TrapType trap;
};

class BugHole: public CellClass
{
  public:
    BugHole( int r, int c, LandType land, vector<Player *> bugs);
    bool EnterCell(Player *);  
    void Display(ostream& out) const;  
  
  protected:
    bool Trigger(Player * );
  
  private:
     bool tripped;
     vector<Player *> bugs;
};




class SinkHole: public CellClass
{
  public:
    SinkHole(int r, int c, LandType land, int hazard);
    bool EnterCell(Player *);
    void Display(ostream& out) const;
  
  protected:
    bool Trigger(Player * );
  
  private:
    int hazard;
    
  
};


class LandMine: public CellClass
{
  public:
    LandMine(int r, int c, LandType land, int damage);
    bool EnterCell(Player *);
    void Display(ostream& out) const;
  
  protected:
    void Trigger(Player * );

  private:
    bool tripped;
    int damage;
  
};


  
#endif

