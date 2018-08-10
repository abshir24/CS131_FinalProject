#include <iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include <iostream>
#include <fstream>

using namespace std;

void retrieveSeats(char seats[][30],int size);

void displaySeats(char seats[][30],int size);

int main()
{
    char seats[15][30];
    
    retrieveSeats(seats,15);
    
    displaySeats(seats,15);
    

    return 0;
}


//This function retrieves the seats from the file and places them into a 2D array
void retrieveSeats(char seats[][30],int size)
{
    
    ifstream readIn;
    
    readIn.open("db.txt");
    
    char seat;
    
    int row=0,column=0;
    
    while(readIn>>seat){
        
        seats[row][column++] = seat;
        
        if(column==30){
            
            row++;
            
            column=0;
        }
        
    }
    
//    cout<<"Seat display test"<<endl;
//
//    for(int i = 0;i<size;i++){
//
//        for(int j = 0;j<30;j++)
//            cout<<seats[i][j];
//
//        cout<<endl;
//    }
    
}

//This function takes the newly updated 2D array of seats and organizes it to chart of seats.

void displaySeats(char seats[][30],int size)
{
    int i,j;
    
    cout<<"    "<<1;//5 space chars
    
    for(i = 2;i <= 30;++i)
        cout<<setw(5)<<i;//4 space chars
    
    cout<<endl;
    cout<<"   ----|";
    
    for(i = 2;i <= 30;++i)
        cout<<"----|";
    
    cout<<endl;
    
    for(i = 0;i <size;++i)
    {
        cout<<setw(2)<<i+1<<"|";
        
        
        for(j = 0;j <30;++j){
            
            
            
            cout<<setw(4)<<seats[i][j]<<"|";
        }
        
        cout<<endl;
        
        cout<<" -|----";
        
        for(j = 2;j < 30;++j)
            cout<<"|----";
        
        cout<<"|----|";
        cout<<endl;
        
    }
}
