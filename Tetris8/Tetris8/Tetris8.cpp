#include <iostream>

#include "Tetramina.h"
#include "Draw.h"

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

	Draw show;	
	
	while (show.window.isOpen())
	{
		Glass mainGlass;	//�������� ������, ��� �������� ���������� ������
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
				show.clock.restart(); //������������� ����� ��������	

				do
				{
					time1 = show.clock.getElapsedTime().asMicroseconds();// ��������� ����� ��������						

					toPrintGlass = mainGlass; // ��������� �������� �� ���������� ������� ����� ����� �����			

					spareFig = mainFig; // ��������� �������� �� �� ��������� ������		

					xTmp = xMain;//��������� � �� ������ ���������� �����-������

					Event anyEvent;
					while (show.window.pollEvent(anyEvent))
					{
						if (anyEvent.type == Event::Closed)// �������� ���� � ����� ����
						{
							show.window.close();
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
										
					show.Cls();
					show.OnScreen(toPrintGlass);
					show.OnScreen(nextFig, randNext);				
					show.OnScreen(score);
					show.ShowOn();

				} while (time1 < 6000 * sleepTime);// �������� (����� ����������� �����������)

				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass; // ������� �� �������� ������� � ��������, ����� ���� ��� ������ ������������

			score += mainGlass.delLine();//�������� ����� ���� ���������� ���� ������ �����

		} while (yMain != 0);
		return score;
	}
}
