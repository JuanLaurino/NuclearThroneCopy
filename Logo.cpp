#include "Logo.h"
#include "Video.h"
#include "Main.h"

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
	Video::getInstance()->renderGraphic(_spriteID, (WIN_WIDTH - 431) / 2, (WIN_HEIGHT - 145) / 2, 421, 145, 0, 145); // Logo Fondo
	Video::getInstance()->renderGraphic(_spriteID, (WIN_WIDTH - 421) / 2, (WIN_HEIGHT - 145) / 2, 421, 145, 0, 0); // Logo basico

}
