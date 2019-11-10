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
	int randTetr = 0, randNext = rand() % 7, tetrAn = 0;// ������
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
		Glass toPrintGlass; //��������� ������

		do
		{
			randTetr = randNext;//������� ������
			randNext = rand() % 7; //��������� ������			

			level = score / 1000 + 1;// ������ ������ 1000 ����� +1 - �������� � �������

			sleepTime = 101 - (level * 10) * (level <= 10) - 100 * (level > 10);//�������� ���� ����� �������� ����������� 

			int xMain = 0, xTmp = 0;// ��������� �������� ������
			bool collapse = false;

			Tetramina mainFig(randTetr);  // ������ ��������
			Tetramina nextFig(randNext); // ������ ��������� (� ������)
			Tetramina spareFig(randTetr);  // ������ ��������		

			for (yMain = 0; yMain < HightOfGlass; yMain++)//���� ��������� ������
			{
				float time1 = 0;// ����� � �������������
				clock.restart(); //������������� ����� ��������	

				do
				{
					time1 = clock.getElapsedTime().asMicroseconds();// ��������� ����� ��������						

					toPrintGlass = mainGlass; // ��������� �������� �� ���������� ������� ����� ����� �����			

					spareFig = mainFig; // ��������� �������� �� �� ��������� ������		

					xTmp = xMain;//��������� � �� ������ ���������� �����-������

					Event anyEvent;
					while (window.pollEvent(anyEvent))
					{
						if (anyEvent.type == Event::Closed)// �������� ���� � ����� ����
						{
							window.close();
							return 0;
						}

						/* ������ */

						if (anyEvent.type == Event::KeyPressed)
							if (anyEvent.key.code == Keyboard::Up)
							{														
								mainFig.transform();//������� ������		
							};

						if (Keyboard::isKeyPressed(Keyboard::Left)) xMain = xMain - 1; //����	
						if (Keyboard::isKeyPressed(Keyboard::Right)) xMain = xMain + 1; //����� 
						if (Keyboard::isKeyPressed(Keyboard::Down)) sleepTime = 1; // �������
					}
					for (size_t i = 0; i < TTRM; i++) // �������� ������������ �������������� 
					{
						collapse = mainGlass.getPoint((mainFig.getYTetram(i) + yMain), (mainFig.getXTetram(i) + xMain))
							|| (mainFig.getXTetram(i) + xMain >= WidthOfGlass)
							|| (mainFig.getXTetram(i) + xMain < 0);
						if (collapse == true) // �������� ����� ���� ���� ����������� �� �����
						{
							xMain = xTmp;
							mainFig = spareFig;
							collapse = false;
							break;
						}
					}
					
					for (size_t i = 0; i < TTRM; i++)// ������ �������� �� ���� ��� ������
					{
						toPrintGlass.setPoint((mainFig.getYTetram(i) + yMain), (mainFig.getXTetram(i) + xMain), randTetr);
					};

					for (size_t i = 0; i < TTRM; i++)// �������� ������������ ������������
					{
						collapse = mainGlass.getPoint((mainFig.getYTetram(i) + yMain) + 1, (mainFig.getXTetram(i) + xMain))
							|| (mainFig.getYTetram(i) + yMain >= HightOfGlass - 1);// ������ +1 ������  

						if (collapse == true)	break; // ������������� ��� ������-�� ������������
					}

					
					//Draw
					{
						window.clear(Color::White);
						window.draw(background);

						for (int i = 2; i < HightOfGlass; i++) // �������� ������, ����� � ����� 2
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
						for (int i = 0; i < 4; i++) // ��������� ������, �����
						{
							s.setTextureRect(IntRect(randNext * 18, 0, 18, 18));
							s.setPosition(nextFig.getXTetram(i) * 18, nextFig.getYTetram(i) * 18);
							s.move(220, 65); //offset
							window.draw(s);
						}
						window.draw(frame);

						Font font;//����� 
						font.loadFromFile("images/trebucbd.ttf");//  ���� ������
						Text text("", font, 20);// ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);

						text.setString(to_string(score));//������ ������ ������
						text.setPosition(240, 20);//������� ������
						window.draw(text);

						window.display();
					}
					//end draw

				} while (time1 < 6000 * sleepTime);// �������� (����� ����������� �����������)

				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass;

			score += mainGlass.delLine();//�������� ����� ���� ���������� ���� ������ �����

		} while (yMain != 0);
		return score;
	}
}
