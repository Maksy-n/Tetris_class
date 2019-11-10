#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFML/Graphics/Rect.hpp"
#include <iostream>
#include <string>

#include "Tetramina.h"

using namespace std;
using namespace sf;

int main() 
{
	int score = 0;
	int level = 0;
	int randTetr = 0, randNext = rand() % 7, tetrAn = 0;// фигура
	int yMain = 0;
	unsigned int sleepTime = 105;
	bool exitToMain = false;

	RenderWindow window(VideoMode(300, 420), "Tetris");

	Texture t1, t2, t3;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");

	Sprite s(t1), background(t2), frame(t3);

	Clock clock;

	while (window.isOpen())
	{
		Glass mainGlass;
		Glass toPrintGlass; //временный стакан

		do
		{
			randTetr = randNext;//текущая фигура
			randNext = rand() % 7; //следующая фигура			

			level = score / 1000 + 1;// размер уровня 1000 очков +1 - начинаем с первого

			sleepTime = 101 - (level * 10) * (level <= 10) - 100 * (level > 10);//скорость игры время задержки подобранное 

			int xMain = 0, xTmp = 0;// начальное положене фигуры
			bool collapse = false;

			Tetramina mainFig(randTetr);  // фигура основная
			Tetramina nextFig(randNext); // фигура следующая (в окошке)
			Tetramina spareFig(randTetr);  // фигура хранения		

			for (yMain = 0; yMain < HightOfGlass; yMain++)//цикл опускания фигуры
			{
				float time1 = 0;// время в микросекундах
				clock.restart(); //перезагружает время задержки	

				do
				{
					time1 = clock.getElapsedTime().asMicroseconds();// фиксирует время задержки						

					toPrintGlass = mainGlass; // переносит значения из временного стакана перед новым ходом			

					spareFig = mainFig; // переносит значения из во временную фигуру		

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
								mainFig.transform();//поворот фигуры		
							};

						if (Keyboard::isKeyPressed(Keyboard::Left)) xMain = xMain - 1; //лево	
						if (Keyboard::isKeyPressed(Keyboard::Right)) xMain = xMain + 1; //право 
						if (Keyboard::isKeyPressed(Keyboard::Down)) sleepTime = 1; // падение
					}
					for (size_t i = 0; i < TTRM; i++) // проверка столкновений горизонтальная 
					{
						collapse = mainGlass.getPoint((mainFig.getYTetram(i) + yMain), (mainFig.getXTetram(i) + xMain))
							|| (mainFig.getXTetram(i) + xMain >= WidthOfGlass)
							|| (mainFig.getXTetram(i) + xMain < 0);
						if (collapse == true) // отменяет сдвиг если есть припятствия по бокам
						{
							xMain = xTmp;
							mainFig = spareFig;
							collapse = false;
							break;
						}
					}
					
					for (size_t i = 0; i < TTRM; i++)// вносит значения на слой для печати
					{
						toPrintGlass.setPoint((mainFig.getYTetram(i) + yMain), (mainFig.getXTetram(i) + xMain), randTetr);
					};

					for (size_t i = 0; i < TTRM; i++)// проверка столкновения вертикальная
					{
						collapse = mainGlass.getPoint((mainFig.getYTetram(i) + yMain) + 1, (mainFig.getXTetram(i) + xMain))
							|| (mainFig.getYTetram(i) + yMain >= HightOfGlass - 1);// фигура +1 клетка  

						if (collapse == true)	break; // останавливает при первом-же столкновении
					}

					
					//Draw
					{
						window.clear(Color::White);
						window.draw(background);

						for (int i = 2; i < HightOfGlass; i++) // основной стакан, старт с линии 2
						{
							for (int j = 0; j < WidthOfGlass; j++)
							{
								if (toPrintGlass.getPoint(i, j) == 0) continue;

								s.setTextureRect(IntRect(toPrintGlass.getColor(i, j) * 18, 0, 18, 18));
								s.setPosition(j * 18, (i - 2) * 18);
								s.move(30, 31); //offset
								window.draw(s);
							}
						}
						for (int i = 0; i < 4; i++) // следующая фигура, сбоку
						{
							s.setTextureRect(IntRect(randNext * 18, 0, 18, 18));
							s.setPosition(nextFig.getXTetram(i) * 18, nextFig.getYTetram(i) * 18);
							s.move(220, 65); //offset
							window.draw(s);
						}
						window.draw(frame);

						Font font;//шрифт 
						font.loadFromFile("images/trebucbd.ttf");//  файл шрифта
						Text text("", font, 20);// объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);

						text.setString(to_string(score));//задает строку тексту
						text.setPosition(240, 20);//позицию текста
						window.draw(text);

						window.display();
					}
					//end draw

				} while (time1 < 6000 * sleepTime);// задержка (число подбирается произвольно)

				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass;

			score += mainGlass.delLine();//удаление линии если необходимо плюс запись очков

		} while (yMain != 0);
		return score;
	}
}
