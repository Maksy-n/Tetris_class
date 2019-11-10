#pragma once

 const int HightOfGlass = 22;
 const int WidthOfGlass = 10;
 const int TTRM = 4;

class Tetramina // фигуры
{
private:
	int transformVal = 0;
	int transformTmp = 0;
	int *tetramina;

public:
	Tetramina(int numOfFigure);	
	int getXTetram(int numOfVal);
	int getYTetram(int numOfVal);
	void transform();
	void operator=(const Tetramina &other);
	~Tetramina();
};

class TetraminaVirtual // шаблоны
{
public:
	int tetramAngle = 0;
	int *tetraminaTempl;
	TetraminaVirtual(int figureNum);


	~TetraminaVirtual();
};

class Glass // стакан
{
private:
	struct GlassStuct // элементы стакана
	{
		bool point = 0;
		int color = 0;
	};
	GlassStuct theGlass[HightOfGlass][WidthOfGlass];

public:	
	bool getPoint(int Y, int X);
	int getColor(int Y, int X);
	void setPoint(int Y, int X, int setColor);
	int delLine();
};
