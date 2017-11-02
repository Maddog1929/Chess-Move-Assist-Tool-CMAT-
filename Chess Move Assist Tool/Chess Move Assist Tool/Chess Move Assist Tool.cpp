// Chess Move Assist Tool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

class Board
{
public:
	int pieces[8][8] = {
		{ 4, 2, 3, 5, 6, 3, 2, 4 } ,
		{ 1, 1, 1, 1, 1, 1, 1, 1 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 11, 11, 11, 11, 11, 11, 11, 11 } ,
		{ 14, 12, 13, 15, 16, 13, 12, 14 } ,
	};
	
	bool whiteTurn = true;

	void move(int x, int y, int x2, int y2)
	{
		pieces[x2 - 1][y2 - 1] = pieces[x - 1][y - 1];
		pieces[x - 1][y - 1] = 0;
	}

	void endTurn()
	{
		whiteTurn = !whiteTurn;
	}
};

class Inspector
{
public:

};

class Parser {
public:
	string input;
	Board board;

	vector<int> parse(string input) //possible entries: a4,ba4,ka4,k1a4,kaa4,ka1a4,a8=q,ba8=q,O-O,O-O-O
	{ //Parser will return a packet of the following type: (Entry type, Piece, ambuigity x axis (if needed), ambuigity y axis (if needed), x axis, y axis
		

		if (input.find('x') != -1)
		{
			int pos = input.find('x');
			input.erase(pos,pos);
		}
		if (input.find('X') != -1)
		{
			int pos = input.find('X');
			input.erase(pos, pos);
		}
		
		vector<int> result;
		if (input == "O-O")
		{
			result.push_back(-1);
			result.push_back(6);
			result.push_back(7);
			result.push_back((board.whiteTurn) ? 1 : 8);
			return result;
		}
		if (input == "O-O-O")
		{
			result.push_back(-2);
			result.push_back(6);
			result.push_back(3);
			result.push_back((board.whiteTurn) ? 1 : 8);
			return result;
		}
		switch(input.length())
		{
			case(2):
				{
					result.push_back(1);
					result.push_back(1);
					input[0] = toupper(input[0]);
					int row = (int)input[0]-64;
					result.push_back(row);
					string number(1,input[1]);
					result.push_back(stoi(number));
					break;
				}
			case(3) :
				{


					
					if (convertRankChar(input[0]) != -1) {
						result.push_back(1);
						result.push_back(convertRankChar(input[0]));
						input[1] = toupper(input[1]);
						int row = (int)input[1] - 64;
						result.push_back(row);
						string number(1, input[2]);
						result.push_back(stoi(number));
						break;
					}
					else //special pawn case, looks something like ef5
					{
						result.push_back(3);
						result.push_back(1);
						input[0] = toupper(input[0]);
						int row = (int)input[0] - 64;
						result.push_back(row);

						input[1] = toupper(input[1]);
						int row2 = (int)input[1] - 64;
						result.push_back(row2);

						string number(1, input[2]);
						result.push_back(stoi(number));
					}
					break;
				}
			case(4) :
				{
					if (input.find('=') != -1)
					{
						result.push_back(5);
						result.push_back(convertRankChar(input[3]));

						int pos = input.find('=');
						input.erase(pos, pos); //erases whole rest of text?

						input[0] = toupper(input[0]);
						int row = (int)input[0] - 64;
						result.push_back(row);

						string number(1, input[1]);
						result.push_back(stoi(number));
						break;
					}


					if (isRow(input[1])) {
						result.push_back(2);
						result.push_back(convertRankChar(input[0]));
						string number(1, input[1]);
						result.push_back(stoi(number));
					}
					else
					{
						result.push_back(3);
						result.push_back(convertRankChar(input[0]));
						input[1] = toupper(input[1]);
						int row = (int)input[1] - 64;
						result.push_back(row);
					}				
					input[2] = toupper(input[2]);
					int row = (int)input[2] - 64;
					result.push_back(row);
					string number(1, input[3]);
					result.push_back(stoi(number));
					break;
				}
			case(5) :
				{
					if (input.find('=') != -1)
					{
						result.push_back(6);
						result.push_back(convertRankChar(input[4]));

						int pos = input.find('=');
						input.erase(pos, pos); //erases whole rest of text?

						input[0] = toupper(input[0]);
						int row = (int)input[0] - 64;
						result.push_back(row);

						input[1] = toupper(input[1]);
						int row2 = (int)input[1] - 64;
						result.push_back(row2);

						string number(1, input[2]);
						result.push_back(stoi(number));
						break;
					}


					result.push_back(4);
					result.push_back(convertRankChar(input[0]));
					
					input[1] = toupper(input[1]);
					int row = (int)input[1] - 64;
					result.push_back(row);
					
					string number(1, input[2]);
					result.push_back(stoi(number));

					input[3] = toupper(input[3]);
					int row2 = (int)input[3] - 64;
					result.push_back(row2);

					string number2(1, input[4]);
					result.push_back(stoi(number2));
					break;
				}
		}

		return result;
	}
	void updateBoard(Board bd)
	{
		board = bd;
	}
	int convertRankChar(char rank)
	{
		
		switch ((int)rank)
		{
		case(78) : return 2; break;
		case(66) : return 3; break;
		case(82) : return 4; break;
		case(81) : return 5; break;
		case(75) : return 6; break;
		default: return -1;
		}
	}
	bool isRow(char input)
	{
		input = toupper(input);
		if ((int)input < 65)
			return true;

		return false;
	}
};

Board board;
Parser parser;

int main()//possible entries: a4,ba4,ka4,k1a4,kaa4,ka1a4,a8=q,ba8=q,O-O,O-O-O
{
	parser.updateBoard(board);
	vector<int> main = parser.parse("a4");
	for each (int i in main)
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("ba4"); //This is a bug, thinks we are moving bishop, supposed to be pawn in B file moving to A file 4th rank 
	for each (int i in main) // switching to uppercase letters for piece rank can solve this
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("Ka4");
	for each (int i in main)
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("Kba4");
	for each (int i in main)
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("Ka1a4");
	for each (int i in main)
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("exf8=Q");
	for each (int i in main)
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("O-O");
	for each (int i in main)
	{
		cout << i << " ";
	}
	cout << endl;
	main.clear();
	main = parser.parse("O-O-O");
	for each (int i in main)
	{
		cout << i << " ";
	}
	
	system("pause");
    return 0;
}

