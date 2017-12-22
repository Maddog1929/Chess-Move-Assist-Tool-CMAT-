// Chess Move Assist Tool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "termcolor/termcolor.hpp"
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
	};*/

	
	int pieces[8][8] = { // test board
	{ 4, 0, 0, 5, 6, 5, 0, 4 } ,
	{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
	{ 14, 0, 0, 15, 16, 15, 0, 14 } ,
	};
	bool whiteTurn = true;
	bool isUserWhite = true;
	bool canKingCastle[2] = { true,true };
	bool canQueenRookCastle[2] = { true,true };
	bool canKingRookCastle[2] = { true,true };

	//0 for white, 1 for black. Returns yes if king can castle and 1 if its king side, 2 if its queen side or 3 for both. Zero if king cannot castle or no rooks
	int canCastle(int isWhite) 
	{
		if (canKingCastle[isWhite] && (canQueenRookCastle[isWhite] || canKingRookCastle[isWhite]))
		{
			if (canKingRookCastle[isWhite] && canQueenRookCastle[isWhite])
			{
				return 3;
			}
			else if(canKingRookCastle[isWhite]){
				return 1;
			}
			else if(canQueenRookCastle[isWhite])
			{
				return 2;
			}
		}
		return 0;
	}

	bool getUserTeam()
	{
		return isUserWhite;
	}

	void move(int y, int x, int y2, int x2)
	{
		pieces[x2][y2] = pieces[x][y];
		pieces[x][y] = 0;
	}

	void change(int x, int y, int val)
	{
		if (x < 0 || x > 8)
		{
			return;
		}
		if (y < 0 || y > 8)
		{
			return;
		}
		pieces[y][x] = val;
	}

	int get(int x, int y)
	{
		if (x < 0 || x > 7)
		{
			return 0;
		}
		if (y < 0 || y > 7)
		{
			return 0;
		}
		return pieces[y][x];
	}

	vector<int> getPieces(bool whiteTeam)
	{
		vector<int> indexes;
		for (int i = 0; i < 9; i++)//i is rank
		{
			for (int g = 0; g < 9; g++)//g is file
			{
				if (pieces[i][g] != 0)
				{
					if (whiteTeam && pieces[i][g] < 10)
					{
						indexes.push_back(pieces[i][g]);
						indexes.push_back(g);
						indexes.push_back(i);
					}
					else if (!whiteTeam && pieces[i][g] > 10)
					{
						indexes.push_back(pieces[i][g]);
						indexes.push_back(g);
						indexes.push_back(i);
					}
				}
			}
		}
		return indexes;
	}

	void endTurn()
	{
		whiteTurn = !whiteTurn;
	}

	char pieceLetters[7] =
	{
		'0',
		'P',
		'N',
		'B',
		'R',
		'Q',
		'K'

	};

	void printBoard()
	{
		cout << termcolor::cyan << "  A B C D E F G H" << termcolor::reset << endl;
		if (!getUserTeam()) {
			for (int i = 0; i < 8; i++)
			{
				cout << termcolor::cyan << i + 1 << " ";
				for (int g = 0; g < 8; g++)
				{
					int piece = pieces[i][g];
					if (piece > 10)
					{
						piece = piece - 10;
						std::cout << termcolor::white << termcolor::on_grey << pieceLetters[piece] << " " << termcolor::reset;
					}
					else if (piece < 10 && piece != 0) {
						std::cout << termcolor::grey << termcolor::on_white << pieceLetters[piece] << " " << termcolor::reset;
					}
					else
					{
						std::cout << termcolor::green << termcolor::on_grey << pieceLetters[piece] << " " << termcolor::reset;
					}
				}
				cout << endl;

			}
		}
		else
		{
			for (int i = 7; i >= 0; i--)
			{
				cout << termcolor::cyan << i + 1 << " ";
				for (int g = 0; g < 8; g++)
				{
					int piece = pieces[i][g];
					if (piece > 10)
					{
						piece = piece - 10;
						std::cout << termcolor::white << termcolor::on_grey << pieceLetters[piece] << " " << termcolor::reset;
					}
					else if (piece < 10 && piece != 0) {
						std::cout << termcolor::grey << termcolor::on_white << pieceLetters[piece] << " " << termcolor::reset;
					}
					else
					{
						std::cout << termcolor::green << termcolor::on_grey << pieceLetters[piece] << " " << termcolor::reset;
					}
				}
				cout << endl;

			}
		}
		cout << termcolor::cyan << "  A B C D E F G H" << termcolor::reset << endl;
	}
};


