/**************************************************************\
Name Jonathan Smith										       \
Date: 7-31-2024											       \
Program Name: TicTacToe									  	   \
															   \
Program Discription: This program is a challange from OIT,	   \
	The challange is to create a Tic Tac Toe Game against a CPU\
	This is to display my skills and problem-solving ability   \
															   \
/**************************************************************/

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
using namespace std;

//Class Defintion
class Table
{
	private:
		char table[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };												//Table acts as the game board
		char inBuffer = '_';																							//Deturmines what character replaces a part of the table	
		bool RowCheck();																								//RowCheck checks the rows for a win condition
		bool ColCheck();																								//ColCheck checks the collumns for a win condition
		bool DiaCheck();																								//DiaCheck checks the diagonals for a win condition
		bool TieCheck();																								//TieCheck checks for a tie
		
	public:
		void PlayerTurn(bool);																							//PlayerTurn Deturmines what Letter gets input into the table
		void Display();																									//Display prints the table to the terminal
		bool PosCheck(int);																								//PosCheck checks to see if the input position is viable and replaces it if it is
		bool WinCheck();																								//WinCheck interfaces with the other win condition member functions and outputs the result
};

//Class Object Declaration
Table game1;

//Class Member Funciton Definition
void Table::PlayerTurn(bool player)																						//PlayerTurn Deturmines what Letter gets input into the table
{
	switch (player)
	{
		case true:
			inBuffer = 'X';
			break;
		case false:
			inBuffer = 'O';
			break;
	}
}

void Table::Display()																									//Display prints the table to the terminal
{
	int j=0;
	
	system ("cls");
	
	cout << "\nCPU (O)\tPlayer (X)";
	
	for (int i=0; i<3; i++)
	{
		cout << "\n\n ";
		for (int k=0; k<3; k++)
		{	cout << table[j] << "\t"; j++;	}
	}
}

bool Table::PosCheck(int pos)																							//PosCheck checks to see if the input position is viable and replaces it if it is
{
	if ((table[pos-1] - '0') == pos)
	{
		table[pos-1] = inBuffer;
		return true;
	}
	return false;
}

bool Table::RowCheck()																									//RowCheck checks the rows for a win condition
{
	for(int i=0; i<9; i+=3)
	{
		if (table[i] == table[(i+1)] && table [(i+1)] == table[(i+2)])
		{
			cout << endl << table[i] <<" Won with three in a row.";
			return true;
		}
	}
	return false;
}

bool Table::ColCheck()																									//ColCheck checks the collumns for a win condition
{
	for(int i=0; i<3; i++)
	{
		if (table[i] == table[(i+3)] && table [i] == table[(i+6)])
		{
			cout << endl << table[i] <<" Won with three in a collumn";
			return true;
		}
	}
	return false;
}

bool Table::DiaCheck()																									//DiaCheck checks the diagonals for a win condition
{
	if ((table[0] == table[4] && table[0] == table[8])  ||  (table [2] == table[4] && table[2] == table[6]))
	{
		cout << endl << table[4] <<" Won with three diagonally";
		return true;
	}
	return false;
}

bool Table::TieCheck()																									//TieCheck checks for a tie
{
	for(int i=0; i<9; i++)
	{
		if(table[i] == (i+1)+'0')
		{
			return false;
		}
	}
	cout << "\nThe game has tied.";
	return true;
}

bool Table::WinCheck()																									//WinCheck interfaces with the other win condition member functions and outputs the result
{
	bool win;
	win = RowCheck();
	if(win == true)
	{
		return win; 
	}
	else
	{
		win = ColCheck();
		if (win == false)
		{
			win = DiaCheck();
			if (win == false)
			{
				win = TieCheck();
			}
		}
	}
	return win;
}


//Function Declarations
bool OrderPrompt()																										//OrderPrompt prompts the user to deturmine who starts the game
{
	char sel = 'l';
	while (true)
	{
		cout << "Select who goes first, C for CPU and P for player:";
		cin >> sel;
		switch (sel)
		{
			case 'c':
			case 'C': return true;
			case 'p':
			case 'P': return false;
			default: 
				cout << "\nInvalid Menu Choice\n";
				system("pause");
				system("cls");
		}
	}
	
}

char Prompt()																											//Prompt prompts the user for a position to place an X
{
	int pos = 10;
	cout << "\n\nPlayer, Please select a position:";
	cin >> pos;
	return pos;
}

int CPU()																												//CPU deturmines the computer player's placement of it's O
{
	game1.PlayerTurn(false);
	int posSel = 10;
	bool availible = false;
	
	do
	{
		posSel = (rand() % 9) + 1;
		availible = game1.PosCheck(posSel);
	}while (!availible);
	
	game1.Display();
	
}

void UserTurn(bool posAvailible)
{
	while (!posAvailible)
		{
			game1.PlayerTurn(true);
			game1.Display();
			int pos = Prompt();
			posAvailible = game1.PosCheck(pos);
			
			//Warns the user that its selection was invalid
			if (!posAvailible)
			{
				cout << "\nThe position selected is not availible, Ensure you are using a number corrisponding to a position.\n";
				system ("pause");
			}
			game1.Display();
		}
}

//Main Function
int main()
{
	bool winFlag;

	//Setting a time based seed
	srand(time(0));
	
	//Sets starting order
	bool posAvailible = OrderPrompt();
	system ("cls");
	
	
	//Loops until win condition is met
	while(winFlag == false){
		
		winFlag = game1.WinCheck();

		//User's Turn
		if (winFlag == false)
		{	
			UserTurn(posAvailible);	
		}
		else
		{	break;	}
		
		//resets loop for next iteration
		posAvailible = false;
		
		
		//Checks if game ends
		winFlag = game1.WinCheck();
		
		//CPU's Turn
		if(winFlag == false)
		{
			CPU();	
		}
		else
		{	break;	}
		
	}
	cout << endl << endl;
	system("pause");
}
