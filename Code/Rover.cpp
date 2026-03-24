#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
#include<algorithm>
#include<limits>
#include<random>
#include <cstdlib>
#include<conio.h>
using namespace std;

class Rover;
class Map;

class Rover
{   protected:
        int x=0,y=0;
        int Energy=100;
    public:
        void Lore();
        int getX(){return x;}
        int getY(){return y;}
        int getEnergy(){return Energy;}
        void Movment(char way, Map &m);
        void addEnergy(int amount) 
        {
            Energy += amount; 
            if(Energy > 100) Energy = 100; 
        }
        
};

class Map
{
    protected:
        char grid[20][20];
        int Rocks = 50;
        int Sample = 5;
        int Energy_boost = 6;
        int SamplesCollected = 0;
    public:
        void GetGrid(){grid;}
        void dots();
        void FinalMap();
        void Display(int roverX, int roverY, int Energy);
        void EnergySample(Rover &r);
        int getsample() { return SamplesCollected; } 
        void addSamples() { SamplesCollected++; }
        char getTile(int x, int y) { return grid[y][x]; }
};

void Map :: Display(int roverX, int roverY, int Energy)
{
    system("cls");
    cout<<"Energy: "<<Energy<<" % "<<endl;
    cout << "------------------------------------------" << endl;
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            if(i==roverY && j==roverX)
                cout<<"R";
            else
                cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout << "------------------------------------------" << endl;
    cout << "Samples collected: " << SamplesCollected << " / 5" << endl;
    cout << "[W,A,S,D] - Move | [X] - Exit" << endl;
}

void Map :: EnergySample(Rover &r)
{
    int rx = r.getX();
    int ry = r.getY();

    if(grid[ry][rx]=='E')
    {
        r.addEnergy(20);
        grid[ry][rx]='.';
        cout<<"+ 20% Energy !"<<endl;
    }
    else if(grid[ry][rx]=='S')
    {
        grid[ry][rx]='.';
        addSamples();
        cout<<getsample()<<" / 5 samples collected!"<<endl;
    }
}

void Rover :: Movment(char way, Map& m)
{
    int nextX = x;
    int nextY = y;

    if(way=='w' && y>0)
        nextY--;
    else if(way=='s' && y<19)
        nextY++;
    else if(way=='a' && x>0)
        nextX--;
    else if(way=='d' && x<19)
        nextX++;
    
    if(m.getTile(nextX,nextY) != '#')
    {
        x=nextX;
        y=nextY;
    }
    else
        Energy -= 2;

    Energy --;
}

void Map :: dots()
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            grid[i][j]='.';
        }
    }
    grid[0][0] = 'B';
}

void Map :: FinalMap()
{
    dots();
    Rocks = 50;
    Sample = 5;
    Energy_boost = 6;

    while(Rocks>0)
    {
        int x = rand() % 20;
        int y = rand() % 20;

        if(grid[x][y]=='.')
        {
            grid[x][y]='#';
            Rocks --;
        }
    }

    while(Sample>0)
    {
        int x = rand() % 20;
        int y = rand() % 20;

        if(grid[x][y] == '.')
        {
            grid[x][y]='S';
            Sample --;
        }
    }

    while(Energy_boost>0)
    {
        int x = rand() % 20;
        int y = rand() % 20;

        if(grid[x][y]=='.')
        {
            grid[x][y]='E';
            Energy_boost --;
        }
    }
}

void Rover :: Lore()
{
    ifstream lore("Lore.txt");
    string line;

    if(!lore.is_open())
    {
        cout<<"Lore cannot be reached now!"<<endl;
        return;
    }

    while(getline(lore,line))
        cout<<line<<endl;

    lore.close();
    cout<<"[Press ENTER to go back]"<<endl;
    cin.ignore();
    cin.get();
}

void Game()
{
    Rover r;
    Map m;
    m.FinalMap();
    char input = ' ';

    while(input != 'x' && r.getEnergy()>0)
    {
        m.Display(r.getX(), r.getY(), r.getEnergy());
        input = _getch();

        if(input != 'x') 
        {
            r.Movment(input,m);    
            m.EnergySample(r);   

            if(m.getsample() == 5) 
                cout << "ALL SAMPLES COLLECTED! RETURN TO BASE (B) !!!" << endl;
            

            if(m.getsample() == 5 && r.getX() == 0 && r.getY() == 0)
            {
                m.Display(r.getX(), r.getY(), r.getEnergy()); 
                cout << "==========================================" << endl;
                cout << "   MISSION SUCCESS! ROVER RETURNED HOME!  " << endl;
                cout << "==========================================" << endl;
                _getch();
                return; 
            }
        }
    }

    system("cls");
    if(r.getEnergy() <= 0)
        cout << "CRITICAL ERROR: Rover ran out of energy!" << endl;
    
    else 
        cout << "Mission aborted by pilot!" << endl;
    
    cout << "Press any key to return to Main Menu..." << endl;
    _getch();
}

void Start()
{
    cout << "   __\n";
    cout << " _/[]\\_\n";
    cout << "/______\\\n";
    cout << "  /||\\\n";
    cout << " /_||_\\\n";
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<"[Press ENTER to start game!]"<<endl;
    cin.ignore();
    cin.get();
}

void MainMenu()
{
    Rover r;
    int n=10;
    while(n!=3)
    {
        cout << "==================================================\n";
        cout << "                  MARS EXPLORER                  \n";
        cout << "==================================================\n";
        cout << "\n";
        cout << "                     MAIN MENU                    \n";
        cout << "\n";
        cout << "                   1. Start Mission               \n";
        cout << "                   2. Lore                        \n";
        cout << "                   3. Exit                        \n";
        cout << "\n";
        cout << "==================================================\n";
        cout << "Select option: ";  

        int i;
        cin>>i;

        if(i==1)
        {
            Start();
            Game();
        }
        else if(i==2)
            r.Lore();
        else
            n=3;
    }
}

int main()
{
    srand(time(0));
    MainMenu();
    return 0;
}
