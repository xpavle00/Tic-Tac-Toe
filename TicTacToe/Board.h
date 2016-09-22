/**
*	@file		Board.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The Board class represents board of all cells.
*/

#ifndef TICTAC_BOARD_H
#define TICTAC_BOARD_H

#include <vector>

#include "Cell.h"

namespace tic_tac_toe
{
	class Board
	{

	public:

		/**
		*	Structure represents all possible directions.
		*/
		enum Direction
		{
			D_HORIZONTAL,
			D_VERTICAL,
			D_DIAGONAL,
			D_ANTIDIAGONAL
		};


		/**
		*	Structure represents position on board.
		*/
		struct Position
		{
			int x;
			int y;

			Position(const int t_x, const int t_y);
		};

		/**
		*	Constructor that creates board of given size.
		*
		*	@param t_size Size of board.
		*/
		explicit Board(const size_t t_size);

		/**
		*	Get cell on given position.
		*
		*	@paran t_position Position of cell.
		*	@return Cell.
		*/
		Cell getCell(const Position t_position) const;

		/**
		*	Set state of cell on given position.
		*
		*	@paran t_position Position of cell.
		*	@paran t_state New cell state.
		*/
		void setCellState(const Position t_position, Cell::State t_state);

		/**
		*	Check if given position is between board boundaries.
		*
		*	@paran t_position Position of cell.
		*	@return True if position is on board.
		*/
		bool isInBoard(const Position t_position) const;

		/**
		*	Get size of board.
		*
		*	@return Size of board.
		*/
		size_t getSize() const;

		/**
		*	Get amount of the free cells on board.
		*
		*	@return Number of free cells.
		*/
		int getFreeCells() const;

		/**
		*	Get parameter from given direction.
		*
		*	@paran t_direction Given direction.
		*	@return Position struct with parameters of direction.
		*/
		static Position getParameterFromDirection(const Direction t_direction);

	private:
		size_t m_size{ 3 };
		int m_free_cells{ 0 };
		std::vector<Cell> m_board{ std::vector<Cell>(m_size * m_size) };
	};
}

#endif