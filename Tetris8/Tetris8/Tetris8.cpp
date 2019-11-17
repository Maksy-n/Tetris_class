#include "Tetramina.h"
#include "Draw.h"

int main()
{
	int score = 0;
	int level = 0;
	int yMain = 0;
	unsigned int sleepTime = 105;
	
	Draw show; //�������� SFML

	while (show.window.isOpen()) // ������� ����
	{
		Glass mainGlass;	//�������� ������, ��� �������� ���������� ������
		Glass toPrintGlass; //��������� ������

		Tetramina mainFig(rand() % 7);  // ������ ��������
		Tetramina spareFig(0);  // ������ �������� (0) ������ ������ ��������	
		do
		{
			Tetramina nextFig(rand() % 7); // ������ ��������� (� ������)		

			level = score / 1000 + 1;// ������ ������ 1000 ����� +1 - �������� � �������

			sleepTime = 101 - (level * 10) * (level <= 10) - 100 * (level > 10);//�������� ���� ����� �������� ����������� 

			int xMain = 2, xTmp = 2;// ��������� �������� ������

			bool collapse = false;

			for (yMain = 0; yMain < HightOfGlass; yMain++)//���� ��������� ������
			{
				float time1 = 0;// ����� � �������������
				show.clock.restart(); //������������� ����� ��������	

				do // ���� ���� ����� ������
				{
					time1 = show.clock.getElapsedTime().asMicroseconds();// ��������� ����� ��������						

					toPrintGlass = mainGlass; // ��������� �������� �� ���������� ������� ����� ����� �����			

					spareFig = mainFig; // ��������� �������� �� �� ��������� ������		

					xTmp = xMain;//��������� � �� ������ ���������� �����-������

					Event anyEvent; //������� SFML
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
						toPrintGlass.setPoint((mainFig.getYTetram(i) + yMain), (mainFig.getXTetram(i) + xMain), mainFig.getColor());
					};

					for (size_t i = 0; i < TTRM; i++)// �������� ������������ ������������
					{
						collapse = mainGlass.getPoint((mainFig.getYTetram(i) + yMain) + 1, (mainFig.getXTetram(i) + xMain))
							|| (mainFig.getYTetram(i) + yMain >= HightOfGlass - 1);// ������ +1 ������  

						if (collapse == true)	break; // ������������� ��� ������-�� ������������
					}

					//��������� �� ������
					show.Cls();
					show.OnScreen(toPrintGlass);
					show.OnScreen(nextFig, nextFig.getColor());
					show.OnScreen(score);
					show.ShowOn();

				} while (time1 < 6000 * sleepTime);// �������� (����� ����������� �����������)

				if (collapse == true)	break;
			}
			mainGlass = toPrintGlass; // ������� �� �������� ������� � ��������, ����� ���� ��� ������ ������������
			mainFig = nextFig; //����������� ��������� ������ � ������ ����� ����� �����
			score += mainGlass.delLine();//�������� ����� ���� ����������, ���� ������ �����

		} while (yMain != 0);
		return score;
	}
}
