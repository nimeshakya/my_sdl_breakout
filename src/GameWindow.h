#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

constexpr int SCREEN_WIDTH{ 640 };
constexpr int SCREEN_HEIGHT{ 480 };
constexpr int UNIT_LEN{ 15 };
constexpr int BRICK_LEN{ 58 };

// Global Golour for game objects
namespace GameObjColor
{
	constexpr Uint8 BG_RED{ 0x2B };
	constexpr Uint8 BG_GREEN{ 0x2B };
	constexpr Uint8 BG_BLUE{ 0x2B };

	constexpr Uint8 OB_RED{ 0xD2 };
	constexpr Uint8 OB_GREEN{ 0xD2 };
	constexpr Uint8 OB_BLUE{ 0xD2 };

	constexpr Uint8 BRICK_0_RED{ 0x8a };
	constexpr Uint8 BRICK_0_GREEN{ 0x8a };
	constexpr Uint8 BRICK_0_BLUE{ 0xFF };

	constexpr Uint8 BRICK_1_RED{ 0x00 };
	constexpr Uint8 BRICK_1_GREEN{ 0xFF };
	constexpr Uint8 BRICK_1_BLUE{ 0x00 };

	constexpr Uint8 BRICK_2_RED{ 0xFF };
	constexpr Uint8 BRICK_2_GREEN{ 0xFF };
	constexpr Uint8 BRICK_2_BLUE{ 0x00 };
	
	constexpr Uint8 BRICK_3_RED{ 0xF7 };
	constexpr Uint8 BRICK_3_GREEN{ 0x5D };
	constexpr Uint8 BRICK_3_BLUE{ 0x1E };

	constexpr Uint8 BRICK_4_RED{ 0xFF };
	constexpr Uint8 BRICK_4_GREEN{ 0x00 };
	constexpr Uint8 BRICK_4_BLUE{ 0x00 };
}

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

#endif // !GAMEWINDOW_H