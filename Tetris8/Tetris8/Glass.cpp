#include "Tetramina.h"


bool Glass::getPoint(int Y, int X)
{
	return theGlass[Y][X].point;
}
int Glass::getColor(int Y, int X)
{
	return theGlass[Y][X].color;
}

void Glass::setPoint(int Y, int X, int setColor)
{
	theGlass[Y][X].point = true;
	theGlass[Y][X].color = setColor;
}

int Glass::delLine() // удаление линий
{
	bool delLine = false;
	int scoreTmp = 0;
	do
	{
		delLine = false;
		for (int i = HightOfGlass - 1; i > 1; i--)
		{
			scoreTmp = scoreTmp + scoreTmp * (int)delLine + 100 * (int)delLine;//подсчёт счёта по хитрой формуле
			for (size_t j = 0; j < WidthOfGlass; j++)
			{
				if (theGlass[i][j].point == 0)
				{
					delLine = false;
					break;
				}
				else
				{
					delLine = true;
				}
			}
			if (delLine == true)
			{
				for (int k = i; k > 1; k--) {
					for (size_t l = 0; l < WidthOfGlass; l++)
						theGlass[k][l] = theGlass[k - 1][l];
				}
				i++;
			}
		}
	} while (delLine == true);

	return scoreTmp;// счёт
};

