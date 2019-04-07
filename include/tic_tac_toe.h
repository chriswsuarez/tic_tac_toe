
///////////////////////////////////////////////////////////////////////////////
//      Title     : tic_tac_toe.h
//      Project   : tic_tac_toe
//      Created   : 4/5/2019
//      Author    : Chris Suarez
//      Platforms : Ubuntu 64-bit
///////////////////////////////////////////////////////////////////////////////

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>

class Game {
public:
	Game();

private:
	int board_[3][3], num_players, current_player_, turn_count_;
	char syms_[2];
	bool game_over_;
	void userInput();
	void cpuMove();
	int analyzeBoard();
	void printBoard();
	inline void turnManager();
	void gameResult(int result);
};

#endif //TIC_TAC_TOE_H
