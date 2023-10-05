/*
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠆⠜⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⠿⠿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣿⣿⣿
⣿⣿⡏⠁⠀⠀⠀⠀⠀⣀⣠⣤⣤⣶⣶⣶⣶⣶⣦⣤⡄⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿
⣿⣿⣷⣄⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡧⠇⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣾⣮⣭⣿⡻⣽⣒⠀⣤⣜⣭⠐⢐⣒⠢⢰⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣏⣿⣿⣿⣿⣿⣿⡟⣾⣿⠂⢈⢿⣷⣞⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⣷⣶⣾⡿⠿⣿⠗⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠻⠋⠉⠑⠀⠀⢘⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡿⠟⢹⣿⣿⡇⢀⣶⣶⠴⠶⠀⠀⢽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⡿⠀⠀⢸⣿⣿⠀⠀⠣⠀⠀⠀⠀⠀⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠹⣿⣧⣀⠀⠀⠀⠀⡀⣴⠁⢘⡙⢿⣿⣿⣿⣿⣿⣿⣿⣿
⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⠗⠂⠄⠀⣴⡟⠀⠀⡃⠀⠉⠉⠟⡿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠾⠛⠂⢹⠀⠀⠀⢡⠀⠀⠀⠀⠀⠙⠛⠿⢿

Jessie , we need to PathFinding (A*)

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;
using std::pair;

fstream f;
vector<string>Mape;

COORD k;
void CellChar(int x, int y)
{
    k.X =x;
    k.Y =y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

struct Point
{
    unsigned int x, y;
    vector<Point*>neighbour;
    unsigned int fc=0 ; //gc + hc
    unsigned int gc=0 ; //from start to this point
    unsigned int hc=0 ; //from end   to this point

    void Make(unsigned int , unsigned int);
    void Costs();
    void Root();
};

Point* Start = new Point;
Point* End   = new Point;
Point* current;
Point * current2 ;

unsigned int GetDistance        (unsigned int,unsigned int,unsigned int,unsigned int,bool=false);

bool         IsIn                ( vector<Point*> , unsigned int , unsigned int );
Point*        chooseSmallestFcost( vector<Point*>);

vector<Point*>OPEN;
vector<Point*>CLOSED;
vector<Point*>TRUEPATH;

void Point::Make(unsigned int xx, unsigned int yy)
{this->x = xx;this->y = yy;}

void Point::Costs()
{
    this->gc =0;
    this->hc=0;
    this->fc=0;

    this->gc= GetDistance(Start->x , Start->y ,this->x,this->y ,true);
    this->hc= GetDistance(End  ->x , End  ->y ,this->x,this->y );
    this->fc= this->hc + this->gc;
}

void Point::Root()
{
    int a = this->x-1, b=this->y-1;
    Point * Pusher123 = new Point;
    for(int i=b;i<b+3;i++)
    {
        for(int j=a;j<a+3;j++)
        {
            if((j>=0 && i>=0) && (i<=Mape.size()-1 && j<=Mape[i].size()-1)) //OUT OF BORDER
            {
                if(Mape[i][j] == ' ')//FREE SPACE
                {
                    if(j!=this->x || i!=this->y)// NO MID
                    {
                        Pusher123->Make(j,i);
                        {
                            CellChar(j,i);
                            this->neighbour.push_back(Pusher123);
                            Pusher123->Costs();///
                            if(!IsIn(OPEN,j,i))
                            {
                                if(!IsIn(CLOSED,j,i))
                                {
                                    OPEN.push_back(Pusher123); // IS IN vector OPEN (NO NEED TO SPAM NEIGHBOURS)
                                }
                            }
                        }
                        Pusher123 = new Point;
                    }
                }
            }
        }
    }
}

unsigned int GetDistance(unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey, bool heuristic)
{
    unsigned int distance=0;
    if(!heuristic)
    {
        while(sx != ex || sy != ey)
        {
            if(sx < ex && sy < ey)
            {
                sx++;  sy++; distance+=14;
            }
            else if(sx < ex && sy > ey)
            {
                sx++;  sy--; distance+=14;
            }
            else if(sx > ex && sy < ey)
            {
                sx--;  sy++; distance+=14;
            }
            else if(sx > ex && sy > ey)
            {
                sx--;  sy--; distance+=14;
            }
            else
            {   if(sx < ex)
                {
                    sx++;
                    distance+=10;
                }else if(sx > ex)
                {
                    sx--;
                    distance+=10;
                }
                if(sy < ey)
                {
                    sy++;
                    distance+=10;
                }else if(sy > ey)
                {
                    sy--;
                    distance+=10;
                }
            }
        }
        return distance;
    }
    else
    {
        int a=0;
        while(sx != ex || sy != ey)
        {
            for(int i=0; i<CLOSED.size()-a;i++)
            {
                if(sx == ex && sy == ey)//
                {
                    return distance;
                }

                if(IsIn(CLOSED[i]->neighbour,ex,ey))
                {
                    if(CLOSED[i]->x > ex && CLOSED[i]->y > ey)
                    {
                        ex++;  ey++; distance+=14;
                    }
                    else if(CLOSED[i]->x > ex && CLOSED[i]->y < ey)
                    {
                        ex++;  ey--; distance+=14;
                    }
                    else if(CLOSED[i]->x < ex && CLOSED[i]->y > ey)
                    {
                        ex--;  ey++; distance+=14;
                    }
                    else if(CLOSED[i]->x < ex && CLOSED[i]->y < ey)
                    {
                        ex--;  ey--; distance+=14;
                    }
                    else
                    {
                         if(CLOSED[i]->x > ex)
                         {
                            ex++;
                            distance+=10;
                         }
                         else if(CLOSED[i]->x < ex)
                         {
                            ex--;
                            distance+=10;
                         }
                         if(CLOSED[i]->y > ey)
                         {
                            ey++;
                            distance+=10;
                         }
                         else if(CLOSED[i]->y < ey)
                         {
                            ey--;
                            distance+=10;
                         }
                    }
                 a++;
                }
            }
        }
        return distance;
    }
}

Point* chooseSmallestFcost(  vector<Point*> CONTENER)
{
    Point* lowest = CONTENER[0];
    for(auto i : CONTENER)
    {
        if(lowest->fc > i->fc)
        {
            lowest = i;
        }
        if(lowest->fc == i->fc)
        {
            if(lowest->hc > i->hc)
            {
                lowest = i;
            }
        }
    }
    return lowest;
}

void deleteFrom( vector<Point*> & CONTENER , Point * current)
{   for(int i=0; i<CONTENER.size();i++)
    {
        if(( CONTENER[i]->x == current->x  ) && ( CONTENER[i]->y == current->y  ))
        {
            CONTENER.erase(CONTENER.begin()+i);     break;
        }
    }
}

bool IsIn(vector<Point*> CONTENER , unsigned int xx , unsigned int yy)
{
    for(int i=0; i<CONTENER.size();i++)
    {
        if(( CONTENER[i]->x == xx  ) && ( CONTENER[i]->y == yy  ))
        {
            return true;
            break;
        }
    }
    return false;
}


void SHOW(Point* uwu)/// /////////////////////// CHWILOWE
{
    if(uwu->neighbour.size() == 0)
    {

    }
    else
    {
        cout<<uwu->x<<" "<<uwu->y<<":{";
        for(auto qwe : uwu->neighbour)
        {
            cout<<"[";
            cout<<qwe->x;
            cout<<",";
            cout<<qwe->y;
            cout<<"]";
        }
        cout<<"}";cout<<endl;

        for(int i=0; i<uwu->neighbour.size(); i++)
        {
            SHOW(uwu->neighbour[i]);
        }
    }
}/// ////////////////////////////////////////////



void FIND(Point * P , unsigned int sx,unsigned int sy )
{
    if(sx == P->x && sy == P->y)
    {
        current2 = P;
        return ;
    }
    else
    {
        for(int i=0; i<P->neighbour.size();i++)
        {
            FIND(P->neighbour[i],sx,sy);
        }
    }
}

bool IsHaveANeighbour(Point * Poin , unsigned int sx,unsigned int sy)
{
    for(auto qwe : Poin->neighbour)
    {
        if(qwe->x == sx && qwe->y == sy)
        {
            return true;
        }
    }
    return false;
}

void NeighbourOfWho(Point * Poin , unsigned int sx,unsigned int sy)
{
    if( IsHaveANeighbour(Poin,sx,sy) )
    {
        current2 = Poin;
        return ;
    }
    else
    {
        for(int i=0; i<Poin->neighbour.size();i++)
        {
            NeighbourOfWho(Poin->neighbour[i], sx, sy);
        }
    }
}


int main()
{
    {
        string x;
        f.open("mapa1.txt",std::ios::in);
        while(!f.eof())
        {getline(f,x);Mape.push_back(x);}
        for(auto z : Mape)
        {cout<<z<<endl;}
    }



    Start->Make(16,37);
    End->Make(36,1);
    Start->Costs();









/// ###########
////////////////

OPEN.push_back(Start);
    while(true)
    {
        current = chooseSmallestFcost(OPEN);
        deleteFrom(OPEN,current);
        CLOSED.push_back(current);
        current->Root();
        if(current->x == End->x && current->y == End->y)
        {
            break;
        }
    }

///////////////
/// ###########



FIND(Start,End->x,End->y);

TRUEPATH.push_back(current2);

while(current2->x != Start->x || current2->y != Start->y)
{
    NeighbourOfWho(Start,current2->x,current2->y);
    TRUEPATH.push_back(current2);
}







for(auto i: TRUEPATH)
{
    CellChar(i->x,i->y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 19);
    Sleep(100);
    cout<<" ";

}

CellChar(Start->x,Start->y);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);cout<<"S";
CellChar(End->x,End->y);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);cout<<"E";



SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);





CellChar(0,45);
int stop;
std::cin>>stop;

return 0;}
