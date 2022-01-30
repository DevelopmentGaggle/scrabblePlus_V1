#include <vector>
#include <utility>
#include <iostream>
#include "Game.h"

static int pointValues[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

Game::Game(int numPlayers) {
	LogAction("Initializing game...");

	this->numPlayers = numPlayers;
	currPlayerTurn = 0;
	totalTurns = 0;
	lastScore = -1;
	board = new Tile * [BOARD_SIZE];
	prevBoard = nullptr;

	Multiplier scoreBoard[15][15] = { {TW, NN, NN, DL, NN, NN, NN, TW, NN, NN, NN, DL, NN, NN, TW},
									 {NN, DW, NN, NN, NN, TL, NN, NN, NN, TL, NN, NN, NN, DW, NN},
									 {NN, NN, DW, NN, NN, NN, DL, NN, DL, NN, NN, NN, DW, NN, NN},
									 {DL, NN, NN, DW, NN, NN, NN, DL, NN, NN, NN, DW, NN, NN, DL},
									 {NN, NN, NN, NN, DW, NN, NN, NN, NN, NN, DW, NN, NN, NN, NN},
									 {NN, TL, NN, NN, NN, TL, NN, NN, NN, TL, NN, NN, NN, TL, NN},
									 {NN, NN, DL, NN, NN, NN, DL, NN, DL, NN, NN, NN, DL, NN, NN},
									 {TW, NN, NN, DL, NN, NN, NN, DW, NN, NN, NN, DL, NN, NN, TW},
									 {NN, NN, DL, NN, NN, NN, DL, NN, DL, NN, NN, NN, DL, NN, NN},
									 {NN, TL, NN, NN, NN, TL, NN, NN, NN, TL, NN, NN, NN, TL, NN},
									 {NN, NN, NN, NN, DW, NN, NN, NN, NN, NN, DW, NN, NN, NN, NN},
									 {DL, NN, NN, DW, NN, NN, NN, DL, NN, NN, NN, DW, NN, NN, DL},
									 {NN, NN, DW, NN, NN, NN, DL, NN, DL, NN, NN, NN, DW, NN, NN},
									 {NN, DW, NN, NN, NN, TL, NN, NN, NN, TL, NN, NN, NN, DW, NN},
									 {TW, NN, NN, DL, NN, NN, NN, TW, NN, NN, NN, DL, NN, NN, TW} };

	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = new Tile[BOARD_SIZE];
		for (int j = 0; j < BOARD_SIZE; j++) {
			Tile tile;
			tile.row = i;
			tile.col = j;
			tile.multiplier = scoreBoard[i][j];
			tile.letter = '-';
			tile.isStale = true;
			tile.isBlank = false;
			board[i][j] = tile;
		}
	}

    for (int i = 0; i < 4; i++) {
		playerScores.push_back(0);
	}
}

Game::~Game() {
	delete[] board;
}

Tile** Game::GetBoard() {
	return (Tile**)board;
}

std::vector<int> Game::GetPlayerScores() {

    return playerScores;
}

int Game::GetPlayerCount() {
    return numPlayers;
}

int Game::GetTotalTurns() {
    return totalTurns;
}

void Game::PrintBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			std::cout << board[i][j].letter << " ";
		}
		std::cout << std::endl;
	}
}

