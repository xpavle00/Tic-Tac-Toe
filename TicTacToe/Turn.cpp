#include "Turn.h"

using namespace tic_tac_toe;

Turn::Turn(Player first)
	: m_actual_turn(first)
{
}

void Turn::flipTurn()
{
	(m_actual_turn == PLAYER1) ? (m_actual_turn = PLAYER2) : (m_actual_turn = PLAYER1);
}

Turn::Player Turn::getActualTurn() const
{
	return m_actual_turn;
}