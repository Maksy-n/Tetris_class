#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFML/Graphics/Rect.hpp"
#include <string>
#include "Tetramina.h"

using namespace sf;

extern const int HightOfGlass ;
extern const int WidthOfGlass;
extern const int TTRM;

class Draw :public RenderWindow
{

public:
	Draw();
	void Cls();
	void OnScreen(Glass&);
	void OnScreen(Tetramina&, int);
	void OnScreen(int);
	void ShowOn();
	~Draw();

	RenderWindow window;
	Texture t1, t2, t3;
	Sprite s, background, frame;
	Clock clock;
	

};

