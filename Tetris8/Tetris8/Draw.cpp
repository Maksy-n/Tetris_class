#include "Draw.h"

Draw::Draw()
{
	window.create(VideoMode(300, 420), "Tetris");
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");

	s.setTexture(t1);
	background.setTexture(t2);
	frame.setTexture(t3);	
};

void Draw::Cls()
{
	window.clear(Color::White);
	window.draw(background);
};

void Draw::OnScreen(Glass &toPrintGlass)
{
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
};
	
void Draw::OnScreen(Tetramina &nextFig, int randNext)
{
	for (int i = 0; i < 4; i++) // ��������� ������, �����
	{
		s.setTextureRect(IntRect(randNext * 18, 0, 18, 18));
		s.setPosition(nextFig.getXTetram(i) * 18, nextFig.getYTetram(i) * 18);
		s.move(220, 65); //offset
		window.draw(s);
	}
	window.draw(frame);
};

void Draw::OnScreen(int score)
{
	Font font;//����� 
	font.loadFromFile("images/trebucbd.ttf");//  ���� ������
	Text text("", font, 20);// ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);

	text.setString(std::to_string(score));//������ ������ ������
	text.setPosition(240, 20);//������� ������
	window.draw(text);	
}

void Draw::ShowOn()
{
	window.display();
}

Draw::~Draw()
{
}
