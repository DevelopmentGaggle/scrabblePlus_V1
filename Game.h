#pragma once
#include <vector>
#include <utility>
#include <string>

#define BOARD_SIZE 15

enum Multiplier {
	DL, TL, DW, TW, NN = -1
};

struct Tile {
	int row;
	int col;
	char letter;
	Multiplier multiplier;
	bool isStale;
	bool isBlank;
};

class Game {
private:
	//A 2D array of chars that represents the game(board) state AFTER the word is played
	//and any 'BLANK' tiles are interpreted.Empty spaces are represented by a '-' and
	//all letters are in upper case.
	Tile** board;
	Tile** prevBoard;
	int numPlayers;
	int currPlayerTurn;
	int totalTurns;
	int lastScore;
    std::vector<int> playerScores;


	/*	Calculates the total score gained for the turn player's word including letter multipliers,
		word multiplyers, and bingo (all 7 tiles played).

		@param tiles: Vector of tiles that store the row and column and letter of the tile.
		@return An int that represents the score to add to the turn player's score.
   */
	int CalculateWordScore(std::vector<Tile> tiles);

	/*	Increases the turn player's score.
		@param points: Point value to increase score by.
	*/
	void IncreaseScore(int points);

	/*	Sets the turn counter to the next player.
	*/
	void IncrementTurn();

	/*	Writes a message to the turn log.
		@param message: The message to log.
	*/
	void LogAction(std::string message);


public:
	//Constructor
	Game(int numPlayers);

	//Destructor
	~Game();

	//Returns the board
	Tile** GetBoard();

    //Returns the scores
    std::vector<int> GetPlayerScores();

    int GetTotalTurns();

    //Returns the player count
    int GetPlayerCount();

	//Prints letters on board to standard output
	void PrintBoard();

	/*	Adds the new tiles to game board. Calculates and updates the turn player's score.
		@param tiles: Vector of tiles that store the row and column and letter of the tile.
	*/
	void AddTiles(std::vector<Tile> tiles);

	/*	Reverts the player score, turn counter, and board to what they were before the last turn.
	*/
	void UndoTurn();

	/*	Proceeds to the next player's turn.
	*/
	void NextTurn();
};
