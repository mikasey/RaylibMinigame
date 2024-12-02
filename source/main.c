#include <raylib.h>



int main(int argc, char** argv) {
	const int screenWidth = 1280;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "Raylib main window");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(SKYBLUE);

			const char* text = "Text";
			float fontSize = 20;
			Vector2 textSize = MeasureTextEx(GetFontDefault(), "Text", fontSize, 0);
			
			DrawText("Text", screenWidth/2 - textSize.x/2, screenHeight/2 - textSize.y/2, fontSize, DARKBLUE);
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}