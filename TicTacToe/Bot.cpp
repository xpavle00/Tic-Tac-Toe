#include "Bot.h"

using namespace tic_tac_toe;

Bot::Bot(int t_win_size, Cell::State t_bot_symbol)
	: m_bot_symbol(t_bot_symbol),
	m_win_size(t_win_size)
{
}

Bot::ValuedMove::ValuedMove(int t_score, Board::Position t_position)
	: score(t_score),
	position(t_position)
{
}

Bot::ValuedMove Bot::nextInLine(const Board t_board, const Board::Position t_start, const Cell::State t_symbol, const Board::Direction t_direction, const bool t_opponent) const
{
	auto empty_before = 0;
	auto empty_between = 0;
	auto empty_after = 0;
	auto counter_bot = 0;
	auto counter_oponent = 0;
	auto last_cell = Cell::CROSS;
	auto pre_last_cell = Cell::CROSS;
	auto before = true;

	// variables to hold possible positions
	auto last_before = Board::Position(-1,-1);
	auto last_between = Board::Position(-1, -1);
	auto last_after = Board::Position(-1, -1);
	auto last_coords = Board::Position(-1, -1);
	auto pre_last_coords = Board::Position(-1, -1);

	auto parameter = Board::getParameterFromDirection(t_direction); //parameter to get next position
	auto step = 0;
	auto next_position = Board::Position(t_start.x + (step * parameter.x), t_start.y + (step * parameter.y));

	while (t_board.isInBoard(next_position))
	{
		// symbol on position
		auto actual_symbol = t_board.getCell(next_position).getState();

		// 3 states of actual symbol
		if (actual_symbol == t_symbol) //wanted symbol
		{
			empty_between += empty_after;
			empty_after = 0;

			// if first wanted cell
			if (before)
			{
				// save last empty cell before wanted symbols
				if (step > 0 && last_cell == Cell::EMPTY)
				{
					last_before = last_coords;
				}

				if (step > 1 && pre_last_cell == Cell::EMPTY && !t_opponent && m_win_size <= 3)
				{
					last_before = pre_last_coords;
				}

				// next empty cells will be after or between wanted cells
				before = false;
			}

			// save last emty cell between wanted bot symbols
			if (empty_between > 0 && step > 0 && last_cell == Cell::EMPTY)
			{
				last_between = last_coords;
			}
			++counter_bot;
		}
		else if (actual_symbol == Cell::EMPTY) // empty symbol
		{
			// if empty before wanted cell
			if (before)
			{
				++empty_before;
			}
			else
			{
				// save first empty position after wanted symbols
				if (step > 0 && last_cell == t_symbol)
				{
					last_after = next_position;
				}

				// save  second empty position after wanted symbols
				if (step > 0 && empty_after == 1 && !t_opponent && m_win_size <= 3)
				{
					last_after = last_after = next_position;
				}

				++empty_after;
			}
		}
		else // opponents cell
		{
			if (empty_before + counter_bot + empty_between + empty_after >= m_win_size)
			{
				break;
			}

			empty_between = 0;
			empty_after = 0;
			empty_before = 0;
			counter_bot = 0;

			++counter_oponent;
		}

		if (step > 0)
		{
			pre_last_coords = last_coords;
			pre_last_cell = last_cell;
		}

		last_coords = next_position;
		last_cell = actual_symbol;
		++step;
		next_position = Board::Position(t_start.x + (step * parameter.x), t_start.y + (step * parameter.y));
	}

	// if possible winline
	if (empty_before + counter_bot + empty_between + empty_after >= m_win_size)
	{
		// calculate score of winline
		auto score = (counter_bot * CONST_SCORE_BOT) + ((empty_before + empty_after) * CONST_SCORE_EMPTY) - (empty_between * CONST_SCORE_BETWEEN);

		// prioritize bots moves
		if (t_opponent)
			score -= CONST_SCORE_OPPONENT;
		
		// return winlines in this order between, after, before if exists
		if (empty_between > 0)
		{
			return ValuedMove(score, last_between);
		}

		if (empty_after > 0)
		{
			return ValuedMove(score, last_after);
		}

		if (empty_before > 0)
		{
			return ValuedMove(score, last_before);
		}
	}

	return{ CONST_MIN_SCORE, Board::Position(-1,-1)};
}

