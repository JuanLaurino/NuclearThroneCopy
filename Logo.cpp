#include "Logo.h"
#include "Video.h"
#include "KeyDefine.h"

Logo::Logo()
{
}

Logo::~Logo()
{
}

void Logo::update()
{
}

void Logo::render()
{
	Video::getInstance()->renderGraphic(_spriteID, (WIN_WIDTH - 431) / 2, (WIN_HEIGHT - 145) / 2, 421, 145, 0, 145); // Fondo del logo
	Video::getInstance()->renderGraphic(_spriteID, (WIN_WIDTH - 421) / 2, (WIN_HEIGHT - 145) / 2, 421, 145, 0, 0); // Letras del logo

}
