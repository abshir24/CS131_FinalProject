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

void purchaseTicket(char*,const double*,double*);

int numAvailableTickets(char[][30],int);

void checkAvailability(char[][30],int,int[],int[],int&);

int main()
{
    char seats[15][30];
    
    const double ticketPrices[15] = {50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
    
    double purchases[50];
    
    int purchaseArrIdx = 0;
    
    
//    retrieveSeats(seats,15);
//
//    displaySeats(seats,15);
    
//    viewTicketPrices(ticketPrices,15);
    
    

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

//This is the function that views the ticket prices for each row

void viewTicketPrices(const double ticketPrices[],int size)
{
    cout<<" "<<"Row";

    cout<<setw(8)<<"Price";
    
    cout<<endl;
    
    cout<<"|----|";
    
    cout<<"|----|";
    
    cout<<endl;
    
    for(int i = 0;i <size;++i)
    {
        cout<<"|";
        
        cout<<setw(4)<<i+1<<"|";
        
        cout<<"|";
        
        cout<<setw(2)<<"$"<<ticketPrices[i]<<"|";
        
        cout<<endl;
        
    }
    
}

//Function for purchasing ticket.

void purchaseTicket(char seats[][30],const double prices[],double purchases[],int availableTickets,int seatsSize, int &purchasesIdx)
{
    int ticketAmount;
    
    //This loop asks the user for the number of tickets that they want to purchase runs untill the user gives a valid number is between 1 and the amount of tickets available
    
    do{
        cout<<"The number of available tickets are " << availableTickets<<endl;
        
        cout<<"How many tickets would you like to purchase? (Ticket amount must be greater than 0 and less than " << availableTickets <<endl;
        
        cin>>ticketAmount;
    }while(ticketAmount < 1 || ticketAmount > availableTickets);
    
    
    //For loop runs for the number of tickets that the user wants to buy
    
    for(int i = 0;i<ticketAmount;i--)
    {
        cout<<"Select a seat for ticket#" << (ticketAmount - i)<<endl;
        
        
    }
    
}



//Function to check to see if a seat is available

void checkAvailability(char seats[][30],int seatsSize,int prices[],int purchases[],int &purchasesIdx)
{
    int row,seat;
    
    //This loop asks the user for the row of the ticket that they want to purchase runs until number is  between 1 and 15
    do
    {
        cout<<"Which row would you like to select?(Row number must be greater than 0 and less than 16)"<<endl;
        
        cin>>row;
    }while(row<1 || row>15);
    
    //This loop asks the user for the row of the ticket that they want to purchase runs until number is  between 1 and 30
    do
    {
        cout<<"Which seat would you like to select? Seat number must be greater than 0 and less than 31"<<endl;
        
        cin>>seat;
    }while(seat<1 || seat>30);
    
    if(seats[row][seat] == '#')
    {
        cout << "This seat is available. The price for this seat is $" << prices[row]<<endl;
        
        purchases[purch]
        
        
    }
}

//Function for checking the number of available tickets
int numAvailableTickets(char arr[][30],int size)
{
    int count = 0;
    
    for(int i = 0;i<size;i++)
        for(int j = 0;j<30;j++)
            //Check to see if the seat is available and increment count if it is.
            if(arr[i][j] == '#') count++;
}








