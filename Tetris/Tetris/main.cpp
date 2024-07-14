#include <raylib.h>
#include <iostream>
#include "Game.h"
#include "Colors.h"

double lastUpdateTime = 0;

// creating a time delay for the blocks to fall down automatically
bool eventTriggered(double interval) {

	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {

		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main() {

	const int screenWidth = 520;
    const int screenHeight = 620;

	// initiating the game window and setting the fps
	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);

	//Loading an external font
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

	Game game = Game();

	//Main game loop
	while (!WindowShouldClose()) {

		UpdateMusicStream(game.music);

		game.handleInput();
		
		// Implementing the time delay
		if (eventTriggered(0.2)) {

			game.moveBlockDown();
		}
		
		BeginDrawing();
		
		ClearBackground(darkBlue);
		
		DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
		
		DrawTextEx(font, "Next", { 375, 175 }, 38, 2, WHITE);
		
		if (game.gameOver) {

			DrawTextEx(font, "GAME OVER!", { 320, 450 }, 38, 2, WHITE);
		}
		
		DrawRectangleRounded({ 330, 55, 170, 60 }, 0.3, 6, lightBlue);

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textsize = MeasureTextEx(font, scoreText, 38, 2);
		DrawTextEx(font, scoreText, { 330 + (170 - textsize.x) / 2, 65}, 38, 2, WHITE);
		
		DrawRectangleRounded({ 330, 215, 170, 180 }, 0.3, 6, lightBlue);

		game.draw();
		
		EndDrawing();

	}

	//closing the game window.
	CloseWindow();
	return 0;
}