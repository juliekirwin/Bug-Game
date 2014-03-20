// board.cpp

#include "board.h"

BoardClass * BoardClass::bd =NULL;

//*********************************** constructors/dest/oper=
BoardClass::BoardClass( ):ROWSIZE(3), COLSIZE(4)
{
  grid = new CellPtr[ROWSIZE*COLSIZE];
}

BoardClass::BoardClass(int r, int c ):ROWSIZE(r), COLSIZE(c)
{
  grid = new CellPtr[ROWSIZE*COLSIZE];
}

BoardClass::BoardClass(const BoardClass& b):
  ROWSIZE(-1), COLSIZE(-1)
{
  // never called
}

BoardClass& BoardClass::operator=(const BoardClass& b)
{
  //never called
}


BoardClass::~BoardClass( )
{
//  cout << "called destructor:";
  for (int i = 0; i < COLSIZE*ROWSIZE; i++)
     delete grid[i];
  if (grid)
    delete[] grid;
  delete bd;
  bd = NULL;
}

//*********************************** static methods
BoardClass * BoardClass::GetBd( )
{
  return bd;
}

vector<Player*> BoardClass::CreateBoard( )
{
  if (bd==NULL)
  bd = new BoardClass;
  return bd->LoadBoard( );
}

vector<Player*> BoardClass::CreateBoard( int row, int col)
{
  if (bd == NULL)
    bd = new BoardClass(row, col);
  return bd->LoadBoard( );
}


//*********************************** loadboard & create bugs

vector<Player *> BoardClass::LoadBoard( )
{
  vector<Player *> allBugs;
  vector<Player *> bugs;
  ifstream fin;
  char terr;
  char trap;
  char bugtype;
  int data;
  fin.open(BOARD_FILE.c_str());
  int r, c, i=0;
  for (r = 0; r<ROWSIZE; r++)
  {
    for (c = 0; c<COLSIZE; c++)
    {
      fin>>terr>> trap;
      switch (trap)
      {
        case 'B': fin >> data >> bugtype;
                  bugs = CreateBugs(data, bugtype, allBugs);
                  grid[i] = new BugHole(r,c,CellClass::CharToTerr(terr), bugs);
                  break;
        case 'L': fin>>data;
                  grid[i] = new LandMine(r,c,CellClass::CharToTerr(terr), data);
                  break;
        case 'S': fin>>data;
                  grid[i] = new SinkHole(r,c,CellClass::CharToTerr(terr), data);
                  break;                 
        case 'N': 
        default: grid[i] = new CellClass(r,c,CellClass::CharToTerr(terr)); 
                  break;
      }
      fin.ignore(256,'\n');
        
      i++;
    }
  }
  return allBugs;  
}

string ConvertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

vector<Player *> BoardClass::CreateBugs(int num, char type, vector<Player *>&allBugs)
{
  static int total = 0;
  vector<Player *> bugs;
  Player * bug;
  string name = "";
  for (int i = 0; i<num; i++)
  {
    total++;
    name = "";
    name = name +type;
    name = name + ConvertInt(total);
    switch(type)
    {
      case 'S': bug = new Player(name,Player::SPIDER);
                break;
      case 'K': bug = new Player(name,Player::KILLERANT);
                break;
      case 'H': 
      default: bug = new Player(name,Player::HORNET);
    }
    bugs.push_back(bug);
    allBugs.push_back(bug);
  }
  return bugs;
}

void BoardClass::Display(ostream& out) const
{
  int r, c, i;
  string cellstr;
  int colSize[COLSIZE];
  for (c=0; c<COLSIZE;c++)
    colSize[c] = 8;

  // Finds the largest column item for each column
  // used to print the output in tabular format below    
  for (r=0; r<ROWSIZE; r++)
  {
    for (c=0; c<COLSIZE; c++)
    {
      stringstream sstr;
      i = Offset(r,c,COLSIZE);
      grid[i]->Display(sstr);
      cellstr = sstr.str();
      if (cellstr[0] == '(') cellstr = " " +cellstr;
      if (cellstr.size()> colSize[c])
        colSize[c] = cellstr.size();
     }
   }   
   
  // Using the colSize array set each column width for the
  // cell contents when printing the entire board 
  out<<endl;
  for (r=0; r<ROWSIZE; r++)
  {
    for (c=0; c<COLSIZE; c++)
    {
      stringstream sstr;
      i = Offset(r,c,COLSIZE);
      grid[i]->Display(sstr);
      cellstr = sstr.str();
      if (cellstr[0] == '(') cellstr = " " +cellstr;
      out << "| "<<left <<setw(colSize[c]) << cellstr<<" ";
    }   
    out<<"|"<<endl;
  } 
  out<<endl;
}  

bool BoardClass::PlacePlayer(Player * p, int r, int c)
{
      int ip, rp, cp;  // previous coordinates
      int i;   // new offset
      bool ok=true;

      rp = p->Row( );
      cp = p->Column( );
      
      // just incase player is in a cell
      // this will remove the player before placing
      // player in new cell
      if ((rp!=-1) && (cp!=-1))
      {
        ip = Offset(rp,cp, COLSIZE);
        grid[ip]->ExitCell(p);
      }
      
      if ((rp!=-1) || (cp !=-1) ||
          (r <0) || (c<0) || 
         (c >=COLSIZE) || (r>=ROWSIZE))
      {
        ok = false;
      }
      else  // place the player
      {
        i = Offset(r,c,COLSIZE);
//        cout << "Placing " << p->Name() <<" in ["<<r<<","<<c<<"]"<<endl;
        ok = grid[i]->EnterCell(p);

      }
      return ok;
}        

