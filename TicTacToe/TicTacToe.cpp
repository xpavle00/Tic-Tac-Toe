#include "TicTacToe.h"

using namespace tic_tac_toe;

TicTacToe::TicTacToe(size_t size)
	: m_board(Board(size)),
	m_turn(Turn::PLAYER1)
{
	(size <= TICTACTOE_MAX_WIN) ? m_win_size = size : m_win_size = TICTACTOE_MAX_WIN;
}

void TicTacToe::markCell(const Board::Position t_position)
{
	m_board.setCellState(t_position, getStateFromActualTurn());
	m_turn.flipTurn();
}

Cell::State TicTacToe::getStateFromActualTurn() const
{
	if (m_turn.getActualTurn() == Turn::PLAYER1)
	{
		return Cell::CROSS;
	}

	return Cell::NOUGHT;	
}

std::vector<Board::Position> TicTacToe::checkWinner(const Board::Position t_position) const
{

	std::vector<Board::Position> winline = {};

	if (m_board.getCell(t_position).getState() == Cell::EMPTY)
		return winline;

	winline = checkDirection(t_position, Board::D_HORIZONTAL);
	if (winline.size() >= m_win_size)
		return winline;

	winline = checkDirection(t_position, Board::D_VERTICAL);
	if (winline.size() >= m_win_size)
		return winline;

	winline = checkDirection(t_position, Board::D_DIAGONAL);
	if (winline.size() >= m_win_size)
		return winline;

	winline = checkDirection(t_position, Board::D_ANTIDIAGONAL);
	if (winline.size() >= m_win_size)
		return winline;

	return winline;
}

std::vector<Board::Position> TicTacToe::checkDirection(const Board::Position t_position, const Board::Direction t_direction) const
{
	
	auto parameter = Board::getParameterFromDirection(t_direction);

	std::vector<Board::Position> winline = {};
	auto lastAddedState = m_board.getCell(t_position).getState();

	if (lastAddedState == Cell::EMPTY)
		return winline;

	auto step = 1;
	auto next_done = false;
	auto prev_done = false;


	while (!next_done || !prev_done)
	{
		auto next_position = Board::Position(t_position.x + (step * parameter.x), t_position.y + (step * parameter.y));
		auto prev_position = Board::Position(t_position.x - (step * parameter.x), t_position.y - (step * parameter.y));

		if (next_position.x >= 0 && next_position.x < m_board.getSize() && next_position.y >= 0 && next_position.y < m_board.getSize()
			&& (m_board.getCell(next_position).getState() == lastAddedState))
		{
			winline.push_back(next_position);
		}
		else
		{
			next_done = true;
		}

		if (prev_position.x >= 0 && prev_position.x < m_board.getSize() && prev_position.y >= 0 && prev_position.y < m_board.getSize()
			&& (m_board.getCell(prev_position).getState() == lastAddedState))
		{
			winline.push_back(prev_position);
		}
		else
		{
			prev_done = true;
		}

		++step;
	}

	if (winline.size() >= m_win_size - 1)
	{
		winline.push_back(t_position);
	}
	else
	{
		winline.clear();
	}

	return winline;
}

int TicTacToe::getWinSize() const
{
	return m_win_size;
}

Board TicTacToe::getBoard() const
{
	return m_board;
}

Turn::Player TicTacToe::getActualTurn() const
{
	return m_turn.getActualTurn();
}
