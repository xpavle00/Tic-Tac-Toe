/**
*	@file		Turn.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The Turn class represents actual player.
*/

#ifndef TICTAC_TURN_H
#define TICTAC_TURN_H

namespace tic_tac_toe
{
	class Turn
	{

	public:

		/**
		*	Enumeration of possible players.
		*/
		enum Player
		{
			PLAYER1,
			PLAYER2
		};

		/**
		*	Constructor that creates turn with given player.
		*
		*	@param t_first Set player on start. (default PLAYER1)
		*/
		explicit Turn(const Player t_first = PLAYER1);

		/**
		*	Flip turn to other player.
		*/
		void flipTurn();

		/**
		*	Get actual turn.
		*
		*	@return Actual turn.
		*/
		Player getActualTurn() const;

	private:
		Player m_actual_turn;

	};
}

#endif