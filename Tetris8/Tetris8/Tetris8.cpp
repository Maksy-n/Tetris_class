#include <iostream>

#include "Tetramina.h"
#include "Draw.h"

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

	Draw show;	
	
	while (show.window.isOpen())
	{
		Glass mainGlass;	//основной стакан, где хранятся предыдущие фигуры
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
				show.clock.restart(); //перезагружает время задержки	

				do
				{
					time1 = show.clock.getElapsedTime().asMicroseconds();// фиксирует время задержки						

					toPrintGlass = mainGlass; // переносит значения из временного стакана перед новым ходом			

					spareFig = mainFig; // переносит значения из во временную фигуру		

					xTmp = xMain;//временная х на случай наползания слева-справа

					Event anyEvent;
					while (show.window.pollEvent(anyEvent))
					{
						if (anyEvent.type == Event::Closed)// закрытие окна и конец игры
						{
							show.window.close();
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
										
					show.Cls();
					show.OnScreen(toPrintGlass);
					show.OnScreen(nextFig, randNext);				
					show.OnScreen(score);
					show.ShowOn();

				} while (time1 < 6000 * sleepTime);// задержка (число подбирается произвольно)

				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass; // перенос из текущего стакана в основной, после того как фигура остановилась

			score += mainGlass.delLine();//удаление линии если необходимо плюс запись очков

		} while (yMain != 0);
		return score;
	}
}
