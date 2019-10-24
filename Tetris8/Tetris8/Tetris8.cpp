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

class TetraminaVirtual
{
public:
	virtual int getXTetram(int i) = 0;

	virtual int getYTetram(int i) = 0;

	virtual void transform() = 0;

};

/*описание точек фигуры:
в квадрате 4х4 по 4. Сначала 4 X, потом 4 Y  и снова. {2, 3 ... 0, 3 } */
class OTetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
	}

	void transform() override //функция поворота
	{
		tetramAngle;
	};
private:
	int tetramAngle = 0;
	int tetramina[1][TTRM * 2] = { 2, 2, 3, 3, 2, 3, 3, 2 };
};

class TTetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
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

class ITetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 2;
	};
private:
	int tetramAngle = 0;
	int tetramina[2][TTRM * 2] = { 2, 2, 2, 2, 0, 1, 2, 3 ,
									3, 2, 1, 0, 2, 2, 2, 2 };
};

class LTetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 4;
	};
private:
	int tetramAngle = 0; // переменная поворота
	int tetramina[4][TTRM * 2] = { 1, 2, 3, 1, 1, 1, 1, 2,
									2, 3, 3, 3, 1, 1, 2, 3,
									1, 2, 3, 2, 3, 3, 3, 4,
									1, 1, 1, 2, 1, 2, 3, 3 };
}; 

class JTetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 4;
	};
private:
	int tetramAngle = 0; // переменная поворота
	int tetramina[4][TTRM * 2] = { 1, 2, 3, 3, 1, 1, 1, 2,
									2, 3, 3, 4, 3, 3, 2, 1,
									1, 2, 3, 2, 1, 1, 1, 2,
									1, 1, 1, 2, 1, 2, 3, 3 };
};
class STetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 2;
	};
private:
	int tetramAngle = 0;
	int tetramina[2][TTRM * 2] = { 1, 2, 2, 3, 3, 3, 2, 2 ,
									1, 1, 2, 2, 1, 2, 2, 3 };
};

class ZTetramina : public TetraminaVirtual
{
public:

	int getXTetram(int i) override // получение значения X
	{
		return tetramina[tetramAngle][i];
	}
	int getYTetram(int i)override  // получение значения Y
	{
		return tetramina[tetramAngle][i + 4];
	}

	void transform() override //функция поворота
	{
		tetramAngle = (tetramAngle + 1) % 2;
	};
private:
	int tetramAngle = 0;
	int tetramina[2][TTRM * 2] = { 1, 2, 2, 3, 2, 2, 3, 3 ,
									2, 2, 3, 3, 3, 2, 2, 1 };
};


class Tetramina
{
public:
	TetraminaVirtual* tmp;

	Tetramina(int figureNum)
	{
		switch (figureNum)
		{
		case 0: //O
		{
			tmp = &oTetramina;
		}break;

		case 1: // T
		{
			tmp = &tTetramina;
		}break;

		case 2: //I
		{
			tmp = &iTetramina;
		}break;
		case 3: //L
		{
			tmp = &lTetramina;
		}break;

		case 4: // J
		{
			tmp = &jTetramina;
		}break;

		case 5: //S
		{
			tmp = &sTetramina;
		}break;
		case 6: //Z
		{
			tmp = &zTetramina;
		}break;
		default:
			break;
		}
	};

private:
	OTetramina oTetramina;
	TTetramina tTetramina;
	ITetramina iTetramina;
	LTetramina lTetramina;
	JTetramina jTetramina;
	STetramina sTetramina; 
	ZTetramina zTetramina;
	
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

	int delLine() // удаление линий
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
					for (int k = i; k > 1; k--) {
						for (size_t l = 0; l < WidthOfGlass; l++)
							theGlass[k][l] = theGlass[k - 1][l];
					}
					i++;
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
		Glass mainGlass;
		Glass toPrintGlass;
		do
		{
			randTetr = randNext;//текущая фигура
			randNext = rand() % 7; //следующая фигура			

			level = score / 1000 + 1;// размер уровня 1000 очков +1 - начинаем с первого

			sleepTime = 101 - (level * 10) * (level <= 10) - 100 * (level > 10);//скорость игры время задержки подобранное 

			//scoreLevel(tetramNext.part, score, level);//печать элементов////

			int xMain = 0, xTmp = 0;// начальное положене фигуры
			bool collapse = false;

			Tetramina mainFig(randTetr);  // фигура основная
			Tetramina nextFig(randNext); // фигура следующая (в окошке)
			Tetramina spareFig(randTetr);  // фигура хранения		

			for (yMain = 0; yMain < HightOfGlass; yMain++)//цикл опускания фигуры
			{
				toPrintGlass = mainGlass; // переносим значения из временного стакана перед новым ходом

				for (size_t i = 0; i < 3; i++) //колличество нажатий на кнопки за одну иттерацию
				{
					spareFig = mainFig;

					xTmp = xMain;//временная х на случай наползания слева-справа

					Event anyEvent;
					while (window.pollEvent(anyEvent))
					{
						if (anyEvent.type == Event::Closed)// закрытие окна и конец игры
						{
							window.close();
							return 0;
						}

						/* кнопки */

						if (anyEvent.type == Event::KeyPressed)
							if (anyEvent.key.code == Keyboard::Up)
							{
								//поворот фигуры								
								mainFig.tmp->transform();
							};

						if (Keyboard::isKeyPressed(Keyboard::Left)) xMain = xMain - 1; //лево	
						if (Keyboard::isKeyPressed(Keyboard::Right)) xMain = xMain + 1; //право 
						if (Keyboard::isKeyPressed(Keyboard::Down)) sleepTime = 1; // падение
					}
					for (size_t i = 0; i < TTRM; i++) // проверка столкновений горизонтальная 
					{
						collapse = mainGlass.getPoint((mainFig.tmp->getYTetram(i) + yMain), (mainFig.tmp->getXTetram(i) + xMain))
							|| (mainFig.tmp->getXTetram(i) + xMain >= WidthOfGlass)
							|| (mainFig.tmp->getXTetram(i) + xMain < 0);
						if (collapse == true) // отменяем сдвиг если есть припятствия по бокам
						{
							xMain = xTmp;
							mainFig = spareFig;
							collapse = false;
							break;
						}
					}
					this_thread::sleep_for(chrono::milliseconds(sleepTime)); // задержка

					//if (exitToMain) return score; // окончание и выход из игры в меню

					for (size_t i = 0; i < TTRM; i++)
					{
						toPrintGlass.setPoint((mainFig.tmp->getYTetram(i) + yMain), (mainFig.tmp->getXTetram(i) + xMain), randTetr);
					};
				
					//system("cls");
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
							s.setPosition(nextFig.tmp->getXTetram(i) * 18, nextFig.tmp->getYTetram(i) * 18);
							s.move(240, 72); //offset
							window.draw(s);
						}
						window.draw(frame);
						window.display();
					}
					//end draw
				}

				for (size_t i = 0; i < TTRM; i++)// проверка столкновения вертикальная
				{
					collapse = mainGlass.getPoint((mainFig.tmp->getYTetram(i) + yMain) + 1, (mainFig.tmp->getXTetram(i) + xMain)) // фигура +1 клетка  
						|| (mainFig.tmp->getYTetram(i) + yMain >= HightOfGlass - 1);
					if (yMain >= 20) cout << "JJJJ";
					if (collapse == true)	break; // останавливает при первом-же столкновении
				}
				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass;

			score += mainGlass.delLine();//удаление линии если необходимо плюс запись очков

		} while (yMain != 0);
		return score;
	}
}

