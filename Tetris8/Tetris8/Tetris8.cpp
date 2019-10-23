#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFML/Graphics/Rect.hpp"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;
using namespace sf;

const int HightOfGlass = 22;
const int WidthOfGlass = 10;
const int NMain = 20;
const int TTRM = 4;



class Figure
{
public:
	Figure(int figureNum)
	{
		collsNum = 0;
		tetramNum = figureNum;
		setNewFigure(tetramNum, collsNum);
	};

	int getXTetram(int i)
	{
		return tetramX[i];
	}
	int getYTetram(int i)
	{
		return tetramY[i];
	}
	void transform(int figureNum, int coll)
	{
		setNewFigure(tetramNum, coll);
	}
	int getTetramNum()
	{
		return tetramNum;
	}

private:
	int tetramX[TTRM];
	int tetramY[TTRM];
	int tetramNum;
	int collsNum;

	void setTetramVal(int*  x, int  z)
	{
		for (size_t i = 0; i < TTRM; i++)
		{
			tetramX[i] = x[i];
			tetramY[i] = x[i + TTRM];
		}
		tetramNum = z;
		collsNum = 0;
	}
	void setNewFigure(int fig, int coll)
	{
		switch (fig)//O
		{
		case 0:
		{
			int tetramina[TTRM * 2] = { 2, 3, 2, 3, 2, 3, 3, 2 };
			setTetramVal(tetramina, fig);
		}break;

		case 1:
		{
			switch ((coll %= 2))//I
			{
			case (0):
			{
				int tetramina[TTRM * 2] = { 2, 2, 2, 2, 0, 1, 2, 3 };
				setTetramVal(tetramina, fig);
			}break;
			case (1):
			{
				int tetramina[TTRM * 2] = { 0, 1, 2, 3, 2, 2, 2, 2 };
				setTetramVal(tetramina, fig);
			}break;
			}
		}break;

		case 2:
		{
			switch ((coll %= 4))//T
			{
			case (0):
			{
				int tetramina[TTRM * 2] = { 1, 2, 3, 2, 2, 2, 2, 3 };
				setTetramVal(tetramina, fig);
			}break;
			case (1):
			{
				int tetramina[TTRM * 2] = { 2, 2, 2, 1, 1, 2, 3, 2 };
				setTetramVal(tetramina, fig);
			}break;
			case (2):
			{
				int tetramina[TTRM * 2] = { 1, 2, 3, 2, 2, 2, 2, 1 };
				setTetramVal(tetramina, fig);
			}break;
			case (3):
			{
				int tetramina[TTRM * 2] = { 2, 2, 2, 3, 1, 2, 3, 2 };
				setTetramVal(tetramina, fig);
			}break;
			}
		}break;
		default:
			break;
		}
	};
};


class Tetramina
{
public:

	Tetramina(int figureNum,  Tetramina2 *newTetramina)
	{

		switch (figureNum)//O
		{
		case 0:
		{
			/*int tetramina[TTRM * 2] = { 2, 3, 2, 3, 2, 3, 3, 2 };
			setTetramVal(tetramina, fig);*/
		}break;

		case 1:
		{
			ITetramina figure;
			newTetramina = &figure;			

		}break;

		case 2:
		{
			TTetramina figure;
			Tetramina2 *newFigure = &figure;
		}break;
		default:
			break;
		}

		/*collsNum = 0;
		tetramNum = figureNum;
		///Tetramina selectFigClass[7];
		setNewFigure(tetramNum, collsNum);*/
	};

	int getTetramNum()
	{
		return tetramNum;
	}

private:
	int tetramX[TTRM];
	int tetramY[TTRM];
	int tetramNum;
	int collsNum;

	void setTetramVal(int*  x, int  z)
	{
		for (size_t i = 0; i < TTRM; i++)
		{
			tetramX[i] = x[i];
			tetramY[i] = x[i + TTRM];
		}
		tetramNum = z;
		collsNum = 0;
	}
	virtual void setNewFigure(int fig, int coll)
	{
		switch (fig)//O
		{
		case 0:
		{
			int tetramina[TTRM * 2] = { 2, 3, 2, 3, 2, 3, 3, 2 };
			setTetramVal(tetramina, fig);
		}break;
		default:
			break;
		}
	}
};
class Tetramina2
{
public:
	virtual int getXTetram(int i) = 0;

