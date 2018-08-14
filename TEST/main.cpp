#include<string>
#include<iomanip>
#include <iostream>
#include <fstream>

using namespace std;

void retrieveSeats(char[][30],int size);

void displaySeats(char[][30],const double[],int);

void viewTicketPrices(const double[],int size);

void purchaseTicket(char[][30],const double[],int);

int numAvailableTickets(char[][30],int);

bool checkAvailability(char[][30],const double[],double[],int ticketIdx);

bool checkAvailability(char[][30],const double[],int ticketAmount);

double calculateSum(double runningTotal[],int size);

bool userVerification(char seats[][30],const double ticketPrices[], double runningTotal[], int sizeTotal);

void updateSeatsDb(char[][30],int size);

void salesReport(char[][30],const double[],int size);

void activateHome(char[][30],const double[]);




int main()
{
    
    char seats[15][30];
    
    const double ticketPrices[15] = {50,48,46,44,42,40,38,36,34,32,30,28,26,24,22};
    
    activateHome(seats,ticketPrices);
    
    return 0;
}

//Activates the home menu

void activateHome(char seats[][30],const double ticketPrices[15])
{
    int answer, size = 15;
    
    string userOut;
    
    //Retrieves seating from db and places data in seats array
    
    retrieveSeats(seats,size);
    
    
    do{
        cout<<"Please select from the following menu.(1,2,3,4)"<<endl;
        
        cout<<"1) Display Seats"<<endl;
        
        cout<<"2) View Ticket Prices"<<endl;
        
        cout<<"3) Purchase Ticket"<<endl;
        
        cout<<"4) View Sales Report"<<endl;
        
        cout<<"5) Leave application"<<endl;
        
        cin>>answer;
        
    }while(answer < 1 || answer>5);
    
    //This switch statement will take the user input and run the functions for that input accordingly
        
    switch(answer){
        case 1:
            
            displaySeats(seats,ticketPrices,size);
            
            break;
        case 2:
            
            viewTicketPrices(ticketPrices,size);
            
            break;
        case 3:
            
            purchaseTicket(seats,ticketPrices,numAvailableTickets(seats,size));
            
            break;
        
        case 4:
            salesReport(seats,ticketPrices,size);
            
            break;
            
        default:
            //If option 5 is chosen return the function. This will end the application
            return;
    }
    
    
    //Ask the user if they want to return to the home menu
    do{
        
        cout<<"Would you like to return back to the home menu?"<<endl;
        
        cin>>userOut;
        
    }while((userOut[0] != 'Y' && userOut[0] != 'y') && (userOut[0] != 'N' && userOut[0] != 'n'));
    
    
    //If they want to return to the home menu then run the activate home function again
    if(userOut[0] == 'Y' || userOut[0] == 'y')
        
        return activateHome(seats,ticketPrices);
    
}


//This function retrieves the seats from the file and places them into a 2D array
void retrieveSeats(char seats[][30],int size)
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

void displaySeats(char seats[][30],const double ticketPrices[15],int size)
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

void viewTicketPrices(const double ticketPrices[15],int size)
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

