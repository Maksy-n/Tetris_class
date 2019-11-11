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
};
	
void Draw::OnScreen(Tetramina &nextFig, int randNext)
{
	for (int i = 0; i < 4; i++) // следующая фигура, сбоку
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
	Font font;//шрифт 
	font.loadFromFile("images/trebucbd.ttf");//  файл шрифта
	Text text("", font, 20);// объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);

	text.setString(std::to_string(score));//задает строку тексту
	text.setPosition(240, 20);//позицию текста
	window.draw(text);	
}

void Draw::ShowOn()
{
	window.display();
}

Draw::~Draw()
{
}
