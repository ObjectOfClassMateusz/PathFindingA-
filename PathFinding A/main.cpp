#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <math.h>
#include <algorithm>
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;

vector<string>Map;

COORD k;
void CellChar(int x, int y)
{
    k.X =x;
    k.Y =y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

struct Point
{
    unsigned int x , y;
    char walkable;      //'#'   ' '
    Point* parent;
    unsigned int fc=0 ; //gc + hc
    unsigned int gc=0 ; //from start to this point
    unsigned int hc=0 ; //from end   to this point
    void Make(unsigned int , unsigned int , char );
};

void Point::Make(unsigned int xx, unsigned int yy , char unwalk)
{
    this->x = xx;
    this->y = yy;
    this->walkable=unwalk;
}

vector<vector<Point*>>grid;
vector<Point*>path;

vector<Point*>OPEN;
vector<Point*>CLOSED;

unsigned int GetDistance(Point * A, Point * B)
{
    int distX =  abs(static_cast<int>(A->x - B->x));
    int distY =  abs(static_cast<int>(A->y - B->y));
    if(distX > distY)
    {
        return 14*distY + 10*(distX - distY);
    }
    return 14*distX + 10*(distY - distX);
}

vector<Point*>GetNeighbour(Point *p)
{
        vector<Point*>Ns;
        int a = p->x-1;//5-1 = 4
        int b = p->y-1;//5-1 = 4
        for(int i=b;i<b+3;i++)//i=4
        {
            for(int j=a;j<a+3;j++)//j=4
            {
                if(j==p->x && i==p->y){ continue ;}
                int checkX = i;
                int checkY = j;
                if((i>=0 && j>=0) && (i<=grid.size()-1 && j<=grid[i].size()-1))
                {
                    Ns.push_back(grid[checkX][checkY]);
                }
            }
        }
        return Ns;
}


void deleteFrom( vector<Point*> & CONTENER , Point * C)
{   for(int i=0; i<CONTENER.size();i++)
    {
        if(( CONTENER[i]->x == C->x  ) && ( CONTENER[i]->y == C->y  ))
        {
            CONTENER.erase(CONTENER.begin()+i);
            break;
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
            //break;
        }
    }
    return false;
}

void Retrace(Point* s , Point* e)
    {
        vector<Point*> pathTemp;
        Point *c = e;
        while(c != s)
        {
            pathTemp.push_back(c);
            c = c->parent;
        }
        std::reverse(pathTemp.begin(), pathTemp.end());
        path = pathTemp;
    }

int main()
{


        fstream f;
        string x;
        f.open("mapa1.txt",std::ios::in);
        while(!f.eof())
        {getline(f,x);Map.push_back(x);}
        f.close();

        for(int i=0; i<Map.size();i++)
        {
            vector<Point*> temp;
            for(int j=0; j<Map[i].length(); j++)
            {
                Point* p = new Point;
                p->Make(j,i,Map[i][j]);
                temp.push_back(p);
                p = new Point;
            }
            grid.push_back(temp);
            temp.clear();
        }

        for(int a=0; a<grid.size();a++)
        {
            for(int b=0; b<grid[a].size();b++)
            {
                cout<<grid[a][b]->walkable;
            }
            cout<<'\n';
        }


    Point* Start = new Point;
    Point* End   = new Point;
    Point* current = new Point;

    unsigned int StartX = 16;
    unsigned int StartY = 4;

    unsigned int EndX = 59;
    unsigned int EndY = 33;

    Start = grid[StartY][StartX];
    End = grid[EndY][EndX];

    OPEN.push_back(Start);
    while(OPEN.size()>0)
    {
        current = OPEN[0];
        for(int i=1; i<OPEN.size(); i++)
        { // current = node with (lowest fc or the same and hc must be lowest)
            if(OPEN[i]->fc < current->fc || OPEN[i]->fc == current->fc && OPEN[i]->hc < current->hc)
            {
                current = OPEN[i];
            }
        }
        deleteFrom(OPEN,current);
        CLOSED.push_back(current);
        if(current == End)
        {
            Retrace(Start,End);
            break;
        }
        for(Point * n : GetNeighbour(current))
        {//    pomiń jeśli nie do chodzenia lub jest w CLOSED
            if(n->walkable=='#' || IsIn(CLOSED,n->x , n->y))
            {continue;}
            int newMovementCostToN = current->gc + GetDistance(current , n);

            if((newMovementCostToN < n->gc)  || !IsIn(OPEN,n->x,n->y))
            {
                n->gc = newMovementCostToN;
                n->hc= GetDistance(n,End);
                n->fc = n->gc + n->hc;
                n->parent = current;
                if(!IsIn(OPEN,n->x,n->y))
                {
                    OPEN.push_back(n);
                }
            }
        }
    }

    for(int i=0; i<path.size();i++)
    {
        CellChar(path[i]->x ,path[i]->y );
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
        Sleep(100);
        cout<<" ";
    }

CellChar(Start->x,Start->y);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);cout<<"S";
CellChar(End->x,End->y);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);cout<<"E";

CellChar(0,45);
std::cin>>x;

return 7;
}
