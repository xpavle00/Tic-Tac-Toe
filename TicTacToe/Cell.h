/**
*	@file		Cell.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The Cell class represents one cell in board.
*/

#ifndef TICTAC_CELL_H
#define TICTAC_CELL_H

namespace tic_tac_toe
{
	class Cell
	{

	public:

		/**
		*	Structure represents all cell states.
		*/
		enum State
		{
			EMPTY,
			CROSS,
			NOUGHT
		};

		/**
		*	Constructor that creates EMPTY cell
		*/
		explicit Cell();

		/**
		*	Get state of cell.
		*
		*	@return State of cell.
		*/
		State getState() const;

		/**
		*	Set state of cell.
		*
		*	@param t_state Set state of cell.
		*/
		void setState(const State t_state);

		/**
		*	Reverse state.
		*
		*	@param t_state Original state.
		*	@return	Reversed state (CROSS x NOUGHT).
		*/
		static State getReversedState(const State t_state);

	private:
		State m_actual_state{ EMPTY };

	};
}

#endif