int Game::CalculateWordScore(std::vector<Tile> tiles) {
	int points = 0;
	

	//First check to see if the word was inserted horizonatally or vertically
	bool isVert = true;

	//If the row numbers of two tiles are the same, then the word is horizontal
	if (tiles.size() > 1 && tiles[0].row == tiles[1].row) {
		isVert = false;
	}

    if(tiles.size() >= 7) {
        points += 50;
        LogAction("Bingo!");
    }

	int tempTotal = 0;
	int wordMult = 1;
	int rpos = tiles[0].row;
	int cpos = tiles[0].col;
	Tile* currTile = &board[rpos][cpos];

	if (tiles.size() == 1) {
		rpos = tiles[0].row;
		currTile = &board[rpos][cpos];
		if ((cpos - 1 >= 0 && board[rpos][cpos - 1].letter != '-') || (cpos + 1 < BOARD_SIZE && board[rpos][cpos + 1].letter != '-')) {
			while (currTile->letter != '-') {
				int value = 0;

				if (currTile->isBlank == false) {
					value = pointValues[currTile->letter - 'A'];
				}

				if (currTile->isStale == false) {
					if (currTile->multiplier == DL) {
						value *= 2;
					}
					else if (currTile->multiplier == TL) {
						value *= 3;
					}
					else if (currTile->multiplier == DW) {
						wordMult *= 2;
					}
					else if (currTile->multiplier == TW) {
						wordMult *= 3;
					}
				}

				tempTotal += value;
				cpos--;
				if (cpos < 0) {
					break;
				}
				currTile = &board[rpos][cpos];
			}

			cpos = tiles[0].col + 1;
			if (cpos < BOARD_SIZE) {
				currTile = &board[rpos][cpos];

				while (currTile->letter != '-') {
					int value = 0;

					if (currTile->isBlank == false) {
						value = pointValues[currTile->letter - 'A'];
					}

					if (currTile->isStale == false) {
						if (currTile->multiplier == DL) {
							value *= 2;
						}
						else if (currTile->multiplier == TL) {
							value *= 3;
						}
						else if (currTile->multiplier == DW) {
							wordMult *= 2;
						}
						else if (currTile->multiplier == TW) {
							wordMult *= 3;
						}
					}

					tempTotal += value;
					cpos++;
					if (cpos >= BOARD_SIZE) {
						break;
					}
					currTile = &board[rpos][cpos];
				}

			}
		}
		points += (tempTotal * wordMult);

		tempTotal = 0;
		wordMult = 1;
		rpos = tiles[0].row;
		cpos = tiles[0].col;
		currTile = &board[rpos][cpos];
		if ((rpos - 1 >= 0 && board[rpos - 1][cpos].letter != '-') || (rpos + 1 < BOARD_SIZE && board[rpos + 1][cpos].letter != '-')) {
			while (currTile->letter != '-') {
				int value = 0;

				if (currTile->isBlank == false) {
					value = pointValues[currTile->letter - 'A'];
				}

				if (currTile->isStale == false) {
					if (currTile->multiplier == DL) {
						value *= 2;
					}
					else if (currTile->multiplier == TL) {
						value *= 3;
					}
					else if (currTile->multiplier == DW) {
						wordMult *= 2;
					}
					else if (currTile->multiplier == TW) {
						wordMult *= 3;
					}
				}

				tempTotal += value;
				rpos--;
				if (rpos < 0) {
					break;
				}
				currTile = &board[rpos][cpos];
			}

			rpos = tiles[0].row + 1;
			if (rpos < BOARD_SIZE) {
				currTile = &board[rpos][cpos];

				while (currTile->letter != '-') {
					int value = 0;

					if (currTile->isBlank == false) {
						value = pointValues[currTile->letter - 'A'];
					}

					if (currTile->isStale == false) {
						if (currTile->multiplier == DL) {
							value *= 2;
						}
						else if (currTile->multiplier == TL) {
							value *= 3;
						}
						else if (currTile->multiplier == DW) {
							wordMult *= 2;
						}
						else if (currTile->multiplier == TW) {
							wordMult *= 3;
						}
					}

					tempTotal += value;
					rpos++;
					if (rpos >= BOARD_SIZE) {
						break;
					}
					currTile = &board[rpos][cpos];
				}

			}
			points += (tempTotal * wordMult);
		}
	}
	else if (isVert) {
		tempTotal = 0;
		wordMult = 1;
		rpos = tiles[0].row;
		cpos = tiles[0].col;
		currTile = &board[rpos][cpos];
		while (currTile->letter != '-') {
			int value = 0;

			if (currTile->isBlank == false) {
				value = pointValues[currTile->letter - 'A'];
			}

			if (currTile->isStale == false) {
				if (currTile->multiplier == DL) {
					value *= 2;
				}
				else if (currTile->multiplier == TL) {
					value *= 3;
				}
				else if (currTile->multiplier == DW) {
					wordMult *= 2;
				}
				else if (currTile->multiplier == TW) {
					wordMult *= 3;
				}
			}

			tempTotal += value;
			rpos--;
			if (rpos < 0) {
				break;
			}
			currTile = &board[rpos][cpos];
		}

		rpos = tiles[0].row + 1;

		if (rpos < BOARD_SIZE) {
			currTile = &board[rpos][cpos];

			while (currTile->letter != '-') {
				int value = 0;

				if (currTile->isBlank == false) {
					value = pointValues[currTile->letter - 'A'];
				}

				if (currTile->isStale == false) {
					if (currTile->multiplier == DL) {
						value *= 2;
					}
					else if (currTile->multiplier == TL) {
						value *= 3;
					}
					else if (currTile->multiplier == DW) {
						wordMult *= 2;
					}
					else if (currTile->multiplier == TW) {
						wordMult *= 3;
					}
				}

				tempTotal += value;
				rpos++;
				if (rpos >= BOARD_SIZE) {
					break;
				}
				currTile = &board[rpos][cpos];
			}
		}

		points += (tempTotal * wordMult);

		for (int i = 0; i < tiles.size(); i++) {
			tempTotal = 0;
			wordMult = 1;
			cpos = tiles[i].col;
			rpos = tiles[i].row;
			currTile = &board[rpos][cpos];
			if (!((cpos - 1 >= 0 && board[rpos][cpos - 1].letter != '-') || (cpos + 1 < BOARD_SIZE && board[rpos][cpos + 1].letter != '-'))) {
				continue;
			}

			while (currTile->letter != '-') {
				int value = 0;

				if (currTile->isBlank == false) {
					value = pointValues[currTile->letter - 'A'];
				}

				if (currTile->isStale == false) {
					if (currTile->multiplier == DL) {
						value *= 2;
					}
					else if (currTile->multiplier == TL) {
						value *= 3;
					}
					else if (currTile->multiplier == DW) {
						wordMult *= 2;
					}
					else if (currTile->multiplier == TW) {
						wordMult *= 3;
					}
				}

				tempTotal += value;
				cpos--;
				if (cpos < 0) {
					break;
				}
				currTile = &board[rpos][cpos];
			}

			cpos = tiles[i].col + 1;
			if (cpos < BOARD_SIZE) {
				currTile = &board[rpos][cpos];

				while (currTile->letter != '-') {
					int value = 0;

					if (currTile->isBlank == false) {
						value = pointValues[currTile->letter - 'A'];
					}

					if (currTile->isStale == false) {
						if (currTile->multiplier == DL) {
							value *= 2;
						}
						else if (currTile->multiplier == TL) {
							value *= 3;
						}
						else if (currTile->multiplier == DW) {
							wordMult *= 2;
						}
						else if (currTile->multiplier == TW) {
							wordMult *= 3;
						}
					}

					tempTotal += value;
					cpos++;
					if (cpos >= BOARD_SIZE) {
						break;
					}
					currTile = &board[rpos][cpos];
				}

			}
			points += (tempTotal * wordMult);
		}

	}
	else {
		tempTotal = 0;
		wordMult = 1;
		rpos = tiles[0].row;
		cpos = tiles[0].col;
		currTile = &board[rpos][cpos];
		while (currTile->letter != '-') {
			int value = 0;

			if (currTile->isBlank == false) {
				value = pointValues[currTile->letter - 'A'];
			}

			if (currTile->isStale == false) {
				if (currTile->multiplier == DL) {
					value *= 2;
				}
				else if (currTile->multiplier == TL) {
					value *= 3;
				}
				else if (currTile->multiplier == DW) {
					wordMult *= 2;
				}
				else if (currTile->multiplier == TW) {
					wordMult *= 3;
				}
			}

			tempTotal += value;
			cpos--;
			if (cpos < 0) {
				break;
			}
			currTile = &board[rpos][cpos];
		}

		cpos = tiles[0].col + 1;

		if (cpos < BOARD_SIZE) {
			currTile = &board[rpos][cpos];

			while (currTile->letter != '-') {
				int value = 0;

				if (currTile->isBlank == false) {
					value = pointValues[currTile->letter - 'A'];
				}

				if (currTile->isStale == false) {
					if (currTile->multiplier == DL) {
						value *= 2;
					}
					else if (currTile->multiplier == TL) {
						value *= 3;
					}
					else if (currTile->multiplier == DW) {
						wordMult *= 2;
					}
					else if (currTile->multiplier == TW) {
						wordMult *= 3;
					}
				}

				tempTotal += value;
				cpos++;
				if (cpos >= BOARD_SIZE) {
					break;
				}
				currTile = &board[rpos][cpos];
			}
		}

		points += (tempTotal * wordMult);


		for (int i = 0; i < tiles.size(); i++) {
			tempTotal = 0;
			wordMult = 1;
			rpos = tiles[i].row;
			cpos = tiles[i].col;
			currTile = &board[rpos][cpos];
			if (!((rpos - 1 >= 0 && board[rpos - 1][cpos].letter != '-') || (rpos + 1 < BOARD_SIZE && board[rpos + 1][cpos].letter != '-'))) {
				continue;
			}

			while (currTile->letter != '-') {
				int value = 0;

				if (currTile->isBlank == false) {
					value = pointValues[currTile->letter - 'A'];
				}

				if (currTile->isStale == false) {
					if (currTile->multiplier == DL) {
						value *= 2;
					}
					else if (currTile->multiplier == TL) {
						value *= 3;
					}
					else if (currTile->multiplier == DW) {
						wordMult *= 2;
					}
					else if (currTile->multiplier == TW) {
						wordMult *= 3;
					}
				}

				tempTotal += value;
				rpos--;
				if (rpos < 0) {
					break;
				}
				currTile = &board[rpos][cpos];
			}

			rpos = tiles[i].row + 1;
			if (rpos < BOARD_SIZE) {
				currTile = &board[rpos][cpos];

				while (currTile->letter != '-') {
					int value = 0;

					if (currTile->isBlank == false) {
						value = pointValues[currTile->letter - 'A'];
					}

					if (currTile->isStale == false) {
						if (currTile->multiplier == DL) {
							value *= 2;
						}
						else if (currTile->multiplier == TL) {
							value *= 3;
						}
						else if (currTile->multiplier == DW) {
							wordMult *= 2;
						}
						else if (currTile->multiplier == TW) {
							wordMult *= 3;
						}
					}

					tempTotal += value;
					rpos++;
					if (rpos >= BOARD_SIZE) {
						break;
					}
					currTile = &board[rpos][cpos];
				}

			}
			points += (tempTotal * wordMult);
		}
	}

	LogAction(std::string("Calculated word score: " + std::to_string(points)));
	return points;
}