Player * BoardClass::FindPlayer(PlayerClass* p) const
{
  Player * player = NULL;
  vector<Player *> occ;
  int i,r,c;  // current coordinates
  
  // Need to find the Player from the PlayerClass
  r = p->Row();
  c = p->Column();
  i = Offset(r,c,COLSIZE);
  occ = grid[i]->Occupants( );
  for (i = 0; i<occ.size(); i++)
  {
    if (p->Name() == occ[i]->Name())
      player = occ[i];
  }
  return player;
}  

int BoardClass::MoveCost(PlayerClass/*called from PC Move*/ * p, int units) const
{
  Player * player = FindPlayer(p);

  // If the Player is found then call the
  // MoveCost using the Player address
  if (player)
    return MoveCost(player, units);
  else
    return 0;

}

bool BoardClass::MoveForward(PlayerClass/*called from PC Move()*/ * p, int units)
{
  Player * player = FindPlayer(p);

  // If the Player is found then call the
  // MoveForward using the Player address
  if (player)
    return MoveForward(player, units);
  else
    return false;
}

int BoardClass::FindNewCell(Player * p, int units) const
{
  int ip, rp, cp; // previous coordinates
  int i, r, c;  // new coordinates
  char dir;
  int cost;
  // determine the cell the player
  // wants to move into
  r = rp = p->Row( );
  c = cp = p->Column( );
  dir = p->Direction( );
  for (int u=0; u<units; u++)
  {
    UpdateRowCol(dir,r,c);
  }
  ip = Offset(rp,cp, COLSIZE);
  i = Offset(r,c, COLSIZE);
//  cout << "old: ["<<rp<<","<<cp<<"] = "<<ip <<endl;
//  cout << "new: ["<<r<<","<<c<<"] = "<<i <<endl;
  return i;
}

int BoardClass::MoveCost(Player * p, int units) const
{
  int i;  // new offset
  i = FindNewCell(p,units);     // offset of new cell
  return grid[i]->EnterCost( );
}

bool BoardClass::MoveForward(Player * p, int units)
{
  bool ok=true;
  int ip; // previous offset
  int i;  // new offset
  int cost;
  i = FindNewCell(p, units);
  cost = grid[i]->EnterCost( );
  if (cost > p->Momentum( ))
    ok = false;
  else
  {
    ip = Offset(p->Row(),p->Column(), COLSIZE); // offset of current cell
    ok = grid[ip]->ExitCell(p);
    if (ok)
      ok =grid[i]->EnterCell(p);
  } 
  return ok;  
}



void BoardClass::PrintBoard(ostream & out, Player *p) const
{
  char m;  // holding spot for player direction
  char terr;

  int enemies= 0, friends=0;
  int rp,cp;  // current coordinates
  int r,c,i;  // iteration variables
  rp = p->Row( );
  cp = p->Column( );
  out <<"|";
  PrintLine(out,COLSIZE *10,"=");
  out<<"|"<<endl;
  for (r = 0; r<ROWSIZE; r++)
  {
    out << "|";
    for (c=0; c<COLSIZE; c++)
    {
//      if ((r == rp) && (c ==cp)) m = 'X';
//      else 
      m = ' ';
      i = Offset(r,c,COLSIZE);
      terr = grid[i]->Terrain( );
      friends =(grid[i]->Friends(p)).size();
      enemies =(grid[i]->Enemies(p)).size();
      if (grid[i]->InCell(p))
      {
        switch (p->Direction( ))
           {
              case 'N': m = '^';break;
              case 'S': m = 'v';break;
              case 'E': m = '>';break;
              default: m = '<';
          }
      }
      out << "["<<m<<terr<<" F"<<setw(1)<<friends
          << " E"<<setw(1) <<enemies<<"]";
    } // column
    out << "|";
    out<<endl;
    out << "|";
    PrintLine(out,COLSIZE *10,"=");
    out <<"|"<<endl;
  } // row
  out <<endl;
}

void BoardClass::PrintLine(ostream& out, int num, string s) const
{
  for (int i = 0; i<num; i++)
    out<<s;
}

int BoardClass::Offset(int r, int c, int colSize) const
{
      return(r*colSize +c);
} 

void BoardClass::UpdateRowCol(char dir, int& r, int & c) const
{
    // Calculates the new coordinates
    // wraps the board
    if ((r>=0)&& (c>=0))
    {
      switch (toupper(dir))
      {
        case 'N': r= (r==0)*ROWSIZE+r-1; return;
        case 'S': r=(r+1)%ROWSIZE; return;
        case 'E': c= (c+1)%COLSIZE; return;
        case 'W': c=(c==0)*COLSIZE+c-1; return;
      }
    }
    return;
}

/*
int main( )
{
  BoardClass * bd;
  BoardClass::CreateBoard(6,4); //Creates a 6X4 board
  bd = BoardClass::GetBd( );
  bd->Display(cout);

  return 0;
}
*/
