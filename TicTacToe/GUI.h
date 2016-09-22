/**
*	@file		GUI.h
*	@author		Peter Pavlenko <pavlenko.p@gmail.com>
*	@date		22/9/2016
*	@version	1.0
*
*	@section DESCRIPTION
*
*	The Gui class represents one all game gui using TicTacToe game.
*/

#ifndef TICTAC_GUI_H
#define TICTAC_GUI_H

#include "ui_launcher.h"
#include "TicTacToe.h"
#include "Bot.h"

#define CONST_CELL_SIZE 70
#define CONST_SMALL_CELL_SIZE 25

namespace tic_tac_toe
{
	class Gui : public QMainWindow
	{
		Q_OBJECT


			/**
			*	Structure represents all possible game modes.
			*/
			enum GameMode
		{
			PLAYER,
			CPU,
			PVP
		};

	public:

		/**
		*	Constructor that creates game gui.
		*/
		explicit Gui(QWidget *parent = nullptr);
		~Gui();

	private:

		/**
		*	Make one move in game.
		*
		*	@param t_next_move Position of marked cell.
		*/
		void oneMove(Board::Position t_next_move);

		/**
		*	Show winner if exists.
		*
		*	@param t_next_move Position of marked cell.
		*/
		void checkWinner(Board::Position t_next_move);

		/**
		*	Show dialog window.
		*
		*	@param t_message Message to show.
		*/
		void showDialog(const char* t_message) const;

		//game
		TicTacToe *m_game;
		Bot* m_bot;
		int m_game_size{ 3 };
		bool m_in_game = false;
		bool m_game_ended = false;

		//gui
		Ui::QTestClass ui;
		QWidget *window = new QWidget;
		QString m_style;
		GameMode m_game_mode{ PLAYER };
		std::vector<std::vector<QPushButton *>> playground;

		//slots
		private slots:
		void launchGame();
		void changeSize(int value);
		void changeToPlayer();
		void changeToCPU();
		void changeToPvP();
		void playBox();

	protected:
		QSpinBox *gameSize;

	};
}

#endif
