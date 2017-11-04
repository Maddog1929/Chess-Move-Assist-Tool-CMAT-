// Chess Move Assist Tool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

class Board
{
public:
	/*int pieces[8][8] = {
		{ 4, 2, 3, 5, 6, 3, 2, 4 } ,
		{ 1, 1, 1, 1, 1, 1, 1, 1 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 11, 11, 11, 11, 11, 11, 11, 11 } ,
		{ 14, 12, 13, 15, 16, 13, 12, 14 } ,
	};
	*/

	int pieces[8][8] = { // test board
		{ 1, 1, 1, 0, 0, 0, 0, 0 } ,
		{ 0, 11, 0, 0, 0, 0, 0, 0 } ,
		{11, 11, 11, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	};
	bool whiteTurn = true;

	void move(int y, int x, int y2, int x2)
	{
		pieces[x2 - 1][y2 - 1] = pieces[x - 1][y - 1];
		pieces[x - 1][y - 1] = 0;
	}

	int get(int x, int y)
	{
		if( x < 0 || x > 8)
		{
			return 0;
		}
		if ( y < 0 || y > 8)
		{
			return 0;
		}
		return pieces[y][x];
	}

	void endTurn()
	{
		whiteTurn = !whiteTurn;
	}
};

class Inspector
{
public:
	Board board;
	void updateBoard(Board bd)
	{
		board = bd;
	}
	int isLegal(vector<int> move)
	{
		if (move[0] == 1)
		{
			switch (move[1])
			{
			case(6) : return false; break;
			case(5) :
				{
					int file = move[2]-1;
					int rank = move[3]-1;
					int queen = false;
					int block = false;
					int queens = 0;
					cout << "Looking for queens" << endl;
					for (int i = 0; i < 9; i++) //left to right check
					{
						if (i == file)
						{
							queen = false;
							continue;
						}
						if (i < file) 
						{
							//check for queen and if it has l.o.s to posistion
							if (board.get(i, rank) == ((board.whiteTurn) ? 5 : 15))
							{
								queen = true;
								queens++;
							}
							else if (board.get(i, rank) != 0 && queen == true)
							{
								queen == false;
								queens--;
							
							}
						}
						else
						{
							if (board.get(i, rank) == ((board.whiteTurn) ? 5 : 15))
							{
								queens++;
								break;
							}
							else if (board.get(i, rank) != 0)
							{
								break;
							}
						}
					}//left to right check
					cout << "Left to right done. " << queens << " queens" << endl;
					for (int i = 0; i < 9; i++) //bottom to top check
					{
						if (i == rank)
						{
							queen = false;
							continue;
						}
						if (i < rank)
						{
							//check for queen and if it has l.o.s to posistion
							if (board.get(file, i) == ((board.whiteTurn) ? 5 : 15))
							{
								queen = true;
								queens++;
							}
							else if (board.get(file, i) != 0 && queen == true)
							{
								queen == false;
								queens--;

							}
						}
						else
						{
							if (board.get(file, i) == ((board.whiteTurn) ? 5 : 15))
							{
								queens++;
								break;
							}
							else if (board.get(file, i) != 0)
							{
								break;
							}
						}
					}
					cout << "Bottom to top done. " << queens << " queens" << endl;
					for (int i = 1; i < 9; i++)//bottom left
					{
						if (board.get(file-i, rank-i) == ((board.whiteTurn) ? 5 : 15))
						{
							queens++;
							break;
						}
						else if (board.get(file-i, rank-i) != 0)
						{
							queens++;
							break;
						}
					}
					cout << "Bottom left done. " << queens << " queens" << endl;
					for (int i = 1; i < 9; i++)//bottom right
					{
						if (board.get(file + i, rank - i) == ((board.whiteTurn) ? 5 : 15))
						{
							queens++;
							break;
						}
						else if (board.get(file+i, rank-i) != 0)
						{
							break;
						}
					}
					cout << "Bottom right done. " << queens << " queens" << endl;
					for (int i = 1; i < 9; i++)//top left
					{
						if (board.get(file - i, rank + i) == ((board.whiteTurn) ? 5 : 15))
						{
							queens++;
							break;
						}
						else if (board.get(file - i, rank + i) != 0)
						{
							break;
						}
					}
					cout << "Top left done. " << queens << " queens" << endl;
					for (int i = 1; i < 9; i++)//top right
					{
						if (board.get(file + i, rank + i) == ((board.whiteTurn) ? 5 : 15))
						{
							queens++;
							break;
						}
						else if (board.get(file + i, rank + i) != 0)
						{
							break;
						}
					}
					cout << "Top right done. " << queens << " queens" << endl;
					if(queens>1)
					{
						return -1;
					}
					else if (queens == 1)
					{
						return 1;
					}
					break;
				}
			case(4) :
				{
					int file = move[2] - 1;
					int rank = move[3] - 1;
					int rook = false;
					int block = false;
					int rooks = 0;
					cout << "Looking for rooks" << endl;
					for (int i = 0; i < 9; i++) //left to right check
					{
						if (i == file)
						{
							rook = false;
							continue;
						}
						if (i < file)
						{
							//check for queen and if it has l.o.s to posistion
							if (board.get(i, rank) == ((board.whiteTurn) ? 4 : 14))
							{
								rook = true;
								rooks++;
							}
							else if (board.get(i, rank) != 0 && rook == true)
							{
								rook == false;
								rooks--;

							}
						}
						else
						{
							if (board.get(i, rank) == ((board.whiteTurn) ? 4 : 14))
							{
								rooks++;
								break;
							}
							else if (board.get(i, rank) != 0)
							{
								break;
							}
						}
					}//left to right check
					cout << "Left to right done. " << rooks << " rooks" << endl;
					for (int i = 0; i < 9; i++) //bottom to top check
					{
						if (i == rank)
						{
							rook = false;
							continue;
						}
						if (i < rank)
						{
							//check for queen and if it has l.o.s to posistion
							if (board.get(file, i) == ((board.whiteTurn) ? 4 : 14))
							{
								rook = true;
								rooks++;
							}
							else if (board.get(file, i) != 0 && rook == true)
							{
								rook == false;
								rooks--;

							}
						}
						else
						{
							if (board.get(file, i) == ((board.whiteTurn) ? 4 : 14))
							{
								rooks++;
								break;
							}
							else if (board.get(file, i) != 0)
							{
								break;
							}
						}
					}
					cout << "Bottom to top done. " << rooks << " rooks" << endl;
					if (rooks>1)
					{
						return -1;
					}
					else if (rooks == 1)
					{
						return 1;
					}
					break;
				}
			case(3) :
			{
				int file = move[2] - 1;
				int rank = move[3] - 1;
				int bishop = false;
				int block = false;
				int bishops = 0;
				cout << "Looking for bishops" << endl;
				for (int i = 1; i < 9; i++)//bottom left
				{
					if (board.get(file - i, rank - i) == ((board.whiteTurn) ? 3 : 13))
					{
						bishops++;
						break;
					}
					else if (board.get(file - i, rank - i) != 0)
					{
						bishops++;
						break;
					}
				}
				cout << "Bottom left done. " << bishops << " bishops" << endl;
				for (int i = 1; i < 9; i++)//bottom right
				{
					if (board.get(file + i, rank - i) == ((board.whiteTurn) ? 3 : 13))
					{
						bishops++;
						break;
					}
					else if (board.get(file + i, rank - i) != 0)
					{
						break;
					}
				}
				cout << "Bottom right done. " << bishops << " bishops" << endl;
				for (int i = 1; i < 9; i++)//top left
				{
					if (board.get(file - i, rank + i) == ((board.whiteTurn) ? 3 : 13))
					{
						bishops++;
						break;
					}
					else if (board.get(file - i, rank + i) != 0)
					{
						break;
					}
				}
				cout << "Top left done. " << bishops << " bishops" << endl;
				for (int i = 1; i < 9; i++)//top right
				{
					if (board.get(file + i, rank + i) == ((board.whiteTurn) ? 3 : 13))
					{
						bishops++;
						break;
					}
					else if (board.get(file + i, rank + i) != 0)
					{
						break;
					}
				}
				cout << "Top right done. " << bishops << " bishops" << endl;
				if (bishops>1)
				{
					return -1;
				}
				else if (bishops == 1)
				{
					return 1;
				}
				break;
			}
			case(2) :
			{
				int file = move[2] - 1;
				int rank = move[3] - 1;
				int knights = 0;
				cout << "Looking for knights" << endl;
				if (board.get(file + 2, rank - 1) == ((board.whiteTurn) ? 2:12 ))// top left
				{
					knights++;
				}
				if (board.get(file + 2, rank + 1) == ((board.whiteTurn) ? 2 : 12))// top right
				{
					knights++;
				}
				if (board.get(file - 2, rank - 1) == ((board.whiteTurn) ? 2 : 12))// bottom left
				{
					knights++;
				}
				if (board.get(file - 2, rank + 1) == ((board.whiteTurn) ? 2 : 12))// bottom right
				{
					knights++;
				}
				if (board.get(file + 1, rank - 2) == ((board.whiteTurn) ? 2 : 12))// left top
				{
					knights++;
				}
				if (board.get(file - 1, rank - 2) == ((board.whiteTurn) ? 2 : 12))// left bottom
				{
					knights++;
				}
				if (board.get(file + 1, rank + 2) == ((board.whiteTurn) ? 2 : 12))// right top
				{
					knights++;
				}
				if (board.get(file - 1, rank + 2) == ((board.whiteTurn) ? 2 : 12))// right bottom
				{
					knights++;
				}
				cout << knights << " knights found" << endl;
				if (knights>1)
				{
					return -1;
				}
				else if (knights == 1)
				{
					return 1;
				}
				break;
			}
			case(1) :
			{
				int file = move[2] - 1;
				int rank = move[3] - 1;
				int pawns = 0;
				cout << "Looking for pawns" << endl;
				if (board.whiteTurn)
				{
					if (board.get(file, rank - 1) == 1)
					{
						pawns++;
					}
					if (board.get(file + 1, rank - 1) == 1)
					{
						pawns++;
					}
					if (board.get(file - 1, rank - 1) == 1)
					{
						pawns++;
					}
				}
				else
				{
					if (board.get(file, rank + 1) == 11)
					{
						pawns++;
					}
					if (board.get(file + 1, rank + 1) == 11)
					{
						pawns++;
					}
					if (board.get(file - 1, rank + 1) == 11)
					{
						pawns++;
					}
				}
				cout << pawns << " pawns found" << endl;

				if (pawns>1)
				{
					return -1;
				}
				else if (pawns == 1)
				{
					return 1;
				}
				break;

			}
			}
			
		}
		
		
		
		return false;
		
	}

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