void purchaseTicket(char seats[][30],const double ticketPrices[15],int availableTickets)
{
    int ticketAmount, answer;
    
    displaySeats(seats,ticketPrices,15);
    
    double *runningTotal = nullptr;
    
    //Copy of seats array for user validation
    
    char seatsCopy[15][30];
    
    retrieveSeats(seatsCopy,15);
    
    ////////////////////////
    
    
    //This loop asks the user for the number of tickets that they want to purchase runs untill the user gives a valid number is between 1 and the amount of tickets available
    
    do{
        cout<<"The number of available tickets are " << availableTickets<<endl;
        
        
        cout<<"How many tickets would you like to purchase? (Ticket amount must be greater than 0 and less than " << availableTickets << ")"<<endl;
        
        
        cin>>ticketAmount;
        
    }while(ticketAmount < 1 || ticketAmount > availableTickets);
    
    
    //Array of prices for seats for the final total for the user
    
    
    runningTotal = new double[ticketAmount];
    
    
    //Ask user if they want to automatically pick seats or manually
    
    do{
        
        cout<<"Would you like to pick seats manually or would you like the system to pick from the available seats? (1,2) "<<endl;
        
        
        cout<<"1)Automatic "<<endl;
        
        
        cout<<"2)Manual "<<endl;
        
        
        cin>>answer;
        
    }while(answer != 1 && answer!= 2);
    
    
    //if the user selects automatically
    
    if(! --answer )
    {
        //if they are not satisfied with the seats that were chosen automatically then we will return them to the home page
        
        
        if(checkAvailability(seatsCopy,ticketPrices,ticketAmount))
            
            //If they are update the data base with the new seats
            
            updateSeatsDb(seatsCopy,15);
            
    }
    else{
        
         //If the user wants to input their tickets manually
        
        
        //For loop runs for the number of tickets that the user wants to buy
        
        for(int i = 0;i<ticketAmount;i++)
        {
            
            cout<<"Select a seat for ticket #" << (i + 1)<<endl;
            
            
            //If no seat is purchased we will ask the user if they still want to purchase the remaining amount of tickets that they selected
            
            
            if(!checkAvailability(seatsCopy,ticketPrices,runningTotal,i)){
                
                
                //return if that is the first ticket and they don't want to puchase anymore return home
                
                
                if(i == 0) return;
                
                
                string answer;
                
                
                do{
                    
                    cout<<"Would you like to purchase the remaining "<< (ticketAmount - (i+1)) << " tickets? (yes or no)"<<endl;
                    
                    
                    cin>>answer;
                    
                    
                }while((answer[0] != 'Y' && answer[0] != 'y') && (answer[0] != 'N' && answer[0] != 'n'));
                
                
                //If the user doesn't want to buy their remaining tickets then we will redirect them to the home page.
                
                if(answer[0] == 'N' || answer[0] == 'n'){
                    
                    cout<<"We will now return you to the main menu thanks for shopping with us"<<endl;
                    
                    return;
                }
                
            }
            
        }
        
        //If the user is satisfied update the data base with the newly recorded seats and return home;
        
        if(userVerification(seatsCopy,ticketPrices,runningTotal,ticketAmount))
            
            updateSeatsDb(seatsCopy, 15);
        
    }
    
    
    
}



//Function to check to see if a seat is available

bool checkAvailability(char seats[][30],const double ticketPrices[15],double runningTotal[],int ticketIdx)
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
    
    
    //If the seat is available
    if(seats[--row][--seat] == '#')
    {
        //Display seat price
        
        cout << "This seat is available. The price for this seat is $" << ticketPrices[row]<<endl;
        
        //Update the array to make the seat unavailable
        
        seats[row][seat] = 'O';

        
        //Update the index for the running total array so that we can calculate the total when the purchase is finalized.
        
        runningTotal[ticketIdx] = ticketPrices[row];
    }
    else{
        
        //If the seat is not available ask the user if they want to purchase another ticket
        
        string answer;
        
        do{
            
            cout<<"This seat is not available would like to purchase another seat in its place? (yes or no)"<<endl;
            
            
            cin>> answer;
            
        }while((answer[0] != 'Y' && answer[0] != 'y') && (answer[0] != 'N' && answer[0] != 'n'));
        
        
        //If the user answers yes then run the check availability function again
        
        if(answer[0] == 'Y' || answer[0] == 'y')
            
            checkAvailability(seats,ticketPrices,runningTotal,ticketIdx);
        
        else
            //return false to send them back to ticket purchases
            
            return false;
            
    }
    
    
    return true;
}



//Overloaded checkAvailability function this function picks seats automatically based on user row preference

