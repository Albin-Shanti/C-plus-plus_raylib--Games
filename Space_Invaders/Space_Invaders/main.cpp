#include <raylib.h>
#include <string>
#include "Game.h"


std::string formatWithLeadingZeros(int number, int width) {

	std::string numberText = std::to_string(number);
	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}


int main() {

	Color darkBlue = { 14, 16, 23, 225 };
	Color lightGreen = Color{ 94, 252, 3, 255 };
	
	int offset = 50;
	const int screenWidth = 750;
	const int screenHeight = 700;
	

	InitWindow(screenWidth + offset, screenHeight + 2 * offset, "Space Invaders");
	InitAudioDevice();
	
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");
	
	SetTargetFPS(60);

	Game game;


	while (!WindowShouldClose()) {

		UpdateMusicStream(game.music);
		game.handleInputs();
		game.Update();

		BeginDrawing();
		ClearBackground(darkBlue);
		DrawRectangleRoundedLines({ 10, 10, 780, 780 }, 0.18f, 20, 2, lightGreen);
		DrawLineEx({ 25, 730 }, { 775, 730 }, 3, lightGreen);

		if (game.run) {
			
			DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, lightGreen);
		}
		else {

			DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, lightGreen);
		}

		float x = 60.0f;
		for (int i = 0; i < game.lives; i++) {

			DrawTextureV(spaceshipImage, {x, 730}, WHITE);
			x += 60;
		}

		DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, lightGreen);
		std::string scoreText = formatWithLeadingZeros(game.score, 5);
		DrawTextEx(font, scoreText.c_str(), { 50, 40 }, 34, 2, lightGreen);
		
		DrawTextEx(font, "HIGH-SCORE", { 570, 15 }, 34, 2, lightGreen);
		std::string highscoreText = formatWithLeadingZeros(game.highscore, 5);
		DrawTextEx(font, highscoreText.c_str(), { 655, 40 }, 34, 2, lightGreen);

		
		game.Draw();
		EndDrawing();


	}

	CloseWindow();
	CloseAudioDevice();
	return 0;
}

