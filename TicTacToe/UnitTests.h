/**
*	@file		UnitTests.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The UnitTest class is here only for development.
*/

#ifndef TICTAC_TESTS_H
#define TICTAC_TESTS_H

namespace tic_tac_toe
{
	class UnitTests
	{
	public:
		static void testClassCell();
		static void testClassBoard();
		static void testClassTurn();
		static void testClassTicTacToe();
		static void testClassBot();
		static void testAll();
	};
}

#endif