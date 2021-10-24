#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <windows.h>

using namespace std;

class Logic 
{
private:
  int mrXPos;
  int mrXVisible=-1;
  int turnNumber;
  bool gameEnd=false;
  // All connected nodes of graph are given below
    vector<int> l0 =  {1, 35, 36}; 
    vector<int> l1 =  {0, 2, 8};
    vector<int> l2 =  {1, 6, 3, 7};
    vector<int> l3 =  {5, 2};
    vector<int> l4 =  {5};
    vector<int> l5 =  {3, 4, 6, 12};
    vector<int> l6 =  {2, 5, 7, 11};
    vector<int> l7 =  {2, 6, 8, 10};
    vector<int> l8 =  {1, 7, 9};
    vector<int> l9 =  {8, 10, 18, 30, 31, 34}; 
    vector<int> l10 = {7, 9, 11};
    vector<int> l11 = {6, 10, 12, 17, 18};
    vector<int> l12 = {5, 11, 13};
    vector<int> l13 = {12, 14};
    vector<int> l14 = {13, 15, 17};
    vector<int> l15 = {14, 16, 21};
    vector<int> l16 = {15, 17, 18, 19};
    vector<int> l17 = {11, 14, 16};
    vector<int> l18 = {9, 11, 16};
    vector<int> l19 = {16, 20, 21};
    vector<int> l20 = {19, 21, 22, 30};
    vector<int> l21 = {15, 19, 20};
    vector<int> l22 = {20, 23};
    vector<int> l23 = {22, 24};
    vector<int> l24 = {23, 25, 30};
    vector<int> l25 = {24, 26, 29};
    vector<int> l26 = {25, 27, 28};
    vector<int> l27 = {26, 28, 33};
    vector<int> l28 = {26, 27, 29, 33};
    vector<int> l29 = {25, 28, 30, 31, 32};
    vector<int> l30 = {9,20,24, 29, 31};
    vector<int> l31 = {9, 29, 30, 34};
    vector<int> l32 = {29, 33, 35};
    vector<int> l33 = {27, 28, 32};
    vector<int> l34 = {9, 31, 35};
    vector<int> l35 = {0, 32, 34, 36};
    vector<int> l36 = {0, 35};
    
    //adjacencey list
    vector<int> adjList[37] = {l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l30, l31, l32, l33, l34, l35, l36};
    vector <int> DetectivePos = {-1,-1};// detective's initial location 
    int priority[37] = {0}; //all priority are set to false
  public:
  
