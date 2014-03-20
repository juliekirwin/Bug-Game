// board.h

#ifndef _BOARD
#define _BOARD

#include <vector>
#include <iostream>
#include <sstream>
#include "gamefiles.h"
#include "cell.h"
#include "p5.h"  // this was should have the header for your handleclass
// include board.h in your playerclass cpp file (NOT header file!!)

using namespace std;
using namespace GameFiles;

class BoardClass
{
  public:
    static BoardClass* GetBd( );
    // Returns a pointer to the board
    // pre:  board should already be created
    // post: returns a pointer to the board, NULL if no board created

    static vector<Player *> CreateBoard( );
    // Creates the board using a default size
    // pre:  none
    // post: the board is created, unless it already existed
    
    static vector<Player *> CreateBoard(int r, int c);
    // Creates the board using a default size
    // pre:  none
    // post: the board is created, unless it already existed
    
    ~BoardClass( );
    // destructor for the board
    
    vector<Player *> Occupants(Player * player) const;
    // Returns the vector of occupants for a cell inhabited by player
    // pre:  none
    // post: returns a vector of occupants, empty of player not on board
    
    vector<Player *> Enemies(Player * player) const;
    // Returns the vector of enemies for a cell inhabited by player
    // pre:  none
    // post: returns a vector of enemies, empty of player not on board
    
    vector<Player *> Friends(Player * player) const;
    // Returns the vector of friends for a cell inhabited by player
    // pre:  none
    // post: returns a vector of friends, empty of player not on board
    

    bool PlacePlayer(Player *p, int row, int col);
    // Moves a player into a cell, used for initial location
    // pre:  player not on board (will remove from cell if the player is)
    // post: player moved into a cell on the board
    
    bool MoveForward(Player * p, int units);
    // Moves a player a specific units forward
    // pre:  player must be on the board, units must be >=0
    // post: If terrain permits and player has momentum, 
    //       then player is moved forward a specific number of units
    
    int MoveCost(Player * p, int units) const;
    // Checks the move cost for a player to move units in a forward directions
    // pre:  player must be on the board, units must be >=0
    // post: returns the cost of moving forward, 
    //       >=200 is return if player cannot move forward
    
    bool MoveForward(PlayerClass * p, int units);
    // Moves a player a specific units forward
    // pre:  player must be on the board, units must be >=0
    // post: If terrain permits and player has momentum, 
    //       then player is moved forward a specific number of units
    
    int MoveCost(PlayerClass * p, int units) const;
    // Checks the move cost for a player to move units in a forward directions
    // pre:  player must be on the board, units must be >=0
    // post: returns the cost of moving forward, 
    //       >=200 is return if player cannot move forward
    
    void Display(ostream& out) const;
    // Displays the board using the cell Display format
    // pre:  out should be open
    // post: board is written to the output file
    
    void PrintBoard(ostream& out, Player * player) const;
    // Displays the board for a player using players coordinates
    // pre:  out should be open
    // post: Board is wrriten to output file for player
        
  private:
    typedef CellClass* CellPtr;
    // used to access the board grid
    
    static BoardClass * bd;
    // instance of the board
    
    const int ROWSIZE;
    // constant set when board is created
    
    const int COLSIZE;
    // constant set when board is created
    
    CellPtr *grid;
    // grid that contains the board information
    
    // Disallowed methods
    BoardClass( );
    BoardClass(int r, int c);
    BoardClass(const BoardClass&);
    BoardClass& operator=(const BoardClass&);
    
    vector<Player *> LoadBoard( );
    // Loads the board from the file
    // pre:  BOARD_FILE must be ready for input with a data line
    //       for each cell 
    //       first char terrain: C or M or R or S
    //       second char trap: N or B or L or S
    //       if trap then trap data follows:
    //          bug hole data: number of bugs followed by type (H, K, S)
    //          Landmine and sinkhole data: number indicating damage & hazard
    // post: cells are created in row major order
    
    vector<Player *> CreateBugs(int num, char type, vector<Player *>& allBugs);
    // Create the bugs given the number, and type
    // pre:  number and type needs proper values
    // post: bugs are created and appended to the allBugs vector,
    //       new bugs returned from the function.
    
    void PrintLine(ostream& out, int num, string s) const;
    // Prints a line to the output stream
    
    int Offset(int r, int c, int colSize) const;
    // Calculates the offset for the grid given the row & col value
    
    void UpdateRowCol(char dir, int& r, int & c) const;
    // Returns the updated row and column given the direction and current coor.

    Player * FindPlayer(PlayerClass *p) const;
    // Finds the Player in the cell when given the PlayerClass object
    // Search is done by the player name.  Name must be unique in the cell!!
    
    int FindNewCell(Player *p, int units) const;
    // Determines the new cell the player is accessing
        
};

#endif


