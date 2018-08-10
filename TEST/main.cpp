#include <iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include <iostream>
#include <fstream>

using namespace std;

void retrieveSeats(char seats[][30],int size);

void displaySeats(char seats[][30],int size);

void viewTicketPrices(const double[],int size);

int main()
{
    char seats[15][30];
    
    const double ticketPrices[15] = {50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
    
    retrieveSeats(seats,15);
    
    displaySeats(seats,15);
    
    viewTicketPrices(ticketPrices,15);

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
    int i,j,width;
    double rowPrice = 50.0;
    
    cout<<"    "<<1;//5 space chars
    
    width = 5;
    
    for(i = 2;i <= 31;++i)
        //If i is less than 31 display row number else display price header
        
        i < 31? cout<<setw(width)<<i : cout<<setw(8)<<"Price";

    cout<<endl;
    cout<<"   ----|";
    
    for(i = 2;i <= 31;++i)
        cout<<"----|";
    
    cout<<endl;
    
    for(i = 0;i <size;++i)
    {
        cout<<setw(2)<<i+1<<"|";
        
        
        for(j = 0;j <31;++j){
            //If the row price is less not a double digit number then the width of box == 3
            
            rowPrice<10? width = 3 : width = 2;
            
            //If the count is less than 30 display the seating info else display the price of the row
            
            j<30? cout<< setw(4) <<seats[i][j] <<"|" : cout<<setw(width)<< "$"<<rowPrice<<"|" ;
            
        }
        
        cout<<endl;
        
        rowPrice -= 2.0;
        
        cout<<" -|----";
        
        for(j = 2;j < 31;++j)
            cout<<"|----";
        
        cout<<"|----|";
        cout<<endl;
        
    }
}

void viewTicketPrices(const double ticketPrices[],int size)
{
    int i,j;
    
    cout<<"    "<<"Row";//5 space chars
    
    
    cout<<setw(8)<<"Price";
    
    cout<<endl;
    cout<<"   ----|";
    
    for(i = 2;i <= 4;++i)
        cout<<"----|";
    
    cout<<endl;
    
//    for(i = 0;i <size;++i)
//    {
//        
//        for(j = 0;j <31;++j){
//            
//            
//          
//            
//            //If the count is less than 30 display the seating info else display the price of the row
//            
//            j<30? cout<< setw(4) <<seats[i][j] <<"|" : cout<<setw(width)<< "$"<<rowPrice<<"|" ;
//            
//        }
//        
//        cout<<endl;
//        
//        rowPrice -= 2.0;
//        
//        cout<<" -|----";
//        
//        for(j = 2;j < 31;++j)
//            cout<<"|----";
//        
//        cout<<"|----|";
//        cout<<endl;
//        
//    }
}





