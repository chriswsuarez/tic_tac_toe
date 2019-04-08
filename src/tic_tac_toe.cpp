
///////////////////////////////////////////////////////////////////////////////
//      Title     : tic_tac_toe.h
//      Project   : tic_tac_toe
//      Created   : 4/5/2019
//      Author    : Chris Suarez
//      Platforms : Ubuntu 64-bit
///////////////////////////////////////////////////////////////////////////////

#include "tic_tac_toe.h"

Game::Game() {
	this->menu();
}

// Method to initalize all game variables and clear board
void Game::init() {
	// Initialize variables
	game_over_ = false;
	num_players = -1;
	current_player_ = 1;
	turn_count_ = 0;
	result_ = -1;

	// Initialize board to zeros noting no moves have been made
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j){
			board_[i][j] = 0;
		}
	}

	std::cout << std::endl << "----------" << std::endl << "Begin Game!" << std::endl << "----------" << std::endl;

	// Input number of user controlled players
	while (num_players < 0 || num_players > 2) {
		std::cout << "Please enter a number of players (0-2):  ";
		std::cin >> num_players;
	}

	// Allowing users to set whatever character they want to play with.
	// If the input more than 1 character then we use then dummy_str to grab only the first char
	char dummy_str[140];
	for (int i=0; i<num_players; ++i) {
		std::cout << "Player " << i+1 << " please enter the character to place on the board for your move:  ";
		std::cin >> dummy_str;
		syms_[i] = dummy_str[0];
	}
}

void Game::menu() {
	int menu_val = 0;
	std::cout << "--- MENU ---" << std::endl;
	std::cout << "1. How to play" << std::endl;
	std::cout << "2. Start new game" << std::endl;
	std::cout << "3. Exit Program" << std::endl;
	std::cout << "4. Super secret mode" << std::endl;
	std::cout << "Enter your choice here: ";

	while (menu_val < 1 || menu_val > 4) {
		std::cin >> menu_val;
		if (menu_val == 1) {
			// TODO
			std::cout << "Sorry instructions are coming soon! Please enter a valid *different* option from the menu: ";
			menu_val = 0;
		} else if (menu_val == 2) {
			this->init();
			this->runGame();
		} else if (menu_val == 3) {
			exit(0);
		} else if (menu_val == 4) {
			// TODO
			std::cout << "Sorry super secret Ultimate mode is coming soon! Please enter a valid *different* option from the menu: ";
			menu_val = 0;			
		} else {
			std::cout << "Please enter a valid option from the menu: ";
		}
	}
}

void Game::runGame() {
	// Run game
	while (true) {
		
		if (num_players > 0) {
			this->userInput();
			this->turnManager();
			this->printBoard();
			result_ = this->analyzeBoard();
		}

		if (game_over_) {
			this->gameResult();
			this->menu();
		}

		if (num_players < 2) {
			this->cpuMove();
			result_ = this->analyzeBoard();
		}

		if (game_over_) {
			this->gameResult();
			this->menu();
		}
	}
}


// This method is designed to keep track of whose turn it is and count how many total turns have been taken.
inline void Game::turnManager() {
	if (current_player_ == 1) {
		current_player_ = 2;
	} else if (current_player_ == 2) {
		current_player_ = 1;
	}
	turn_count_++;
}

// User Input requests the user to input their next selection and makes the move.
void Game::userInput() {
	int cell = 0;
	while (cell < 1 || cell > 9) {
		std::cout << "Player " << syms_[current_player_-1] << " please enter the desired cell to place your move (1-9):  ";
		std::cin >> cell;

		if (board_[(cell-1)/3][(cell-1)%3] != 0) {
			std::cout << "Please place your move in a valid open cell...";
			cell = -1;
		} else {
			board_[(cell-1)/3][(cell-1)%3] = current_player_;
		}
	}
}

// CpuMove is the games AI.  There are 2 modes.  Random cell selector (easy mode) and smart mode.
void Game::cpuMove() {
	// TODO
}

// Analyze board checks the board for all win conditions and cat's game condition.
// If any of them are met then the game over bool will flag and the winner (0,1,2) will be returned.
int Game::analyzeBoard() {

	// Check all row win conditions
	for (int i=0; i<3; ++i) {
		if (board_[i][0] == board_[i][1] && board_[i][0] == board_[i][2] && board_[i][0] != 0) {
			game_over_ = true;
			return board_[i][0];
		}
	}

	// Check all column win conditions
	for (int j=0; j<3; ++j) {
		if (board_[0][j] == board_[1][j] && board_[0][j] == board_[2][j] && board_[0][j] != 0) {
			game_over_ = true;
			return board_[0][j];
		}
	}

	// Check first diagonal win condition
	if (board_[0][0] == board_[1][1] && board_[0][0] == board_[2][2] && board_[0][0] != 0) {
		game_over_ = true;
		return board_[0][0];		
	}

	// Check back diagonal win condition
	if (board_[0][2] == board_[1][1] && board_[0][2] == board_[2][0] && board_[0][2] != 0) {
		game_over_ = true;
		return board_[0][2];		
	}

	// If any of the cell values are still 0 then there's still at least one move to be made
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j){
			if (board_[i][j] == 0) return -1;
		}
	}

	// If no conditions above are met then it's a cat's game
	game_over_ = true;
	return 0;
}


// Print board function simply prints the current game board to the terminal 
// with 1's mapped to X's, 2's mapped to O's, and anything else is a blank cell
void Game::printBoard() {
	std::cout << std::endl;
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j){
			if (board_[i][j] == 1) {
				std::cout << " " << syms_[0];
			} else if (board_[i][j] == 2) {
				std::cout << " " << syms_[1];
			} else {
				std::cout << "  ";	
			}
			if (j < 2) std::cout << " |";
		}
		if (i < 2) std::cout << std::endl << "-----------" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void Game::gameResult() {
	if (result_ == 0) {
		std::cout << "The game ended in a tie...Ya basket of cats!" << std::endl;
	} else if (result_ == 1) {
		std::cout << "PLAYER " << syms_[0] << " IS THE CHAMPION!" << std::endl << std::endl;
	} else {
		std::cout << "PLAYER " << syms_[1] << " IS THE CHAMPION!" << std::endl << std::endl;
	}
}

int main(int argc, char** argv) {
	Game game;
};
