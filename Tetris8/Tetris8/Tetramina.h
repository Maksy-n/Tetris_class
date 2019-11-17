#pragma once

const int HightOfGlass = 22; // Высота стакана 22 клетки (20 поле+ 2 скрыты сверху)
const int WidthOfGlass = 10;  // Ширина стакана;
const int TTRM = 4; // "Размер" тетрамины - 4 клетки

class Tetramina // фигуры
{
private:
	int transformVal = 0;
	int transformTmp = 0;
	int *tetramina;
	int numColor;

public:
	Tetramina(int numOfFigure);
	int getXTetram(int numOfVal);
	int getYTetram(int numOfVal);
	void transform();
	void operator=(const Tetramina &);
	int getColor();
	~Tetramina();
};

class TetraminaTemplate // шаблоны фигур
{
	int tetramAngle = 0;
	int *tetraminaTempl;
public:
	TetraminaTemplate(int );
	int GetTetramAngle();
	int *GetTetraminaTempl();
	~TetraminaTemplate();
};

class Glass // стакан
{
private:
	struct GlassStuct // элементы стакана
	{
		bool point = 0;
		int color = 0;
	};
	GlassStuct mainGlass[HightOfGlass][WidthOfGlass];

public:
	bool getPoint(int Y, int X);
	int getColor(int Y, int X);
	void setPoint(int Y, int X, int setColor);
	int delLine();
};


