/**
*	@file		TicTacToe.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The TicTacToe class represents one game of tic-tac-toe.
*/

#ifndef TICTAC_TICTACTOE_H
#define TICTAC_TICTACTOE_H

#include <vector>

#include "Cell.h"
#include "Turn.h"
#include "Board.h"

#define TICTACTOE_MAX_WIN 5

namespace tic_tac_toe
{
	class TicTacToe
	{

	public:

		/**
		*	Constructor that creates new game
		*
		*	@param t_size Set size of board for game.
		*/
		explicit TicTacToe(const size_t size);

		/**
		*	Mark cell on entered position.
		*
		*	@param t_coords Position of cell to mark.
		*/
		void markCell(const Board::Position t_coords);

		/**
		*	Calculate cell state from actual turn in game.
		*
		*	@return Now playing state.
		*/
		Cell::State getStateFromActualTurn() const;

		/**
		*	Check if winner exists.
		*
		*	@param t_position Position of cell in winline.
		8	@return Vector of winline positions.
		*/
		std::vector<Board::Position> checkWinner(const Board::Position t_position) const;

		/**
		*	Check winline on one direction.
		*
		*	@param t_position Position of cell in winline.
		*	@param t_direction Direction of winline.
		*	@return Vector of winline positions.
		*/
		std::vector<Board::Position> checkDirection(const Board::Position t_position, const Board::Direction t_direction) const;

		/**
		*	Get win size.
		*
		*	@return  Number of same cells in row needed to win.
		*/
		int getWinSize() const;

		/**
		*	Get actual board.
		*
		*	@return Actual board.
		*/
		Board getBoard() const;

		/**
		*	Get actual turn.
		*
		*	@return Actual turn.
		*/
		Turn::Player getActualTurn() const;

	private:
		Board m_board{ Board(3) };
		Turn m_turn{ Turn(Turn::PLAYER1) };
		int m_win_size{ 3 };
	};
}

#endif