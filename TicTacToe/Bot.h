/**
*	@file		Bot.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The Bot class represents AI for TicTacToe.
*/

#ifndef TICTAC_BOT_H
#define TICTAC_BOT_H

#include "Cell.h"
#include "Board.h"

#define CONST_SCORE_BOT 1000
#define CONST_SCORE_EMPTY 10
#define CONST_SCORE_BETWEEN 100
#define CONST_SCORE_OPPONENT 500
#define CONST_MIN_SCORE -10000

namespace tic_tac_toe
{
	class Bot
	{
	public:

		/**
		*	Structure represents score and position of suggested move.
		*/
		struct ValuedMove
		{
			int score;
			Board::Position position;

			/**
			*	Constructs ValuedMove structure.
			*
			*	@param t_score Score of the move.
			*	@param t_position Position of the move
			*/
			ValuedMove(int t_score, Board::Position t_position);
		};

		/**
		*	Constructor that creates Bot.
		*
		*	@param t_win_size Number of symbols in row needed for victory.
		*	@param t_bot_symbol Symbol of player played by AI.
		*/
		explicit Bot(int t_win_size, Cell::State t_bot_symbol);

		/**
		*	Find best move in one direction.
		*
		*	@param	t_board Actual board.
		*	@param	t_start Start position of line.
		*	@param	t_symbol Symbol needed to play in line.
		*	@param	t_direction Direction of the line.
		*	@param	t_opponent True when bot tryies to predict opponents move.
		*/
		ValuedMove nextInLine(const Board t_board, const Board::Position t_start, const Cell::State t_symbol, const Board::Direction t_direction, const bool t_opponent = false) const;

		/**
		*	Find best next move.
		*
		*	@param t_board Actual board.
		*/
		Board::Position nextMove(Board t_board);

		/**
		*	Reset flag of first move.
		*/
		void resetFirst();

	private:
		Cell::State m_bot_symbol{ Cell::CROSS };
		int m_win_size{ 3 };
		bool m_first_move_flag{ true };
	};
}

#endif