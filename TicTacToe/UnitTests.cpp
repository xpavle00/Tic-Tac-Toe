#include "UnitTests.h"

#include <type_traits>
#include <memory>
#include <cassert>

#include "Cell.h"
#include "Board.h"
#include "Turn.h"
#include "TicTacToe.h"
#include "Bot.h"

using namespace tic_tac_toe;

void UnitTests::testClassCell()
{
	auto test_cell_object = std::make_unique<Cell>();

	assert(test_cell_object != nullptr, "Create object error.");

	assert(test_cell_object->getState() == Cell::EMPTY, "Created cell is not empty.");
	test_cell_object->setState(Cell::CROSS);

	assert(test_cell_object->getState() == Cell::CROSS, "Cell did not changed to CROSS.");

	try
	{
		test_cell_object->setState(Cell::NOUGHT);
	}
	catch (const char *e)
	{
		assert(strcmp(e, "Cell is already used.") == 0 , "Bad exception.");
	}

	assert(test_cell_object->getState() == Cell::CROSS, "Not empty Cell changed.");

	assert(Cell::getReversedState(Cell::CROSS) == Cell::NOUGHT, "Reverse state do not working.");
}

void UnitTests::testClassBoard()
{
	auto test_board_object = std::make_unique<Board>(3);

	assert(test_board_object != nullptr, "Create object error.");

	assert(test_board_object->getFreeCells() == 9, "Wrong number of free cells.");

	assert(test_board_object->getCell(Board::Position(0, 0)).getState() == Cell::EMPTY, "Board created with not empty cells.");

	test_board_object->setCellState(Board::Position(0, 0), Cell::NOUGHT);

	assert(test_board_object->getFreeCells() == 8, "Wrong number of free cells.");

	assert(test_board_object->getCell(Board::Position(0, 0)).getState() == Cell::NOUGHT, "Cell is not changed.");
	assert(test_board_object->getCell(Board::Position(2, 2)).getState() == Cell::EMPTY, "Cell on border.");

	try
	{
		test_board_object->getCell(Board::Position(3, 3)).getState();		
	}
	catch (const char *e)
	{
		assert(strcmp(e, "Out of board.") == 0, "Bad exception.");
	}

	assert(!test_board_object->isInBoard(Board::Position(5, 5)), "Out of border unrecognized.");

	assert(Board::getParameterFromDirection(Board::D_HORIZONTAL).x == Board::Position(0, 1).x, "Wrong parameter.");
	assert(Board::getParameterFromDirection(Board::D_HORIZONTAL).y == Board::Position(0, 1).y, "Wrong parameter.");
}

void UnitTests::testClassTurn()
{
	auto test_turn_object = std::make_unique<Turn>(Turn::PLAYER1);

	assert(test_turn_object != nullptr, "Create object error.");

	assert(test_turn_object->getActualTurn() == Turn::PLAYER1, "Created with wrong player.");

	test_turn_object->flipTurn();

	assert(test_turn_object->getActualTurn() == Turn::PLAYER2, "Flip does not work.");
}

void UnitTests::testClassTicTacToe()
{
	auto test_tictactoe_object = std::make_unique<TicTacToe>(3);

	assert(test_tictactoe_object != nullptr, "Create object error.");

	assert(test_tictactoe_object->getWinSize() == 3, "Wrong win size on start.");
	assert(test_tictactoe_object->getActualTurn() == Turn::PLAYER1, "Wrong turn on start.");
	assert(test_tictactoe_object->getStateFromActualTurn() == Cell::CROSS, "Wrong state from actual turn.");

	test_tictactoe_object->markCell(Board::Position(0, 0));

	assert(test_tictactoe_object->getActualTurn() == Turn::PLAYER2, "Turn did not changed.");
	assert(test_tictactoe_object->getStateFromActualTurn() == Cell::NOUGHT, "Wrong state from actual turn.");

	assert(test_tictactoe_object->checkWinner(Board::Position(0,0)).size() == 0, "Wrong winline found.");
	assert(test_tictactoe_object->checkWinner(Board::Position(0, 1)).size() == 0, "Wrong winline found.");

	assert(test_tictactoe_object->checkDirection(Board::Position(0, 0), Board::D_DIAGONAL).size() == 0, "Wrong winline found.");
	assert(test_tictactoe_object->checkDirection(Board::Position(0, 1), Board::D_VERTICAL).size() == 0, "Wrong winline found.");

	test_tictactoe_object->markCell(Board::Position(1, 0));
	test_tictactoe_object->markCell(Board::Position(0, 1));
	test_tictactoe_object->markCell(Board::Position(1, 1));
	test_tictactoe_object->markCell(Board::Position(0, 2));

	assert(test_tictactoe_object->checkDirection(Board::Position(0, 0), Board::D_HORIZONTAL).size() == 3, "Wrong winline found.");
	assert(test_tictactoe_object->checkDirection(Board::Position(0, 0), Board::D_HORIZONTAL).size() == 3, "Wrong winline found.");

	assert(test_tictactoe_object->checkDirection(Board::Position(1, 0), Board::D_HORIZONTAL).size() == 0, "Wrong winline found.");
	assert(test_tictactoe_object->checkDirection(Board::Position(1, 0), Board::D_HORIZONTAL).size() == 0, "Wrong winline found.");
}

void UnitTests::testClassBot()
{
	auto test_board_object = std::make_unique<Board>(3);
	auto test_bot_object = std::make_unique<Bot>(3, Cell::CROSS);

	assert(test_bot_object != nullptr, "Create object error.");

	assert(test_bot_object->nextInLine(*test_board_object, Board::Position(0,0), Cell::CROSS, Board::D_HORIZONTAL).position.x == -1, "Empty line sugestion error.");
	auto tmp = test_bot_object->nextMove(*test_board_object);
	assert(tmp.x == 1, "First next move error.");
	assert(tmp.y == 1, "First next move error.");

	test_board_object->setCellState(Board::Position(0, 0), Cell::CROSS);
	test_board_object->setCellState(Board::Position(0, 1), Cell::CROSS);

	assert(test_bot_object->nextInLine(*test_board_object, Board::Position(0, 0), Cell::CROSS, Board::D_HORIZONTAL).position.x == 0, "Winline not found.");
	assert(test_bot_object->nextInLine(*test_board_object, Board::Position(0, 0), Cell::CROSS, Board::D_HORIZONTAL).position.y == 2, "Winline not found.");
	
	assert(test_bot_object->nextMove(*test_board_object).x == 0, "Winline not found.");
	assert(test_bot_object->nextMove(*test_board_object).y == 2, "Winline not found.");
}

void UnitTests::testAll()
{
	testClassCell();
	testClassBoard();
	testClassTurn();
	testClassTicTacToe();
	testClassBot();
}