Board::Position Bot::nextMove(Board t_board)
{
	int max_size = t_board.getSize();

	if (m_first_move_flag && t_board.getCell(Board::Position(max_size / 2, max_size / 2)).getState() == Cell::EMPTY)
	{
		m_first_move_flag = false;
		return Board::Position(max_size / 2, max_size / 2);
	}

	auto result = ValuedMove(CONST_MIN_SCORE, Board::Position(-1, -1));

	for (auto i = 0; i < max_size; i++)
	{

		auto tmp_result = nextInLine(t_board, Board::Position(0,i), m_bot_symbol, Board::D_VERTICAL);
		if (tmp_result.score >= result.score)
			result = tmp_result;

		tmp_result = nextInLine(t_board, Board::Position(i, 0), m_bot_symbol, Board::D_HORIZONTAL);
		if (tmp_result.score >= result.score)
			result = tmp_result;

		// find only on diagonals with enought cells
		if (i <= max_size - m_win_size)
		{

			tmp_result = nextInLine(t_board, Board::Position(0, i), m_bot_symbol, Board::D_DIAGONAL);
			if (tmp_result.score > result.score)
				result = tmp_result;
			// do not repeat line
			if (i > 0)
			{
				tmp_result = nextInLine(t_board, Board::Position(0, i), m_bot_symbol, Board::D_DIAGONAL);
				if (tmp_result.score > result.score)
					result = tmp_result;
			}
		}

		// find only on antidiagonals with enought cells
		if (i <= max_size - m_win_size)
		{
			tmp_result = nextInLine(t_board, Board::Position(max_size - 1, i), m_bot_symbol, Board::D_ANTIDIAGONAL);
			if (tmp_result.score > result.score)
				result = tmp_result;
			// do not repeat line
			if (i > 0)
			{
				tmp_result = nextInLine(t_board, Board::Position(i, 0), m_bot_symbol, Board::D_ANTIDIAGONAL);
				if (tmp_result.score > result.score)
					result = tmp_result;
			}
		}
		
		// predict opponents next move
		tmp_result = nextInLine(t_board, Board::Position(0, i), Cell::getReversedState(m_bot_symbol), Board::D_VERTICAL, true);
		if (tmp_result.score > result.score)
			result = tmp_result;

		tmp_result = nextInLine(t_board, Board::Position(i, 0), Cell::getReversedState(m_bot_symbol), Board::D_HORIZONTAL, true);
		if (tmp_result.score > result.score)
			result = tmp_result;


		if (i <= max_size - m_win_size)
		{

			tmp_result = nextInLine(t_board, Board::Position(0, i), Cell::getReversedState(m_bot_symbol), Board::D_DIAGONAL, true);
			if (tmp_result.score > result.score)
				result = tmp_result;
			if (i > 0)
			{
				tmp_result = nextInLine(t_board, Board::Position(0, i), Cell::getReversedState(m_bot_symbol), Board::D_DIAGONAL, true);
				if (tmp_result.score > result.score)
					result = tmp_result;
			}
		}

		if (i <= max_size - m_win_size)
		{
			tmp_result = nextInLine(t_board, Board::Position(max_size - 1, i), Cell::getReversedState(m_bot_symbol), Board::D_ANTIDIAGONAL, true);
			if (tmp_result.score > result.score)
				result = tmp_result;
			if (i > 0)
			{
				tmp_result = nextInLine(t_board, Board::Position(i, 0), Cell::getReversedState(m_bot_symbol), Board::D_ANTIDIAGONAL, true);
				if (tmp_result.score > result.score)
					result = tmp_result;
			}
		}
	}

	// if did not find suggestion find first empty
	if (result.position.x == -1 || result.position.y == -1)
	{
		for (auto i = 0; i < max_size; ++i)
		{
			for (auto j = 0; j < max_size; ++j)
			{
				if (t_board.getCell(Board::Position(i, j)).getState() == Cell::EMPTY)
				{
					return Board::Position(i, j);
				}
			}
		}
	}

	return result.position;
}

void Bot::resetFirst()
{
	m_first_move_flag = true;
}