bool checkAvailability(char seats[][30],const double ticketPrices[15],int ticketAmount)
{
    int row, tickets = ticketAmount;
    
    double *runningTotal = nullptr;
    
    //Array of prices for seats for the final total for the user
    
    runningTotal = new double[ticketAmount];
   
    
    //This loop asks the user for the row of the ticket that they want to purchase runs until number is  between 1 and 15
    
    do
    {
        cout<<"Which row would you like to select?(Row number must be greater than 0 and less than 16)"<<endl;
        
        cin>>row;
        
    }while(row<1 || row>15);
    
    //Decrement row to fit array  index
    
    row--;
    
    bool flag = true;
    
    
    //This while loop while the user still has tickets remaining. It will automatically select all of the tickets that are in that row that are available
    //And if those tickets are not available it will select the next available tickets
    
    while(flag)
    {
        for(int seat = 0; seat<30 ;seat++)
        {
            
            if(seats[row][seat] == '#')
            {
                
                seats[row][seat] = 'O';
                
                //Add the price of this seat to our running total for the user
                
                runningTotal[--ticketAmount] = ticketPrices[row];
                
                //if all of the tickets are selected then the while loop will break out
                
                if(!(ticketAmount)){
                    
                    flag = false;
                    
                    break;
                }
                
            }
            
            
        }
        
        // Increment the row if all of the tickets aren't chosen;
        
        row++;
     }
    
    // Return the result from the user's answer of whether or not they want the seats (True or False);
    
    return userVerification(seats,ticketPrices,runningTotal,tickets);
}



bool userVerification(char seats[][30],const double ticketPrices[15], double runningTotal[], int sizeTotal)
{
    string answer;
    
    //Displays seating chart with seats that the user just selected and their total $ amount for each seat.
    
    cout<<"Here are the seats that you just selected. They are shown as O's."<<endl;
    
    cout<<"Your total purchase for these seats came out to $"<<calculateSum(runningTotal,sizeTotal)<<endl;
    
    displaySeats(seats, ticketPrices, 15);
    
    //Ask the user if their satisfied with their seating arrangement and the price
    
    do
    {
        cout<<"Are you satisfied with your seats and the total? (Yes or No)"<<endl;
        
        cin>>answer;
        
    }while((answer[0] != 'Y' && answer[0] != 'y') && (answer[0] != 'N' && answer[0] != 'n'));
    
    //If they are satisfied return true
    
    if(answer[0] == 'Y' || answer[0] == 'y')
        
        return true;
    
    
    
    cout<<"I'm sorry we will redirect you to the homepage"<<endl;
    
    //Return false if they are not satisfied
    
    return false;

    
}


//Updates the seat data in the text file.

void updateSeatsDb(char seats[][30],int size)
{
    ofstream writeFile;
    
    writeFile.open("db.txt");
    
    for(int i = 0;i<size;i++){
        
        for(int j = 0;j<30;j++){
            
            //Convert O's back to *'s
            
            if(seats[i][j] == 'O')
                
                seats[i][j] = '*';
            
            //Write data back to file
            writeFile<<seats[i][j];
        }
        
        //Start new row
        
        writeFile<<endl;
    }
    
    writeFile.close();
    
}

//Function for checking the number of available tickets
int numAvailableTickets(char seats[][30],int size)
{
    int count = 0;
    
    for(int i = 0;i<size;i++)
        
        for(int j = 0;j<30;j++)
            
            //Check to see if the seat is available and increment count if it is.
            
            if(seats[i][j] == '#') count++;
    
    return count;
}

//Function that calculates total sales;

double calculateSales(char seats[][30],const double ticketPrices[15],int size)
{
    double totalSales = 0;
    
    for(int i = 0;i<size;i++)
        
        for(int j = 0;j<30;j++)
            
            //If the seat is sold at the row price to our total sales
            
            if(seats[i][j] == '*') totalSales += ticketPrices[i];
    
    return totalSales;
}

void salesReport(char seats[][30],const double ticketPrices[15],int size)
{
    int available = numAvailableTickets(seats,size),
            //The number of tickets sold is the amount of seats total subtracted by the number of available seats
            sold = 450 - available;
    
    double totalSales = calculateSales(seats,ticketPrices,size);
    
    cout<<"Tickets sold "<< sold <<" tickets"<<endl;
    
    cout<<"Tickets available "<< available <<" tickets"<<endl;
    
    cout<<"Total sales $"<< totalSales<<endl;
    
}


//calculates sum
double calculateSum(double runningTotal[],int size)
{
    int sum = 0;
    
    for(int i = 0;i<size;i++)
        sum+=runningTotal[i];
    
    return sum;
}







