#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "GameWindow.h"

class Texture
{
public:
	Texture();
	~Texture();

	// Loads image at specified path
	bool loadFromFile(std::string path);

	// Creates image from font string 
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	// Renders texxture at given point
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture* mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};

#endif // !TEXTURE_H