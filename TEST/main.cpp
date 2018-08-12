#include <iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include <iostream>
#include <fstream>

using namespace std;

void retrieveSeats(int size);

void displaySeats(int size);

void viewTicketPrices(int size);

void purchaseTicket(int,int);

int numAvailableTickets(int);

bool checkAvailability(int);

void updateSeatsDb(int size);

void salesReport(int size);

void activateHome();

char seats[15][30];

const double ticketPrices[15] = {50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};


int main()
{
    activateHome();
    
    return 0;
}

//Activates the home menu

void activateHome()
{
    int answer, size = 15;
    
    //Retrieves seating from db and places data in seats array
    
    retrieveSeats(15);
    
    
    do{
        cout<<"Please select from the following menu.(1,2,3,4)"<<endl;
        
        cout<<"1) Display Seats"<<endl;
        
        cout<<"2) View Ticket Prices"<<endl;
        
        cout<<"3) Purchase Ticket"<<endl;
        
        cout<<"4) View Sales Report"<<endl;
        
        cin>>answer;
        
    }while(answer < 1 || answer>4);
        
        switch(answer){
            case 1:
                displaySeats(size);
                break;
            case 2:
                viewTicketPrices(size);
                break;
            case 3:
                purchaseTicket(size,numAvailableTickets(size));
                break;
            default:
                salesReport(size);
                break;
        }
}


//This function retrieves the seats from the file and places them into a 2D array
void retrieveSeats(int size)
{
    
    ifstream readFile;
    
    readFile.open("db.txt");
    
    char seat;
    
    int row=0,column=0;
    
    while(readFile>>seat){
        
        seats[row][column++] = seat;
        
        if(column==30){
            
            row++;
            
            column=0;
        }
        
    }
    
    readFile.close();
}

//This function takes the newly updated 2D array of seats and organizes it to chart of seats.

void displaySeats(int size)
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

void viewTicketPrices(int size)
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

void purchaseTicket(int seatsSize,int availableTickets)
{
    int ticketAmount;
    
    //This loop asks the user for the number of tickets that they want to purchase runs untill the user gives a valid number is between 1 and the amount of tickets available
    
    do{
        cout<<"The number of available tickets are " << availableTickets<<endl;
        
        cout<<"How many tickets would you like to purchase? (Ticket amount must be greater than 0 and less than " << availableTickets << ")"<<endl;
        
        cin>>ticketAmount;
        
    }while(ticketAmount < 1 || ticketAmount > availableTickets);
    
    
    //For loop runs for the number of tickets that the user wants to buy
    
    for(int i = 0;i<ticketAmount;i++)
    {
        cout<<"Select a seat for ticket#" << (i + 1)<<endl;
        
        //If no seat is purchased we will ask the user if they still want to purchase the remaining amount of tickets that they selected
        
        if(!checkAvailability(seatsSize)){
            
            //return if there are no remaining tickets
            
            if(i == 0) return ;
            
            string answer;
            
            cout<<"Would you like to purchase the remaining "<< (ticketAmount - (i+1)) << " tickets? (yes or no)"<<endl;
            
            cin>>answer;
            
            //If the user doesn't want to buy their remaining tickets then we will redirect them to the home page.
            
            if(answer[0] == 'N' || answer[0] == 'n'){
                
                cout<<"We will now return you to the main menu thanks for shopping with us"<<endl;
                
                return;
            }
            
        }
        
    }
    
}



//Function to check to see if a seat is available

bool checkAvailability(int seatsSize)
{
    int row,seat;
    
    //This loop asks the user for the row of the ticket that they want to purchase runs until number is  between 1 and 15
    do
    {
        cout<<"Which row would you like to select?(Row number must be greater than 0 and less than 16)"<<endl;
        
        cin>>row;
    }while(row<1 || row>15);
    
    //Decrement the row size to fit array index
    row--;
    
    //This loop asks the user for the row of the ticket that they want to purchase runs until number is  between 1 and 30
    do
    {
        cout<<"Which seat would you like to select? Seat number must be greater than 0 and less than 31"<<endl;
        
        cin>>seat;
    }while(seat<1 || seat>30);
    
    //Decrement the seat size to fit array index
    seat--;
    
    //If the seat is available
    if(seats[row][seat] == '#')
    {
        //Display seat price
        cout << "This seat is available. The price for this seat is $" << ticketPrices[row]<<endl;
        
        //Update the array to make the seat unavailable
        
        seats[row][seat] = '*';
        
        //Update the database
        
        updateSeatsDb(seatsSize);

    }
    else{
        //If the seat is not available ask the user if they want to purchase another ticket
        string answer;
        
        cout<<"This seat is not available would like to purchase another seat in its place? (yes or no)"<<endl;
        
        cin>> answer;
        
        //If the user answers yes then run the check availability function again
        if(answer[0] == 'Y' || answer[0] == 'y')
            
            checkAvailability(seatsSize);
        
        else
            //return false to send them back to ticket purchases
            return false;
            
    }
    
    cout<<"Congratulations seat #"<< (row+1) <<","<< (seat+1) <<" is currently yours!"<<endl;
    
    return true;
}

//Updates the seat data in the text file.

void updateSeatsDb(int size)
{
    ofstream writeFile;
    
    writeFile.open("db.txt");
    
    for(int i = 0;i<size;i++){
        
        for(int j = 0;j<30;j++)
            
            writeFile<<seats[i][j];
        
        writeFile<<endl;
    }
    
    writeFile.close();
    
}

//Function for checking the number of available tickets
int numAvailableTickets(int size)
{
    int count = 0;
    
    for(int i = 0;i<size;i++)
        
        for(int j = 0;j<30;j++)
            
            //Check to see if the seat is available and increment count if it is.
            
            if(seats[i][j] == '#') count++;
    
    return count;
}

//Function that calculates total sales;

double calculateSales(int size)
{
    double totalSales = 0;
    
    for(int i = 0;i<size;i++)
        
        for(int j = 0;j<30;j++)
            
            //If the seat is sold at the row price to our total sales
            
            if(seats[i][j] == '*') totalSales += ticketPrices[i];
    
    return totalSales;
}

void salesReport(int size)
{
    int available = numAvailableTickets(size),
            //The number of tickets sold is the amount of seats total subtracted by the number of available seats
            sold = 450 - available;
    
    double totalSales = calculateSales(size);
    
    cout<<"Tickets sold "<< sold <<" tickets"<<endl;
    
    cout<<"Tickets available "<< available <<" tickets"<<endl;
    
    cout<<"Total sales $"<< totalSales<<endl;
    
}










