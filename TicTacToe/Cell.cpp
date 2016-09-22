#include "Cell.h"

using namespace tic_tac_toe;

Cell::Cell()
	: m_actual_state(EMPTY)
{
}

Cell::State Cell::getState() const
{
	return m_actual_state;
}

void Cell::setState(State t_value)
{
	if (m_actual_state == EMPTY)
	{
		m_actual_state = t_value;
	}
	else
	{
		throw "Cell is already used.";
	}
}

Cell::State Cell::getReversedState(const State t_state)
{
	return (t_state == Cell::CROSS) ? Cell::NOUGHT : Cell::CROSS;
}