void Game::IncreaseScore(int points) {

	lastScore = playerScores[currPlayerTurn];
	playerScores[currPlayerTurn] += points;

	std::string mess = "Player " + std::to_string(currPlayerTurn + 1);
	mess += " score is now ";
	LogAction(std::string(mess + std::to_string(playerScores[currPlayerTurn])));
}

void Game::IncrementTurn() {
	currPlayerTurn = (currPlayerTurn + 1) % numPlayers;
	std::string message = "Start player ";
    message += std::to_string(currPlayerTurn + 1);
	LogAction(message + " turn.");
}

void Game::LogAction(std::string message) {
	std::cout << message << std::endl;
}


void Game::AddTiles(std::vector<Tile> tiles) {
	LogAction("Adding tiles...");

	for (int i = 0; i < tiles.size(); i++) {
		Tile* tile = &(board[tiles[i].row][tiles[i].col]);
		tile->col = tiles[i].col;
		tile->row = tiles[i].row;
		tile->letter = tiles[i].letter;
		tile->isStale = false;
		tile->isBlank = tiles[i].isBlank;
	}

	int points = CalculateWordScore(tiles);
	IncreaseScore(points);

	for (int i = 0; i < tiles.size(); i++) {
		Tile* tile = &(board[tiles[i].row][tiles[i].col]);
		tile->isStale = true;
	}
}

void Game::UndoTurn() {
	
}

void Game::NextTurn() {
	IncrementTurn();
    totalTurns++;
}