					if (convertRankChar(input[0]) == -1)
					{
						result.push_back(4);
						result.push_back(1);

						input[0] = toupper(input[0]);
						int row = (int)input[0] - 64;
						result.push_back(row);

						string number(1, input[1]);
						result.push_back(stoi(number));

						input[2] = toupper(input[2]);
						int row2 = (int)input[2] - 64;
						result.push_back(row2);

						string number2(1, input[3]);
						result.push_back(stoi(number2));
						break;

					}

					if (isRank(input[1])) {
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
	bool isRank(char input)
	{
		input = toupper(input);
		if ((int)input < 65)
			return true;

		return false;
	}
};

Board board;
Parser parser;
Inspector inspector;

int main()//possible entries: a4,ba4,ka4,k1a4,kaa4,ka1a4,a8=q,ba8=q,O-O,O-O-O
 {/*move codes: 
  -2 castle queenside. 
  -1 castle kingside. 
  1 regular move (piece/file/rank). 
  2 ambigious move, specify rank (piece/origin rank/file/rank). 
  3 ambigious move, specify file (piece/origin file/file/rank). 
  4 ambigious move, specify both (piece/origin file/origin rank/file/rank)
  5 pawn rank-up (upgraded piece/file/rank)
  6 ambigious pawn rank-up, specify file (upgraded piece/file/file/rank)
  */
	board.endTurn();
	parser.updateBoard(board);
	vector<int> processedMove = parser.parse("b2");
	inspector.updateBoard(board);
	cout << inspector.isLegal(processedMove) << endl;
	board.endTurn();
	
	system("pause");
    return 0;
}

