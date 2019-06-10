
///////////////////////////////////////////////////////////////////////////////
//      Title     : tic_tac_toe.h
//      Project   : tic_tac_toe
//      Created   : 4/5/2019
//      Author    : Chris Suarez
//      Platforms : Ubuntu 64-bit
///////////////////////////////////////////////////////////////////////////////

#include "tic_tac_toe.h"

// Constructor
Game::Game() {
	this->menu();
}

// Game menu method!
void Game::menu() {
	int menu_val = 0;
	std::cout << "--- MENU ---" << std::endl;
	std::cout << "1. How to play" << std::endl;
	std::cout << "2. Start new game" << std::endl;
	std::cout << "3. Exit Program" << std::endl;
	std::cout << "4. Super secret mode" << std::endl;
	std::cout << "Enter your choice here: ";

	while (menu_val < 1 || menu_val > 4) {
		while(!(std::cin >> menu_val)) {
			std::cout << "Please enter an integer value for the menu option.  ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (menu_val == 1) {
			this->instructions();
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

// This simply prints out the instructions of what the game is and how to play it. When complete it'll send it back to the main menu
void Game::instructions() {
	std::cout << std::endl << "--- Instructions ---" << std::endl;
	std::cout << "Welcome to Tic Tac Toe!  Tic Tac Toe is an exciting game that requires the greatest of whits and courage.  (Press enter to continue)";
	std::cin.ignore();
	std::cin.get();
	std::cout << "The game is based on a 3x3 board in which two players take turns placing a move.  The first to get three (3) in a row wins! (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "When playing this computer based version you will have many options...(Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "You first choose to play against a friend, play against the computer, or even have the computer play itself!  I mean what's more fun than running simulations of games?! (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "Then you choose what your movement character you want! The convention is either an 'X' or an 'O' but what fun is a game without some customization? (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "By the way if you are playing 2 player or against the computer you will also have to input the other players character as well. (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "If you are playing against the computer or running a sim you then will enter how smart you want the computer to play! (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "The computer can either play in random mode (1) or in super smart mode (2).  Be wary, smart mode might just be the smartest thing you've ever witnessed in your life. (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "Like if you were playing against Albert Einstein...you know, if he was essentially a state machine that had pre-programmed tic tac toe strategies encoded in him (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "After you choose the cpu mode then you are all set to make the first move! (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "To make a move you will need to enter a cell number (from 1 to 9) for where you want to place your move. (Press enter to continue)";
	// std::cin.ignore();
	std::cin.get();
	std::cout << "The graphic below shows you which number corresponds to which cell. (Press enter to continue)";
	std::cout << std::endl << std::endl;
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j){
			std::cout << " " << 1 + j + 3*i;
			if (j < 2) std::cout << " |";
		}
		if (i < 2) std::cout << std::endl << "-----------" << std::endl;
	}
	std::cout << std::endl << std::endl;
	std::cout << "(Press enter to continue)";
	std::cin.get();
	std::cout << "Now that you can make moves it's time make moves! Just be the first one to get three of your character in a row and win fabulous prizes! (Press enter to return back to the main menu)" << std::endl;
	std::cin.get();
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
	cpu_diff_[0] = 0;
	cpu_diff_[1] = 0;

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
		while(!(std::cin >> num_players)) {
			std::cout << "Please enter an integer value.  ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
		}
	}

	// Allowing users to set whatever character they want to play with.
	// If the input more than 1 character then we use then dummy_str to grab only the first char
	char dummy_str[140];
	for (int i=0; i<num_players; ++i) {
		std::cout << "Player " << i+1 << " please enter the character to place on the board for your move:  ";
		std::cin >> dummy_str;
		syms_[i] = dummy_str[0];
	}

	// If there is at least 1 computer player then have the user input easy or smart mode
	if (num_players == 0) {
		while (cpu_diff_[0] < 1 || cpu_diff_[0] > 2) {
			std::cout << "How smart do you want computer player X to be? Enter (1) for easy mode or (2) for smart mode:  ";
			while(!(std::cin >> cpu_diff_[0])) {
				std::cout << "Please enter an integer value.  ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		while (cpu_diff_[1] < 1 || cpu_diff_[1] > 2) {
			std::cout << "How smart do you want computer player O to be? Enter (1) for easy mode or (2) for smart mode:  ";
			while(!(std::cin >> cpu_diff_[1])) {
				std::cout << "Please enter an integer value.  ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		// Assigning X and O to the computer moves but using another dummy string because couldnt figure out the best way to do this
		char dumdum[100] = "XO";
		syms_[0] = dumdum[0];
		syms_[1] = dumdum[1];

	// When 1 player have the user choose the difficulty for the cpu
	} else if (num_players == 1) {
		std::cout << "Please enter the character to place on the board for the computer's move:  ";
		std::cin >> dummy_str;
		syms_[1] = dummy_str[0];	

		while (cpu_diff_[1] < 1 || cpu_diff_[0] > 2) {
			std::cout << "How smart do you want computer player to be? Enter (1) for easy mode or (2) for smart mode:  ";
			while(!(std::cin >> cpu_diff_[1])) {
				std::cout << "Please enter an integer value.  ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}
}

// The method that runs the game via callbacks
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
			this->turnManager();
			this->printBoard();
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
	int cell = -1;

	// Have the user input a cell number between 1 and 9
	while (cell < 1 || cell > 9) {
		std::cout << "Player " << syms_[current_player_-1] << " please enter the desired cell to place your move (1-9):  ";
		while(!(std::cin >> cell)) {
			std::cout << "Please enter an integer value.  ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (cell == 99) {
			std::cout << "EASTER EGG! Random Move Generated! ...sorry" << std::endl;
			this->randomMove();
			return;
		}
		// If the input cell number is already consumed on the board then make the user input again by setting cell to -1
		if (board_[(cell-1)/3][(cell-1)%3] != 0) {
			std::cout << "Please place your move in a valid open cell...";
			cell = -1;

		// User entered a valid cell so place on map
		} else {
			board_[(cell-1)/3][(cell-1)%3] = current_player_;
		}
	}
}

// CpuMove is the games AI.  There are 2 modes.  Random cell selector (easy mode) and smart mode.
void Game::cpuMove() {
	int cell = -1;
	std::cout << "Computing move..." << std::endl;

	// If the current cpu player is on smart mode then play smart!
	if (cpu_diff_[current_player_ - 1] == 2) {

		// We are going to understand the board by using bool arrays for each player and open cells
		bool ur_cells[9] = {false};
		bool opp_cells[9] = {false};
		bool open_cells[9] = {false};
		bool empty_board = true;
		bool debug_ai = false;

		// Run through the board and fill up boolean arrays to understand board easily
		for (int i=0; i<3; ++i) {
			for (int j=0; j<3; ++j){
				if (board_[i][j] == 0) {
					open_cells[j + 3*i] = true;
				} else if (board_[i][j] == current_player_) {
					ur_cells[j + 3*i] = true;
					empty_board = false;
				} else {
					opp_cells[j + 3*i] = true;
					empty_board = false;
				}
			}
		}

		// First check to see if we can win the game.  These are the highest priority moves
		// Row win conditions
		for (int i=0; i<3; ++i){
			if (ur_cells[0 + i*3] && ur_cells[1 + i*3] && open_cells[2 + i*3]) {
				if (debug_ai) std::cout << "ROW WIN CONDITION 1" << std::endl;
				board_[i][2] = current_player_;
				return;
			}
			if (ur_cells[0 + i*3] && ur_cells[2 + i*3] && open_cells[1 + i*3]) {
				if (debug_ai) std::cout << "ROW WIN CONDITION 2" << std::endl;
				board_[i][1] = current_player_;
				return;
			}
			if (ur_cells[1 + i*3] && ur_cells[2 + i*3] && open_cells[0 + i*3]) {
				if (debug_ai) std::cout << "ROW WIN CONDITION 3" << std::endl;
				board_[i][0] = current_player_;
				return;
			}
		}

		// Column win conditions
		for (int j=0; j<3; ++j){
			if (ur_cells[j] && ur_cells[3 + j] && open_cells[6 + j]) {
				if (debug_ai) std::cout << "COLUMN WIN CONDITION 1" << std::endl;
				board_[2][j] = current_player_;
				return;
			}
			if (ur_cells[j] && ur_cells[6 + j] && open_cells[3 + j]) {
				if (debug_ai) std::cout << "COLUMN WIN CONDITION 2" << std::endl;
				board_[1][j] = current_player_;
				return;
			}
			if (ur_cells[3 + j] && ur_cells[6 + j] && open_cells[j]) {
				if (debug_ai) std::cout << "COLUMN WIN CONDITION 3" << std::endl;
				board_[0][j] = current_player_;
				return;
			}
		}

		// Diagonal win conditions
		if (ur_cells[0] && ur_cells[4] && open_cells[8]) {
			if (debug_ai) std::cout << "DIAG WIN CONDITION 1" << std::endl;
			board_[2][2] = current_player_;
			return;
		}
		if (ur_cells[0] && ur_cells[8] && open_cells[4]) {
			if (debug_ai) std::cout << "DIAG WIN CONDITION 2" << std::endl;
			board_[1][1] = current_player_;
			return;
		}
		if (ur_cells[4] && ur_cells[8] && open_cells[0]) {
			if (debug_ai) std::cout << "DIAG WIN CONDITION 3" << std::endl;
			board_[0][0] = current_player_;
			return;
		}
		if (ur_cells[2] && ur_cells[4] && open_cells[6]) {
			if (debug_ai) std::cout << "DIAG WIN CONDITION 4" << std::endl;
			board_[2][0] = current_player_;
			return;
		}
		if (ur_cells[2] && ur_cells[6] && open_cells[4]) {
			if (debug_ai) std::cout << "DIAG WIN CONDITION 5" << std::endl;
			board_[1][1] = current_player_;
			return;
		}
		if (ur_cells[4] && ur_cells[6] && open_cells[2]) {
			if (debug_ai) std::cout << "DIAG WIN CONDITION 6" << std::endl;
			board_[0][2] = current_player_;
			return;
		}

		// Now check for moves to block a loss.  Second highest priority moves
		// Row lose conditions
		for (int i=0; i<3; ++i){
			if (opp_cells[0 + i*3] && opp_cells[1 + i*3] && open_cells[2 + i*3]) {
				if (debug_ai) std::cout << "ROW LOSE CONDITION 1" << std::endl;
				board_[i][2] = current_player_;
				return;
			}
			if (opp_cells[0 + i*3] && opp_cells[2 + i*3] && open_cells[1 + i*3]) {
				if (debug_ai) std::cout << "ROW LOSE CONDITION 2" << std::endl;
				board_[i][1] = current_player_;
				return;
			}
			if (opp_cells[1 + i*3] && opp_cells[2 + i*3] && open_cells[0 + i*3]) {
				if (debug_ai) std::cout << "ROW LOSE CONDITION 3" << std::endl;
				board_[i][0] = current_player_;
				return;
			}
		}

		// Column lose conditions
		for (int j=0; j<3; ++j){
			if (opp_cells[j] && opp_cells[3 + j] && open_cells[6 + j]) {
				if (debug_ai) std::cout << "COLUMN LOSE CONDITION 1" << std::endl;
				board_[2][j] = current_player_;
				return;
			}
			if (opp_cells[j] && opp_cells[6 + j] && open_cells[3 + j]) {
				if (debug_ai) std::cout << "COLUMN LOSE CONDITION 2" << std::endl;
				board_[1][j] = current_player_;
				return;
			}
			if (opp_cells[3 + j] && opp_cells[6 + j] && open_cells[j]) {
				if (debug_ai) std::cout << "COLUMN LOSE CONDITION 3" << std::endl;
				board_[0][j] = current_player_;
				return;
			}
		}

		// Diagonal lose conditions
		if (opp_cells[0] && opp_cells[4] && open_cells[8]) {
			if (debug_ai) std::cout << "DIAG LOSE CONDITION 1" << std::endl;
			board_[2][2] = current_player_;
			return;
		}
		if (opp_cells[0] && opp_cells[8] && open_cells[4]) {
			if (debug_ai) std::cout << "DIAG LOSE CONDITION 2" << std::endl;
			board_[1][1] = current_player_;
			return;
		}
		if (opp_cells[4] && opp_cells[8] && open_cells[0]) {
			if (debug_ai) std::cout << "DIAG LOSE CONDITION 3" << std::endl;
			board_[0][0] = current_player_;
			return;
		}
		if (opp_cells[2] && opp_cells[4] && open_cells[6]) {
			if (debug_ai) std::cout << "DIAG LOSE CONDITION 4" << std::endl;
			board_[2][0] = current_player_;
			return;
		}
		if (opp_cells[2] && opp_cells[6] && open_cells[4]) {
			if (debug_ai) std::cout << "DIAG LOSE CONDITION 5" << std::endl;
			board_[1][1] = current_player_;
			return;
		}
		if (opp_cells[4] && opp_cells[6] && open_cells[2]) {
			if (debug_ai) std::cout << "DIAG LOSE CONDITION 6" << std::endl;
			board_[0][2] = current_player_;
			return;
		}		

		// If we can't win or immediately block a loss then we will try to choose smart moves on a more open board.
		// If the oppnent owns the top left corner then go in the center or cells 2 or 4
		if (opp_cells[0]) {
			if (open_cells[4]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 04" << std::endl;
				board_[1][1] = current_player_;
				return;
			}
			if (open_cells[1]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 01" << std::endl;
				board_[0][1] = current_player_;
				return;
			}
			if (open_cells[3]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 03" << std::endl;
				board_[1][0] = current_player_;
				return;
			}
		}

		// If the oppnent owns cell 2 then go in one of the bottom corners
		if (opp_cells[1]) {
			if (open_cells[6]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 16" << std::endl;
				board_[2][0] = current_player_;
				return;
			}
			if (open_cells[8]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 18" << std::endl;
				board_[2][2] = current_player_;
				return;
			}
		}

		// If the oppnent owns cell 3 then go in the center or cell 2 or 6
		if (opp_cells[2]) {
			if (open_cells[4]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 24" << std::endl;
				board_[1][1] = current_player_;
				return;
			}
			if (open_cells[1]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 21" << std::endl;
				board_[0][1] = current_player_;
				return;
			}
			if (open_cells[5]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 25" << std::endl;
				board_[1][2] = current_player_;
				return;
			}
		}

		// If the oppnent owns cell 4 then go in one of the right most corners
		if (opp_cells[3]) {
			if (open_cells[2]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 32" << std::endl;
				board_[0][2] = current_player_;
				return;
			}
			if (open_cells[8]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 38" << std::endl;
				board_[2][2] = current_player_;
				return;
			}
		}
	
		// If the oppnent owns the center then go in one of the corners
		if (opp_cells[4]) {
			if (open_cells[0]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 40" << std::endl;
				board_[0][0] = current_player_;
				return;
			}
			if (open_cells[2]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 42" << std::endl;
				board_[0][2] = current_player_;
				return;
			}
			if (open_cells[6]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 46" << std::endl;
				board_[2][0] = current_player_;
				return;
			}
			if (open_cells[8]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 48" << std::endl;
				board_[2][2] = current_player_;
				return;
			}
		}

		// If the oppnent owns cell 6 then go in one of the left corners
		if (opp_cells[5]) {
			if (open_cells[0]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 50" << std::endl;
				board_[0][0] = current_player_;
				return;
			}
			if (open_cells[6]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 56" << std::endl;
				board_[2][0] = current_player_;
				return;
			}
		}
		
		// If the oppnent owns cell 7 then go in the center or cell 4 or 8
		if (opp_cells[6]) {
			if (open_cells[4]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 64" << std::endl;
				board_[1][1] = current_player_;
				return;
			}
			if (open_cells[3]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 63" << std::endl;
				board_[1][0] = current_player_;
				return;
			}
			if (open_cells[7]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 67" << std::endl;
				board_[2][1] = current_player_;
				return;
			}
		}

		// If the oppnent owns cell 8 then go in one of the top corners
		if (opp_cells[7]) {
			if (open_cells[0]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 70" << std::endl;
				board_[0][0] = current_player_;
				return;
			}
			if (open_cells[2]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 72" << std::endl;
				board_[0][2] = current_player_;
				return;
			}
		}

		// If the oppnent owns cell 9 then go in the center or cell 6 or 8
		if (opp_cells[8]) {
			if (open_cells[4]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 84" << std::endl;
				board_[1][1] = current_player_;
				return;
			}
			if (open_cells[5]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 85" << std::endl;
				board_[1][2] = current_player_;
				return;
			}
			if (open_cells[7]) {
				if (debug_ai) std::cout << "OPEN CELL CONDITION 87" << std::endl;
				board_[2][1] = current_player_;
				return;
			}
		}

		// If you own one corner and the opponent only owns the center then go in the opposite corner
		if (ur_cells[0] && opp_cells[4]) {
			board_[2][2] = current_player_;
			return;
		} else if (ur_cells[2] && opp_cells[4]) {
			board_[2][0] = current_player_;
			return;
		} else if (ur_cells[6] && opp_cells[4]) {
			board_[0][2] = current_player_;
			return;
		} else if (ur_cells[8] && opp_cells[4]) {
			board_[0][0] = current_player_;
			return;
		}
		// If the board is empty go in a random corner
		if (empty_board) {
			int r = rand() % 4 + 1;
			if (r == 1)board_[0][0] = current_player_;
			if (r == 2)board_[0][2] = current_player_;
			if (r == 3)board_[2][0] = current_player_;
			if (r == 4)board_[2][2] = current_player_;
			return;
		}

		// If somehow not all conditions have been covered then let's just make a random move.
		this->randomMove();

	// If the current cpu player is on easy mode then it will simply chose an empty cell at random
	} else if (cpu_diff_[current_player_ - 1 == 1]) {
		this->randomMove();

	// If for some reason the cpu difficulty flag is not set to smart or easy mode then revert to easy mode with a cout note
	} else {
		std::cout << "Note: The cpu difficulty parameter is not right.  Reverting to easy mode! " << std::endl;
		this->randomMove();
	}
}

// This method simply makes a valid random move on the board!
void Game::randomMove() {
	int cell = -1;
	while (cell < 1) {
		cell = rand() % 9 + 1;
		if (board_[(cell-1)/3][(cell-1)%3] != 0) cell = -1;
	}

	board_[(cell-1)/3][(cell-1)%3] = current_player_;
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
// with syms[0] and syms[1] mapped to each players board character
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

// Reports the results of the game. 0 - cats game, 1 - player 1, 2 - player 2
void Game::gameResult() {
	if (result_ == 0) {
		std::cout << "The game ended in a tie...Ya basket of cats!" << std::endl;
	} else if (result_ == 1) {
		std::cout << "PLAYER " << syms_[0] << " IS THE CHAMPION!" << std::endl << std::endl;
	} else if (result_ == 2) {
		std::cout << "PLAYER " << syms_[1] << " IS THE CHAMPION!" << std::endl << std::endl;
	} else {
		std::cout << "Welp, something weird happened. The winner variable did not report a valid results. Soooooooooooo......yeaaaaaaaa";
	}
}

int main(int argc, char** argv) {
	Game game;
};