	virtual int getYTetram(int i) = 0;

	virtual void transform() = 0;
};
class TTetramina : public Tetramina2
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 1];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 4;
	};

private:
	int tetramAngle = 0; // переменная поворота
	int tetramina[4][TTRM * 2] = { 1, 2, 3, 2, 2, 2, 2, 3,
									2, 2, 2, 1, 1, 2, 3, 2,
									1, 2, 3, 2, 2, 2, 2, 1,
									2, 2, 2, 3, 1, 2, 3, 2 };

};

class ITetramina : public Tetramina2
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 1];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 2;
	};
private:
	int tetramAngle = 0;
	int tetramina[2][TTRM * 2] = { 2, 2, 2, 2, 0, 1, 2, 3 ,
									0, 1, 2, 3, 2, 2, 2, 2 };

};


class Glass
{
public:

	bool getPoint(int Y, int X)
	{
		return theGlass[Y][X].point;
	}
	int getColor(int Y, int X)
	{
		return theGlass[Y][X].color;
	}

	void setPoint(int Y, int X, int setColor)
	{
		theGlass[Y][X].point = true;
		theGlass[Y][X].color = setColor;
	}

	int delLine()
	{
		bool delLine = false;
		int scoreTmp = 0;
		do
		{
			scoreTmp = scoreTmp + scoreTmp * delLine + 100 * delLine;//подсчёт счёта по хитрой формуле
			delLine = false;
			for (int i = HightOfGlass - 1; i > 1; i--)
			{

				for (size_t j = 0; j < WidthOfGlass; j++)
				{
					if (theGlass[i][j].point == 0)
					{
						delLine = false;
						break;
					}
					else
					{
						delLine = true;
					}
				}

				if (delLine == true)
				{
					for (int i1 = i; i1 > 1; i1--) {
						for (size_t j = 0; j < WidthOfGlass; j++)
							theGlass[i1][j] = theGlass[i1 - 1][j];
					}
					i += 1;
				}
			}
		} while (delLine);

		return scoreTmp;// счёт
	};

private:
	struct GlassStuct
	{
		bool point = 0;
		int color = 0;
	};

	GlassStuct theGlass[HightOfGlass][WidthOfGlass];
};