  void gameStart() //function by which our game starts.
   {
    turnNumber=1;//initializing turn number to 1
    int temp1=0, temp2=0, temp3=0;//temporary variables
   do
    {      
      srand(time(0));  // Initialize random node generator for all the 3 players(initializing the seed with a number from the time so as to keep the genration totaly random)
      temp1=rand() % 37;   // %number indicates the max value that can be genrated randomly
      temp2=rand() % 37;   //it will generate a rand number less than 37 as remainder of xmod37 is less
      temp3=rand() % 37;
      cout<<endl;
    } while(temp1==temp2 || temp2==temp3 || temp3==temp1);//condition to make sure no 2 values are same
    DetectivePos[0]=temp1;
    DetectivePos[1]=temp2;
    mrXPos=temp3;
    gameLoop();
    
  }
    void gameLoop()   //basic Game order in which it has to be played
   {
    do
    {
      cout<<"***************** turn "<<turnNumber<<" *****************"<<endl;
      cout<<"current detective position: ";
      for(auto x:DetectivePos)
      {

        cout<<x<<" "; 
      }
      cout<<endl;
      
      updateKeyValues(); //function of updating detective's position
      
      moveX();   
      //cout<<"current mr.X postion: "<<mrXPos<<endl;
      if(!gameEnd)
      {
        moveDetective();
        if (turnNumber == 3 || turnNumber == 8 || turnNumber == 13 || turnNumber == 18 || turnNumber == 24)
          {
            revealXPos();
          }
        
        
        checkCondition();  }
        turnNumber++;
    }while(!gameEnd); 
    return ;
  }
    void updateKeyValues() //function of updating detective's position
    {
        for (int i = 0; i < 2; i++)
        {
            
        int val=DetectivePos[i];
        queue<int> readyQueue;//initializing queue
        readyQueue.push(val);
        bool visited[37] = {0};
        visited[val] = 1;
        int p[37] = {0};//indiviusal priority
        while (!readyQueue.empty())//BFS
        {
            int current = readyQueue.front();
            readyQueue.pop();
            //cout << current << endl;
            for (auto x : adjList[current])
            {
                if (!visited[x])
                {

                    readyQueue.push(x);
                    visited[x] = 1;
                    p[x] = p[current] + 1;
                    //cout << x << " " << p[x] << endl;
                }
            }
        }
        //cout << "***********************" << endl;
        for (int i = 0; i < 37; i++)
        {
            priority[i] += p[i];//here we are adding the indivisual genrated layers to the over all hueristic
        }
        priority[val]=-1000;//setting the position of detective to -1000 as a no region and a condition check
        }
       
  }
  void moveX() //this fuction defines the movement of Mr.X this follows a greedy approach based on the hueristc genrated in the funcion updateKeyValues()
  { 
      int choose=-1;//defining to an impossible situation
      int value=0;
      for(auto y: adjList[mrXPos])
      { 
        if(priority[y]>value && priority[y]>0)//condition to check if move is valid and better then the other options [MAX]
        {
          value =priority[y]; 
          choose=y; // ngbr node
        }
      }
      if (choose == -1)//the case where mr.X can only walk into a detective where he is caught
      {
        cout<<"Mr.X was caught no more possible moves"; //caught in a corner cant move
        gameEnd=true;
      }
      else
      mrXPos=choose;
      resetPriority();
  }
  void resetPriority()
  {
      for(int i=0;i<37;i++)
      {
          priority[i]=0;
      }
  }

  
  void moveDetective() //function which tells us the current and next position of detective and gives us option to select next loaction too
  {
    for(int x=0;x<2;x++)
    {
       int temp=0;
       cout<<"current position of detective "<<DetectivePos[x]<<endl;
       cout<<"options to which you can move: ";
       for(auto y: adjList[DetectivePos[x]])
       {
         if(DetectiveChecker(y,DetectivePos[x]))
         cout<<y<<"(Detective) ";
         else
         cout<<y<<" ";
       }
       cout<<endl;
       do
       { 
        
        cout<<"please enter your choice"<<endl;
        cin>>temp;

       }while(!validMove(x,temp));
    }
  }
   bool DetectiveChecker(int pos, int current)//check if detective is there on next node or not.
  {
    
      for(auto y: DetectivePos)
      {
        if(pos == y)
        {
          return true;
        }
      }
    return false;
  }
  bool validMove(int detectiveNumber,int pos )
  { 
    bool possibleMove=false;
    bool invalidMove=false;
 
    for(auto x:adjList[DetectivePos[detectiveNumber]])  //to check if there is any possible move or not
    {
      if(pos==x)
      {
        possibleMove=true;
      }
    }
    if(!possibleMove)
    {
      cout<<"invalid move please try again"<<endl;
      return false;
    }
    for(auto x: DetectivePos)  //to check if there is detective or not
    {
      if(pos == x)
      {
        invalidMove=true;
      }
    }
    
    if(invalidMove)
    {
      cout<<"there is a detective at that position"<<endl;
      return false;
    }
    DetectivePos[detectiveNumber]=pos;
    return true;
    
  }
  void revealXPos() // function telling us the current position of Mr. X .
  {
    cout<<"Mr.X was at position:"<<mrXPos<<endl;
    // mrXVisible=mrXPos;
  }
  int checkCondition()  //function checking if detective has caught Mr. X or not .
  {
    bool mrXCaught=false;
    bool mrXSurvived=false;
    for(auto x:DetectivePos)
    {
      if(x == mrXPos)
      {
        mrXCaught = true;
        break;
      }
    }
      if(turnNumber == 30)//check if MrX survived
      {
        mrXSurvived=true;
      }
      if(mrXCaught)//if mrX was caught
      {
        cout<<"Mr.X was caught"<<endl;
        gameEnd=true;
    
      }
      else if(mrXSurvived)
      {
        cout<<"30 turns are over Mr.X survived";
        gameEnd=true;
      }
    
    return 0;
  }
  
};
int main()
{   system("Color F0");
    Logic one;
    one.gameStart();
}
