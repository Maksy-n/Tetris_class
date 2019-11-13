#include "Tetramina.h"


Tetramina::Tetramina(int numOfFigure) // фигура
{
	TetraminaVirtual figure(numOfFigure); // создаёт на основе шаблона
	transformVal = figure.tetramAngle;
	tetramina = new int[transformVal * TTRM * 2];

	for (size_t i = 0; i < transformVal * TTRM * 2; i++)
	{
		tetramina[i] = figure.tetraminaTempl[i];
	}
};

int Tetramina::	getXTetram(int numOfVal) 
{
	int ix = transformTmp * TTRM * 2 + numOfVal;
	return tetramina[ix];
};

int Tetramina::getYTetram(int numOfVal)
{
	int iy = transformTmp * TTRM * 2 + numOfVal + 4;
	return tetramina[iy];
};

void Tetramina::transform() // поворот
{
	transformTmp = (transformTmp + 1) % transformVal;
};

void Tetramina::	operator=(const Tetramina &other)
{
	this->transformTmp = other.transformTmp;
	this->transformVal = other.transformVal;
	if (this->tetramina != nullptr)
	{
		delete[]this->tetramina;
	}
	this->tetramina = new int[other.transformVal * TTRM * 2];
	for (size_t i = 0; i < (other.transformVal * TTRM * 2); i++)
	{
		this->tetramina[i] = other.tetramina[i];
	}
};

Tetramina::~Tetramina()
{
	delete [] tetramina;
}

TetraminaVirtual::TetraminaVirtual(int figureNum) //шаблоны фигур
{
	switch (figureNum)
	{
	case 0: //O
	{
		tetramAngle = 1;// колличество возможных вариантов фигуры
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 2, 2, 3, 3, 2, 3, 3, 2 }; // фигура (X,X,X,X,Y,Y,Y,Y...)
	}break;

	case 1: // T
	{
		tetramAngle = 4;
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 1, 2, 3, 2, 2, 2, 2, 3,
														2, 2, 2, 1, 1, 2, 3, 2,
														1, 2, 3, 2, 2, 2, 2, 1,
														2, 2, 2, 3, 1, 2, 3, 2 };
	}break;

	case 2: //I
	{
		tetramAngle = 2;
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 2, 2, 2, 2, 0, 1, 2, 3 ,
														3, 2, 1, 0, 2, 2, 2, 2 };
	}break;

	case 3: //L
	{
		tetramAngle = 4;
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 1, 2, 3, 1, 1, 1, 1, 2,
														2, 3, 3, 3, 1, 1, 2, 3,
														1, 2, 3, 3, 3, 3, 3, 2,
														1, 1, 1, 2, 1, 2, 3, 3 };
	}break;

	case 4: // J
	{
		tetramAngle = 4;
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 1, 2, 3, 3, 1, 1, 1, 2,
														2, 3, 3, 3, 3, 3, 2, 1,
														1, 2, 3, 1, 3, 3, 3, 2,
														1, 1, 1, 2, 1, 2, 3, 1 };
	}break;

	case 5: //S
	{
		tetramAngle = 2;
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 1, 2, 2, 3, 3, 3, 2, 2 ,
														1, 1, 2, 2, 1, 2, 2, 3 };
	}break;
	case 6: //Z
	{
		tetramAngle = 2;
		tetraminaTempl = new int[TTRM * 2 * tetramAngle]{ 1, 2, 2, 3, 2, 2, 3, 3 ,
														2, 2, 3, 3, 3, 2, 2, 1 };
	}break;
	default:
		break;
	}
};
TetraminaVirtual::~TetraminaVirtual()
{
	delete[]tetraminaTempl;
}

