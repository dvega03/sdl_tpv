#include "Font.h"

Font::Font() {};

Font::Font(const char* filename, int size)
{
	load(filename, size);
}

bool Font::load(const char* filename, int size)
{
	font = TTF_OpenFont(filename, size);

	if (font == nullptr) return false;
	else return true;
}

void Font::clean()
{
	if (font != nullptr) TTF_CloseFont(font);
	font = nullptr;
}


SDL_Surface* Font::generateSurface(const char* text, SDL_Color color) const
{
	return TTF_RenderText_Solid(font, text, color);
}