int main() {
	int score = 0;
	int level = 0;
	int randTetr = 0, randNext = rand() % 3, tetrAn = 0;// фигура
	int yMain = 0;
	unsigned long long tetrTmp = 0;
	unsigned int sleepTime = 105;

	bool exitToMain = false;

	int keyPad(unsigned int&);

	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "Tetris");

	Texture t1, t2, t3;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");

	Sprite s(t1), background(t2), frame(t3);

	Clock clock;

	while (window.isOpen())
	{
		//setGameScreen();// печать основного экрана

		Glass mainGlass;
		Glass toPrintGlass;
		do
		{
			randTetr = randNext;//текущая фигура
			randNext = 2; //rand() % 3; //следующая фигура
			tetrAn = 0;//начальное положение фигуры -угол поворота

			level = score / 1000 + 1;// размер уровня 1000 очков +1 - начинаем с первого

			sleepTime = 101 - (level * 10) * (level <= 10) - 100 * (level > 10);//скорость игры время задержки подобранное 

			//scoreLevel(tetramNext.part, score, level);//печать элементов////

			int xMain = 0, xTmp = 0;// начальное положене фигуры
			bool collapse = false;

			Tetramina2 *newTetramina, *nextTetramina, *tmpTetramina;
			Tetramina mainFigure(2, newTetramina);
			
			//(randTetr); //randTetr // фигура основная
			Tetramina nextFigure(2, nextTetramina); //randNext // фигура следующая (в окошке)
			Tetramina tmpFigure(2, tmpTetramina);

			//Figure mainFigure(randTetr); //randTetr // фигура основная
			//Figure nextFigure(randNext); //randNext // фигура следующая (в окошке)
			//Figure tmpFigure(randTetr);

			for (yMain = 0; yMain < HightOfGlass; yMain++)//цикл опускания фигуры
			{

				toPrintGlass = mainGlass;

				for (size_t i = 0; i < 3; i++) //колличество нажатий на кнопки за одну иттерацию
				{
					tmpFigure = mainFigure;

					xTmp = xMain;//временная х на случай наползания слева-справа

					Event anyEvent;
					while (window.pollEvent(anyEvent))
					{
						if (anyEvent.type == Event::Closed)
							window.close();

						if (anyEvent.type == Event::KeyPressed)
							if (anyEvent.key.code == Keyboard::Up)
							{//поворот фигуры
								//tetrAn++;
								//mainFigure.transform(randTetr, tetrAn);
								newTetramina->transform;
								
							};
						//if (anyEvent.key.code == Keyboard::Left) x = x - 1;
						//if (anyEvent.key.code == Keyboard::Right) x = x + 1;

						if (Keyboard::isKeyPressed(Keyboard::Left)) xMain = xMain - 1;
						if (Keyboard::isKeyPressed(Keyboard::Right)) xMain = xMain + 1;
						if (Keyboard::isKeyPressed(Keyboard::Down)) sleepTime = 1;
					}
					for (size_t i = 0; i < TTRM; i++)
					{
						collapse = mainGlass.getPoint((newTetramina->getYTetram(i) + yMain), (newTetramina->getXTetram(i) + xMain))
							|| (newTetramina->getXTetram(i) + xMain >= WidthOfGlass)
							|| (newTetramina->getXTetram(i) + xMain < 0);
						if (collapse == true)
						{
							xMain = xTmp;
							mainFigure = tmpFigure;
							collapse = false;
							break;
						}
					}
					this_thread::sleep_for(chrono::milliseconds(sleepTime));

					//if (exitToMain) return score; // окончание и выход из игры в меню

					for (size_t i = 0; i < TTRM; i++)
					{
						toPrintGlass.setPoint((newTetramina->getYTetram(i) + yMain), (newTetramina->getXTetram(i) + xMain), randTetr);
						//toPrintGlass.setPoint((mainFigure.getYTetram(i) + yMain), (mainFigure.getXTetram(i) + xMain), mainFigure.getTetramNum());// старый вариант
					};

					system("cls");
					//Draw
					{
						window.clear(Color::White);
						window.draw(background);

						for (int i = 2; i < HightOfGlass; i++)
							for (int j = 0; j < WidthOfGlass; j++)
							{
								//if (field[i][j] == 0) continue;
								if (toPrintGlass.getPoint(i, j) == 0) continue;
								s.setTextureRect(IntRect(toPrintGlass.getColor(i, j) * 18, 0, 18, 18));

								s.setPosition(j * 18, (i - 2) * 18);
								s.move(28, 31); //offset
								window.draw(s);
							}

						for (int i = 0; i < 4; i++)
						{
							s.setTextureRect(IntRect(randNext * 18, 0, 18, 18));
							//s.setTextureRect(IntRect(nextFigure.getTetramNum() * 18, 0, 18, 18));// старый вариант
							s.setPosition(nextTetramina->getXTetram(i) * 18, nextTetramina->getYTetram(i) * 18);
							s.move(240, 72); //offset
							window.draw(s);
						}

						window.draw(frame);
						window.display();

					}
					//end draw

				}

				for (size_t i = 0; i < TTRM; i++)
				{
					collapse = mainGlass.getPoint((newTetramina->getYTetram(i) + yMain) + 1, (newTetramina->getXTetram(i) + xMain))
						|| (newTetramina->getYTetram(i) + yMain >= HightOfGlass);
					if (collapse == true)	break;
				}

				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass;

			score += mainGlass.delLine();//удаление линии если необходимо плюс запись очков

		} while (yMain);
		return score;
	}
}

