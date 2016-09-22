#include "Board.h"

using namespace tic_tac_toe;

Board::Board(const size_t t_size)
	:m_size(t_size),
	m_free_cells(t_size * t_size),
	m_board(std::vector<Cell>(t_size * t_size))
{
}

Board::Position::Position(const int t_x, const int t_y)
	:x(t_x),
	y(t_y)
{
}

Cell Board::getCell(Position t_position) const
{
	if (!isInBoard(t_position))
		throw "Out of board.";

	return m_board.at(t_position.x  * m_size + t_position.y);
}

void Board::setCellState(const Position t_position, Cell::State t_state)
{
	if (!isInBoard(t_position))
		throw "Out of board.";
	
	m_board.at(t_position.x  * m_size + t_position.y).setState(t_state);
	--m_free_cells;
}

Board::Position Board::getParameterFromDirection(const Direction t_direction)
{

	auto parameter = Position(-1, -1);

	switch (t_direction)
	{
		case Board::D_VERTICAL:
			parameter.x = 1;
			parameter.y = 0;
			break;
		case Board::D_ANTIDIAGONAL:
			parameter.x = -1;
			parameter.y = 1;
			break;
		case Board::D_HORIZONTAL:
			parameter.x = 0;
			parameter.y = 1;
			break;
		case Board::D_DIAGONAL:
			parameter.x = 1;
			parameter.y = 1;
			break;
		default:
			throw "Wrong direction.";
	}

	return parameter;
}

bool Board::isInBoard(const Position t_position) const
{
	return (t_position.x < m_size && t_position.y < m_size && t_position.x >= 0 && t_position.y >= 0);
}

size_t Board::getSize() const
{
	return m_size;
}

int Board::getFreeCells() const
{
	return m_free_cells;
}