class LegalChecker
{
public:

	Board* board;
	void updateBoard(Board* bd)
	{
		board = bd;
	}
	int runCheck(vector<int> move, vector<int>&start)
	{
		//(Move code, Piece code(not team specific), ambiguity x axis (if needed), ambiguity y axis (if needed), x axis, y axis)
		int piece = board->get(move[move.size() - 2]-1, move[move.size() - 1]-1); //we need to sub 1 from each val as it isn't done before this
		if (board->whiteTurn && piece < 10)//checking to see if we are moving onto our own piece of same color
		{
			if (piece != 0)
				return false;
		}
		if (!board->whiteTurn && piece > 10)//checking to see if we are moving onto our own piece of same color
		{
			return false;
		}
		if (move[0] == -1 || move[0] == -2)
		{
			if (!board->canCastle(!board->whiteTurn))
			{
				return 0;
			}

			if (move[0] == -1)//king is at pos 4, and rooks are at 0 and 7
			{
				if (board->canCastle(!board->whiteTurn) == 2)
				{
					return 0;
				}
				if (board->whiteTurn)
				{
					if ((board->get(5, 0) == 0) && (board->get(6, 0) == 0))
					{
						//swap pieces
						board->move(4, 0, 6, 0);
						board->move(7, 0, 5, 0);
						return 5;
					}
				}
				else
				{
					if ((board->get(5, 7) == 0) && (board->get(6, 7) == 0))
					{
						//swap pieces
						board->move(4, 7, 6, 7);
						board->move(7, 7, 5, 7);
						return 5;
					}
				}
			}
			else
			{
				if (board->canCastle(!board->whiteTurn) == 1)
				{
					return 0;
				}
				if (board->whiteTurn)
				{
					if ((board->get(3, 0) == 0) && ((board->get(2, 0) == 0) && (board->get(1, 0) == 0)))
					{
						//swap pieces
						board->move(4, 0, 2, 0);
						board->move(0, 0, 3, 0);
						return 5;
					}
				}
				else
				{
					if ((board->get(3, 7) == 0) && ((board->get(2, 7) == 0) && (board->get(1, 7) == 0)))
					{
						//swap pieces
						board->move(4, 7, 2, 7);
						board->move(0, 7, 3, 7);
						return 5;
					}
				}
			}
		}
	
		else if (move[0] != 5 && move[0] != 6)
		{
			int matchRank;
			int matchFile;
			int file;
			int rank;
			if (move[0] == 1) {
				file = move[2] - 1;
				rank = move[3] - 1;
			}
			else if (move[0] == 2 || move[0] == 3)
			{
				if (move[0] == 2)
					matchRank = move[2] - 1;
				else
					matchFile = move[2] - 1;

				file = move[3] - 1;
				rank = move[4] - 1;
			}
			else {
				matchFile = move[2] - 1;
				matchRank = move[3] - 1;
				file = move[4] - 1;
				rank = move[5] - 1;
				start.push_back(matchFile);
				start.push_back(matchRank);
				return 1;
			}
			switch (move[1])
			{
			case(6) :
			{
				int file = move[2] - 1;
				int rank = move[3] - 1;
				for (int i = 0; i < 3; i++) {
					if (board->get(file - (1 - i), rank - 1) == ((board->whiteTurn) ? 6 : 16))
					{
						start.push_back(file - (1 - i));
						start.push_back(rank - 1);
						board->canKingCastle[!board->whiteTurn]=false;
						return true;
					}
				}
				for (int i = 0; i < 3; i++) {
					if (board->get(file - (1 - i), rank + 1) == ((board->whiteTurn) ? 6 : 16))
					{
						start.push_back(file - (1 - i));
						start.push_back(rank + 1);
						board->canKingCastle[!board->whiteTurn] = false;
						return true;
					}
				}
				if (board->get(file - 1, rank) == ((board->whiteTurn) ? 6 : 16))
				{
					start.push_back(file - 1);
					start.push_back(rank);
					board->canKingCastle[!board->whiteTurn] = false;
					return true;
				}
				if (board->get(file + 1, rank) == ((board->whiteTurn) ? 6 : 16))
				{
					start.push_back(file + 1);
					start.push_back(rank);
					board->canKingCastle[!board->whiteTurn] = false;
					return true;
				}
				break;
			}
			case(5) :
			{
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
						//check for queen and if it has l.o.s to position
						if (board->get(i, rank) == ((board->whiteTurn) ? 5 : 15))
						{
							queen = true;
							queens++;
							start.push_back(i);
							start.push_back(rank);
						}
						else if (board->get(i, rank) != 0 && queen == true)
						{
							queen = false;
							queens--;
							start.pop_back();
							start.pop_back();

						}
					}
					else
					{
						if (board->get(i, rank) == ((board->whiteTurn) ? 5 : 15))
						{
							start.push_back(i);
							start.push_back(rank);
							queens++;
							break;
						}
						else if (board->get(i, rank) != 0)
						{
							break;
						}
					}
				}
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
						if (board->get(file, i) == ((board->whiteTurn) ? 5 : 15))
						{
							queen = true;
							queens++;
							start.push_back(file);
							start.push_back(i);
						}
						else if (board->get(file, i) != 0 && queen == true)
						{
							queen = false;
							queens--;
							start.pop_back();
							start.pop_back();
						}
					}
					else
					{
						if (board->get(file, i) == ((board->whiteTurn) ? 5 : 15))
						{
							start.push_back(file);
							start.push_back(i);
							queens++;
							break;
						}
						else if (board->get(file, i) != 0)
						{
							break;
						}
					}
				}
				cout << "Bottom to top done. " << queens << " queens" << endl;
				for (int i = 1; i < 9; i++)//bottom left
				{
					if (board->get(file - i, rank - i) == ((board->whiteTurn) ? 5 : 15))
					{
						start.push_back(file - i);
						start.push_back(rank - i);
						queens++;
						break;
					}
					else if (board->get(file - i, rank - i) != 0)
					{
						break;
					}
				}
				cout << "Bottom left done. " << queens << " queens" << endl;
				for (int i = 1; i < 9; i++)//bottom right
				{
					if (board->get(file + i, rank - i) == ((board->whiteTurn) ? 5 : 15))
					{
						start.push_back(file + i);
						start.push_back(rank - i);
						queens++;
						break;
					}
					else if (board->get(file + i, rank - i) != 0)
					{
						break;
					}
				}
				cout << "Bottom right done. " << queens << " queens" << endl;
				for (int i = 1; i < 9; i++)//top left
				{
					if (board->get(file - i, rank + i) == ((board->whiteTurn) ? 5 : 15))
					{
						start.push_back(file - i);
						start.push_back(rank + i);
						queens++;
						break;
					}
					else if (board->get(file - i, rank + i) != 0)
					{
						break;
					}
				}
				cout << "Top left done. " << queens << " queens" << endl;
				for (int i = 1; i < 9; i++)//top right
				{
					if (board->get(file + i, rank + i) == ((board->whiteTurn) ? 5 : 15))
					{
						start.push_back(file + i);
						start.push_back(rank + i);
						queens++;
						break;
					}
					else if (board->get(file + i, rank + i) != 0)
					{
						break;
					}
				}
				cout << "Top right done. " << queens << " queens" << endl;
				if (queens>1)
				{
					if (move[0] == 1)
						return -1;
					if (move[0] == 2)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i + 1) == matchRank)
							{
								int correctFile = start.at(i);
								start.clear();
								start.push_back(correctFile);
								start.push_back(matchRank);
								return 1;
							}
						}
					}
					if (move[0] == 3)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i) == matchFile)
							{
								int correctRank = start.at(i + 1);
								start.clear();
								start.push_back(matchFile);
								start.push_back(correctRank);
								return 1;
							}
						}
					}
				}
				else if (queens == 1)
				{
					return 1;
				}
				break;
			}
			case(4) :
			{
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
						
						if (board->get(i, rank) == ((board->whiteTurn) ? 4 : 14))
						{
							start.push_back(i);
							start.push_back(rank);
							rook = true;
							rooks++;
						}
						else if (board->get(i, rank) != 0 && rook == true)
						{
							start.pop_back();
							start.pop_back();
							rook = false;
							rooks--;

						}
					}
					else
					{
						if (board->get(i, rank) == ((board->whiteTurn) ? 4 : 14))
						{
							start.push_back(i);
							start.push_back(rank);
							rooks++;
							break;
						}
						else if (board->get(i, rank) != 0)
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
						if (board->get(file, i) == ((board->whiteTurn) ? 4 : 14))
						{
							start.push_back(file);
							start.push_back(i);
							rook = true;
							rooks++;
						}
						else if (board->get(file, i) != 0 && rook == true)
						{
							start.pop_back();
							start.pop_back();
							rook = false;
							rooks--;

						}
					}
					else
					{
						if (board->get(file, i) == ((board->whiteTurn) ? 4 : 14))
						{
							start.push_back(file);
							start.push_back(i);
							rooks++;
							break;
						}
						else if (board->get(file, i) != 0)
						{
							break;
						}
					}
				}
				cout << "Bottom to top done. " << rooks << " rooks" << endl;
				if (rooks>1)
				{
					if (move[0] == 1)
						return -1;
					if (move[0] == 2)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i + 1) == matchRank)
							{
								int correctFile = start.at(i);
								start.clear();
								start.push_back(correctFile);
								start.push_back(matchRank);
								if (start.at(0) == 0)
								{
									board->canQueenRookCastle[!board->whiteTurn] = false;
								}
								if (start.at(0) == 7)
								{
									board->canKingRookCastle[!board->whiteTurn] = false;
								}
								return 1;
							}
						}
					}
					if (move[0] == 3)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i) == matchFile)
							{
								int correctRank = start.at(i + 1);
								start.clear();
								start.push_back(matchFile);
								start.push_back(correctRank);
								if (start.at(0) == 0)
								{
									board->canQueenRookCastle[!board->whiteTurn] = false;
								}
								if (start.at(0) == 7)
								{
									board->canKingRookCastle[!board->whiteTurn] = false;
								}
								return 1;
							}
						}
					}
				}
				else if (rooks == 1)
				{
					if (start.at(0) == 0)
					{
						board->canQueenRookCastle[!board->whiteTurn] = false;
					}
					if (start.at(0) == 7)
					{
						board->canKingRookCastle[!board->whiteTurn] = false;
					}
					return 1;
				}
				break;
			}
			case(3) :
			{
				int bishop = false;
				int block = false;
				int bishops = 0;
				cout << "Looking for bishops" << endl;
				for (int i = 1; i < 9; i++)//bottom left
				{
					if (board->get(file - i, rank - i) == ((board->whiteTurn) ? 3 : 13))
					{
						start.push_back(file - i);
						start.push_back(rank - i);
						bishops++;
						break;
					}
					else if (board->get(file - i, rank - i) != 0)
					{
						break;
					}
				}
				cout << "Bottom left done. " << bishops << " bishops" << endl;
				for (int i = 1; i < 9; i++)//bottom right
				{
					if (board->get(file + i, rank - i) == ((board->whiteTurn) ? 3 : 13))
					{
						start.push_back(file + i);
						start.push_back(rank - i);
						bishops++;
						break;
					}
					else if (board->get(file + i, rank - i) != 0)
					{
						break;
					}
				}
				cout << "Bottom right done. " << bishops << " bishops" << endl;
				for (int i = 1; i < 9; i++)//top left
				{
					if (board->get(file - i, rank + i) == ((board->whiteTurn) ? 3 : 13))
					{
						start.push_back(file - i);
						start.push_back(rank + i);
						bishops++;
						break;
					}
					else if (board->get(file - i, rank + i) != 0)
					{
						break;
					}
				}
				cout << "Top left done. " << bishops << " bishops" << endl;
				for (int i = 1; i < 9; i++)//top right
				{
					if (board->get(file + i, rank + i) == ((board->whiteTurn) ? 3 : 13))
					{
						start.push_back(file + i);
						start.push_back(rank + i);
						bishops++;
						break;
					}
					else if (board->get(file + i, rank + i) != 0)
					{
						break;
					}
				}
				cout << "Top right done. " << bishops << " bishops" << endl;
				if (bishops>1)
				{
					if (move[0] == 1)
						return -1;
					if (move[0] == 2)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i + 1) == matchRank)
							{
								int correctFile = start.at(i);
								start.clear();
								start.push_back(correctFile);
								start.push_back(matchRank);
								return 1;
							}
						}
					}
					if (move[0] == 3)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i) == matchFile)
							{
								int correctRank = start.at(i + 1);
								start.clear();
								start.push_back(matchFile);
								start.push_back(correctRank);
								return 1;
							}
						}
					}
				}
				else if (bishops == 1)
				{
					return 1;
				}
				break;
			}
			case(2) :
			{
				int knights = 0;
				cout << "Looking for knights" << endl;
				if (board->get(file + 2, rank - 1) == ((board->whiteTurn) ? 2 : 12))// top left
				{
					start.push_back(file + 2);
					start.push_back(rank - 1);
					knights++;
				}
				if (board->get(file + 2, rank + 1) == ((board->whiteTurn) ? 2 : 12))// top right
				{
					start.push_back(file + 2);
					start.push_back(rank + 1);
					knights++;
				}
				if (board->get(file - 2, rank - 1) == ((board->whiteTurn) ? 2 : 12))// bottom left
				{
					start.push_back(file - 2);
					start.push_back(rank - 1);
					knights++;
				}
				if (board->get(file - 2, rank + 1) == ((board->whiteTurn) ? 2 : 12))// bottom right
				{
					start.push_back(file - 2);
					start.push_back(rank - 1);
					knights++;
				}
				if (board->get(file + 1, rank - 2) == ((board->whiteTurn) ? 2 : 12))// left top
				{
					start.push_back(file + 1);
					start.push_back(rank - 2);
					knights++;
				}
				if (board->get(file - 1, rank - 2) == ((board->whiteTurn) ? 2 : 12))// left bottom
				{
					start.push_back(file - 1);
					start.push_back(rank - 2);
					knights++;
				}
				if (board->get(file + 1, rank + 2) == ((board->whiteTurn) ? 2 : 12))// right top
				{
					start.push_back(file + 1);
					start.push_back(rank + 2);
					knights++;
				}
				if (board->get(file - 1, rank + 2) == ((board->whiteTurn) ? 2 : 12))// right bottom
				{
					start.push_back(file - 1);
					start.push_back(rank + 2);
					knights++;
				}
				cout << knights << " knights found" << endl;
				if (knights>1)
				{
					if (move[0] == 1)
						return -1;
					if (move[0] == 2)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i + 1) == matchRank)
							{
								int correctFile = start.at(i);
								start.clear();
								start.push_back(correctFile);
								start.push_back(matchRank);
								return 1;
							}
						}
					}
					if (move[0] == 3)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i) == matchFile)
							{
								int correctRank = start.at(i + 1);
								start.clear();
								start.push_back(matchFile);
								start.push_back(correctRank);
								return 1;
							}
						}
					}
				}
				else if (knights == 1)
				{
					return 1;
				}
				break;
			}
			case(1) :
			{
				int pawns = 0;
				bool iscap = false;
				if (board->get(file, rank) != 0)
				{
					iscap = true;
				}
				cout << "Looking for pawns" << endl;
				if (board->whiteTurn)
				{
					if (!iscap) {
						if (board->get(file, rank - 1) == 1)
						{
							start.push_back(file);
							start.push_back(rank - 1);
							pawns++;
						}
						if (board->get(file, rank - 2) == 1 && rank == 3)
						{
							start.push_back(file);
							start.push_back(rank - 2);
							pawns++;
						}
					}
					if (iscap) {
						if (board->get(file + 1, rank - 1) == 1)
						{
							start.push_back(file + 1);
							start.push_back(rank - 1);
							pawns++;
						}
						if (board->get(file - 1, rank - 1) == 1)
						{
							start.push_back(file - 1);
							start.push_back(rank - 1);
							pawns++;
						}
					}
				}
				else
				{
					if (!iscap) {
						if (board->get(file, rank + 1) == 11)
						{
							start.push_back(file);
							start.push_back(rank + 1);
							pawns++;
						}
						if (board->get(file, rank + 2) == 11 && rank == 4)
						{
							start.push_back(file);
							start.push_back(rank + 2);
							pawns++;
						}
					}
					if (iscap) {
						if (board->get(file + 1, rank + 1) == 11)
						{
							start.push_back(file + 1);
							start.push_back(rank + 1);
							pawns++;
						}
						if (board->get(file - 1, rank + 1) == 11)
						{
							start.push_back(file - 1);
							start.push_back(rank + 1);
							pawns++;
						}
					}
				}
				cout << pawns << " pawns found" << endl;

				if (pawns>1)
				{
					if (move[0] == 1)
						return -1;
					if (move[0] == 2)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i + 1) == matchRank)
							{
								int correctFile = start.at(i);
								start.clear();
								start.push_back(correctFile);
								start.push_back(matchRank);
								if (board->whiteTurn)
								{
									if (start.at(1) > rank)
									{
										return 0;
									}
								}
								if (!board->whiteTurn)
								{
									if (start.at(1) < rank)
									{
										return 0;
									}
								}
								return 1;
							}
						}
					}
					if (move[0] == 3)
					{
						for (int i = 0; i < start.size(); i = i + 2)
						{
							if (start.at(i) == matchFile)
							{
								int correctRank = start.at(i + 1);
								start.clear();
								start.push_back(matchFile);
								start.push_back(correctRank);
								if (board->whiteTurn)
								{
									if (start.at(1) > rank)
									{
										return 0;
									}
								}
								if (!board->whiteTurn)
								{
									if (start.at(1) < rank)
									{
										return 0;
									}
								}
								return 1;
							}
						}
					}
				}
				else if (pawns == 1)
				{
					if (board->whiteTurn)
					{
						if (start.at(1) > rank)
						{
							return 0;
						}
					}
					if (!board->whiteTurn)
					{
						if (start.at(1) < rank)
						{
							return 0;
						}
					}
					return 1;
				}
				break;

			}
			}

		}

		if (move[0] == 5 || move[0] == 6)
		{
			int matchFile = 0;
			int file;
			int rank;
			if (move[0] == 5) {
				file = move[2] - 1;
				rank = move[3] - 1;
			}
			if (move[0] == 6) {
				matchFile = move[2] - 1;
				file = move[3] - 1;
				rank = move[4] - 1;
			}


			int pawns = 0;
			bool iscap = false;
			if (board->get(file, rank) != 0)
			{
				iscap = true;
			}
			cout << "Looking for pawns" << endl;
			if (board->whiteTurn)
			{
				if (!iscap) {
					if (board->get(file, rank - 1) == 1)
					{
						start.push_back(file);
						start.push_back(rank - 1);
						pawns++;
					}
					if (board->get(file, rank - 2) == 1 && rank == 3)
					{
						start.push_back(file);
						start.push_back(rank - 2);
						pawns++;
					}
				}
				if (iscap) {
					if (board->get(file + 1, rank - 1) == 1)
					{
						start.push_back(file + 1);
						start.push_back(rank - 1);
						pawns++;
					}
					if (board->get(file - 1, rank - 1) == 1)
					{
						start.push_back(file - 1);
						start.push_back(rank - 1);
						pawns++;
					}
				}
			}
			else
			{
				if (!iscap) {
					if (board->get(file, rank + 1) == 11)
					{
						start.push_back(file);
						start.push_back(rank + 1);
						pawns++;
					}
					if (board->get(file, rank + 2) == 11 && rank == 4)
					{
						start.push_back(file);
						start.push_back(rank + 2);
						pawns++;
					}
				}
				if (iscap) {
					if (board->get(file + 1, rank + 1) == 11)
					{
						start.push_back(file + 1);
						start.push_back(rank + 1);
						pawns++;
					}
					if (board->get(file - 1, rank + 1) == 11)
					{
						start.push_back(file - 1);
						start.push_back(rank + 1);
						pawns++;
					}
				}
			}
			cout << pawns << " pawns found" << endl;

			if (pawns > 1)
			{
				if (move[0] == 5)
					return -1;
				if (move[0] == 6)
				{
					for (int i = 0; i < start.size(); i = i + 2)
					{
						if (start.at(i) == matchFile)
						{
							int correctRank = start.at(i+1);
							start.clear();
							start.push_back(matchFile);
							start.push_back(correctRank);
							if (board->whiteTurn)//last minute check for moving a pawn backwards
							{
								if (start.at(1) > rank)
								{
									return 0;
								}
							}
							if (!board->whiteTurn)
							{
								if (start.at(1) < rank)
								{
									return 0;
								}
							}

							return 1;
						}
					}
				}
			}
			else
			{//we are going to change the piece via the reference we have to the board class, we cant do this via function because 
			//we would only have a copy of the board class in this instance
				if (board->whiteTurn) //last minute check for moving a pawn backwards
				{
					if (start.at(1) > rank)
					{
						return 0;
					}
				}
				if (!board->whiteTurn)
				{
					if (start.at(1) < rank)
					{
						return 0;
					}
				}


;				if (board->whiteTurn == false)
				{
					board->change(start.at(0), start.at(1), move.at(1)+10); // make piece black if its supposed to be
				}else
				{
					board->change(start.at(0), start.at(1), move.at(1));
				}
				return true;
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
			input.erase(pos, pos);
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
		switch (input.length())
		{
		case(2) :
		{
			result.push_back(1);
			result.push_back(1);
			input[0] = toupper(input[0]);
			int row = (int)input[0] - 64;
			result.push_back(row);
			string number(1, input[1]);
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
LegalChecker inspector;

int main()//possible entries: a4,ba4,ka4,k1a4,kaa4,ka1a4,a8=q,ba8=q,O-O,O-O-O
{/*move codes:
 -2 castle queen side.
 -1 castle king side.
 1 regular move (piece/file/rank).
 2 ambitious move, specify rank (piece/origin rank/file/rank).
 3 ambitious move, specify file (piece/origin file/file/rank).
 4 ambitious move, specify both (piece/origin file/origin rank/file/rank)
 5 pawn rank-up (upgraded piece/file/rank)
 6 ambitious pawn rank-up, specify file (upgraded piece/file/file/rank)
 */
	while (true) {
		//todo, add support for actual analysis
		cout << "Are you on white team? y/n ";
		char ans;
		cin >> ans;
		if (ans == 'y')
		{
			board.isUserWhite = true;
			break;
		}
		else if (ans == 'n')
		{
			board.isUserWhite = false;
			break;
		}
	}
	while (true) {
		system("cls");
		while (true) {
			board.printBoard();
			cout << "Enter" << (board.whiteTurn ? " white " : " black ") << "turn: ";
			string ans;
			cin >> ans;
			parser.updateBoard(board);
			vector<int> processedMove = parser.parse(ans);
			vector<int> intendedPiece;
			inspector.updateBoard(&board);
			int response = inspector.runCheck(processedMove, intendedPiece);
			if (response == 0)
			{
				cout << "Illegal move, try again" << endl;
				system("pause");
			}
			if (response == -1)
			{
				cout << "Move is ambiguous, please specify" << endl;
				system("pause");
			}
			if (response == 1)
			{
				int x = intendedPiece.at(0);
				int y = intendedPiece.at(1);
				int x2 = processedMove.at(processedMove.size() - 2) - 1;
				int y2 = processedMove.at(processedMove.size() - 1) - 1;
				board.move(x, y, x2, y2);
				break;

			}
			if (response == 5)
			{
				//we don't do anything because castling was handled inside the runCheck function
				break;

			}
		}
		//system("cls");
		//system("pause");
		board.printBoard();
		board.endTurn();

	}
	system("pause");
	return 0;
}
