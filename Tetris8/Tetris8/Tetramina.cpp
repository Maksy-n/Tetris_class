#include "Tetramina.h"

Tetramina::Tetramina(int numOfFigure) // фигура
{
	TetraminaTemplate figure(numOfFigure); // создаёт на основе шаблона
	numColor = numOfFigure;
	transformVal = figure.GetTetramAngle();
	tetramina = new int[transformVal * TTRM * 2];
	int *tmp = figure.GetTetraminaTempl();

	for (size_t i = 0; i < transformVal * TTRM * 2; i++)
	{
		tetramina[i] = tmp[i];
	}
};

int Tetramina::getXTetram(int numOfVal)
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

int Tetramina::getColor()
{
	return numColor;
}

void Tetramina:: operator=(const Tetramina &other)
{
	this->transformTmp = other.transformTmp;
	this->transformVal = other.transformVal;
	this->numColor = other.numColor;
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
	delete[] tetramina;
}

TetraminaTemplate::TetraminaTemplate(int figureNum) //шаблоны фигур
{
	struct Template
	{
		int angle;
		int *templ;
		void operator=(const Template &other)
		{
			if (this->templ != nullptr)
			{
				delete[]this->templ;
			}
			this->templ = new int[other.angle * TTRM * 2];
			for (size_t i = 0; i < (other.angle * TTRM * 2); i++)
			{
				this->templ[i] = other.templ[i];
			}
		}
		~Template()
		{
			delete[] templ;
		}
	};

	Template *figure = new Template[7];

	//O
	figure[0].angle = 1;// колличество возможных вариантов фигуры
	figure[0].templ = new int[TTRM * 2 * figure[0].angle]{ 2, 2, 3, 3, 2, 3, 3, 2 };// фигура (X,X,X,X,Y,Y,Y,Y...)

	// T
	figure[1].angle = 4;
	figure[1].templ = new int[TTRM * 2 * figure[1].angle]{ 1, 2, 3, 2, 2, 2, 2, 3,
															2, 2, 2, 1, 1, 2, 3, 2,
															1, 2, 3, 2, 2, 2, 2, 1,
															2, 2, 2, 3, 1, 2, 3, 2 };
	//I
	figure[2].angle = 2;
	figure[2].templ = new int[TTRM * 2 * figure[2].angle]{ 2, 2, 2, 2, 0, 1, 2, 3 ,
															3, 2, 1, 0, 2, 2, 2, 2 };
	//L
	figure[3].angle = 4;
	figure[3].templ = new int[TTRM * 2 * figure[3].angle]{ 1, 2, 3, 1, 1, 1, 1, 2,
															2, 3, 3, 3, 1, 1, 2, 3,
															1, 2, 3, 3, 3, 3, 3, 2,
															1, 1, 1, 2, 1, 2, 3, 3 };
	// J
	figure[4].angle = 4;
	figure[4].templ = new int[TTRM * 2 * figure[4].angle]{ 1, 2, 3, 3, 1, 1, 1, 2,
															2, 3, 3, 3, 3, 3, 2, 1,
															1, 2, 3, 1, 3, 3, 3, 2,
															1, 1, 1, 2, 1, 2, 3, 1 };
	//S
	figure[5].angle = 2;
	figure[5].templ = new int[TTRM * 2 * figure[5].angle]{ 1, 2, 2, 3, 3, 3, 2, 2 ,
															1, 1, 2, 2, 1, 2, 2, 3 };
	//Z
	figure[6].angle = 2;
	figure[6].templ = new int[TTRM * 2 * figure[6].angle]{ 1, 2, 2, 3, 2, 2, 3, 3 ,
															2, 2, 3, 3, 3, 2, 2, 1 };

	tetramAngle = figure[figureNum].angle;
	tetraminaTempl = new int[TTRM * 2 * tetramAngle];
	for (size_t i = 0; i < TTRM * 2 * tetramAngle; i++)
	{
		tetraminaTempl[i] = figure[figureNum].templ[i];
	}

	delete[]figure;
};

int TetraminaTemplate::GetTetramAngle()
{
	return tetramAngle;
};

int *TetraminaTemplate::GetTetraminaTempl()
{
	return tetraminaTempl;
};

TetraminaTemplate::~TetraminaTemplate()
{
	delete[]tetraminaTempl;
}

