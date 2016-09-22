#include "GUI.h"
#include "qdesktopwidget.h"
#include "qfile.h"
#include "qlabel.h"
#include "qpainter.h" 
#include "qsignalmapper.h"

using namespace tic_tac_toe;

Gui::Gui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(launchGame())); 
	connect(ui.gameSize, SIGNAL(valueChanged(int)), this, SLOT(changeSize(int)));
	connect(ui.firstPlayer, SIGNAL(pressed()), this, SLOT(changeToPlayer()));
	connect(ui.firstCPU, SIGNAL(pressed()), this, SLOT(changeToCPU()));
	connect(ui.pvp, SIGNAL(pressed()), this, SLOT(changeToPvP()));

	this->setWindowTitle("Tic-Tac-Toe");
}

Gui::~Gui()
{

}


void Gui::launchGame()
{
	if (m_in_game)
	{
		for (auto &tmp : playground)
		{
			for (auto &button : tmp)
			{
				button->deleteLater();
			}
		}

		window->layout()->deleteLater();
		window->deleteLater();
		window->hide();
		window->close();

		window = new QWidget;
		m_in_game = false;
	}

	playground.clear();
	
	m_game = new TicTacToe(m_game_size);	
	QGridLayout *layout = new QGridLayout;
	
	QFile File("Resources/qss/stylesheet.qss");
	File.open(QFile::ReadOnly);
	m_style = QLatin1String(File.readAll());

	auto window_size = m_game_size * CONST_CELL_SIZE;

	QRect res = QApplication::desktop()->screenGeometry();

	if (m_game_size > 30)
		window_size = m_game_size * CONST_SMALL_CELL_SIZE;
	else if (window_size > res.height())
		window_size = res.height(); 
	
	for (auto i= 0; i < m_game_size; i++)
	{
		std::vector<QPushButton *> tmp;
		for (auto j= 0; j < m_game_size; j++)
		{
			tmp.push_back(new QPushButton());
			layout->addWidget(tmp.back(),i,j);

			tmp.back()->setProperty("x_pos", QVariant(i));
			tmp.back()->setProperty("y_pos", QVariant(j));

			connect(tmp.back(), SIGNAL(clicked()), this, SLOT(playBox()));

			tmp.back()->setObjectName("cellButton");
		}
		
		playground.push_back(tmp);
	}

	window->setStyleSheet(m_style);
	window->setFixedSize(window_size, window_size);
	window->setLayout(layout);
	window->setWindowTitle("Tic-Tac-Toe");
	window->show();

	if(m_game_mode == CPU)
	{
		m_bot = new Bot(m_game->getWinSize(), Cell::CROSS);
		oneMove(m_bot->nextMove(m_game->getBoard()));		
	}
	else if (m_game_mode == PLAYER)
	{
		m_bot = new Bot(m_game->getWinSize(), Cell::NOUGHT);		
	}

	m_in_game = true;
	m_game_ended = false;
}

void Gui::changeSize(int value)
{
	m_game_size = value;
}

void Gui::changeToPlayer()
{
	m_game_mode = PLAYER;
}

void Gui::changeToCPU()
{
	m_game_mode = CPU;
}

void Gui::changeToPvP()
{
	m_game_mode = PVP;
}

void Gui::playBox()
{
	if (!m_game_ended)
	{
		QPushButton* obj = static_cast<QPushButton*>(sender());
		auto x = obj->property("x_pos").toInt();
		auto y = obj->property("y_pos").toInt();

		try
		{
			oneMove(Board::Position(x,y));

			if (m_game_mode != PVP && m_game->getBoard().getFreeCells() > 0)
				oneMove(m_bot->nextMove(m_game->getBoard()));
		}
		catch (const char* e)
		{
			showDialog(e);
		}
	}
}


void Gui::oneMove(Board::Position t_next_move)
{
	m_game->markCell(t_next_move);

	(m_game->getStateFromActualTurn() != Cell::CROSS) 
		? playground[t_next_move.x][t_next_move.y]->setProperty("cross", true)
		: playground[t_next_move.x][t_next_move.y]->setProperty("nought", true);

	window->style()->unpolish(playground[t_next_move.x][t_next_move.y]);
	window->style()->polish(playground[t_next_move.x][t_next_move.y]);
	window->update();	

	checkWinner(t_next_move);
}

void Gui::checkWinner(Board::Position t_next_move)
{
	auto check = m_game->checkWinner(t_next_move);

	if (check.size()>1)
	{
		for (auto &coords : check)
		{
			playground[coords.x][coords.y]->setProperty("win", true);
			window->style()->unpolish(playground[coords.x][coords.y]);
			window->style()->polish(playground[coords.x][coords.y]);
			window->update();
		}

		m_game_ended = true;

		if(m_game->getActualTurn() != Turn::PLAYER1)
		{
			throw "Player 1 wins.";
		}
		else
		{
			throw "Player 2 wins.";
		}
	}
}

void Gui::showDialog(const char* message) const
{
	QWidget *dialog = new QWidget;
	QLabel *label = new QLabel();
	QGridLayout *layout = new QGridLayout();
	QPushButton *ok_button = new QPushButton();

	label->setText(message);
	label->setStyleSheet("font: 15pt;");

	ok_button->setText("OK");
	ok_button->setFixedWidth(100);
	connect(ok_button, SIGNAL(clicked()), dialog, SLOT(close()));

	layout->addWidget(label, 0, 0, Qt::AlignCenter);
	layout->addWidget(ok_button, 1, 0, Qt::AlignCenter);

	dialog->setWindowTitle("Tic-Tac-Toe");
	dialog->setFixedSize(300, 150);
	dialog->setLayout(layout);
	dialog->show();
}
