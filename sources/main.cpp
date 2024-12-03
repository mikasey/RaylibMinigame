#include <string>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


class Game{
private:
	const char* win_name = "Game!!!";
	int win_width = 800, win_height = 600, win_target_fps = 60;

	Vector3 camera_pos{0, 0, 0};
	Vector3 camera_rot{0, 0, 0};
	float camera_zoom = 1.f;

// resources
	const char* assets_folder = "assets/";
	enum {
		TEX_NULL = 0,
		TEX_CAT,
		TEX_HEART,
		TEXTURES_COUNT
	};
	const char* texture_names[TEXTURES_COUNT]{
		"textures/null_texture.png",
		"textures/cat.png",
		"textures/uwu_heart.png"
	};

	Texture2D* game_textures;

public:
	Game(){
	// Startup
		InitWindow(win_width, win_height, win_name);
		SetTargetFPS(win_target_fps);
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		SetWindowMinSize(240, 144);
		SetWindowMaxSize(1280, 720);
		Image icon = LoadImage("assets/Raylib_logo.png");
		TraceLog(LOG_WARNING, "Icon is in format %x", icon.format);
		SetWindowIcon(icon);
		SetExitKey(NULL);
		InitAudioDevice();

	// Loading stuff
		LoadResources();
	}

	void LoadResources(){
		std::string file_name;
		game_textures = new Texture2D[TEXTURES_COUNT];

		for(int i = 0; i < TEXTURES_COUNT; i++){
			file_name = assets_folder;
			game_textures[i] = LoadTexture((file_name + texture_names[i]).c_str());
		}
	}

	void UnloadResources(){
	// Unload all Texture2D from game_textures
		for(int i = 0; i < TEXTURES_COUNT; i++){
			UnloadTexture(game_textures[i]);
		}

		delete[] game_textures;
	}

	void GameLoop(){
		while(!WindowShouldClose()){
			// PullEvents();

			DrawAll();

			// ManageTime();
		}
	}

	void PullEvents(){
		PollInputEvents();
	}

	void DrawAll(){
		char fps_str[32] = {};
		sprintf(fps_str, "FPS: %i/%i", GetFPS(), win_target_fps);
		int screen_width = GetScreenWidth(), screen_height = GetScreenHeight();

		BeginDrawing();
		{
			ClearBackground(RAYWHITE);
			const int texture_x = screen_width / 2 - game_textures[TEX_HEART].width / 2;
			const int texture_y = screen_height / 2 - game_textures[TEX_HEART].height / 2;
			DrawTexture(game_textures[TEX_CAT], screen_width - game_textures[TEX_CAT].width, screen_height - game_textures[TEX_CAT].height, WHITE);
			DrawTexture(game_textures[TEX_HEART], texture_x, texture_y, WHITE);
			const char* text = "OMG! IT WORKS!";
			const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
			DrawText(text, screen_width / 2 - (int)(text_size.x) / 2, texture_y + game_textures[TEX_HEART].height + (int)(text_size.y), 20, BLACK);


			GuiEnable();
			{
				GuiLabel({10, 10, 120, 20}, fps_str);

			}
			GuiDisable();
		}
		EndDrawing();
	}

	void ManageTime(){
		SwapScreenBuffer();
	}

	~Game(){
		UnloadResources();

		CloseAudioDevice();
		CloseWindow();
	}
};

int main(){

	Game* game = new Game();;

	game->GameLoop();

	delete game;

	return 0;
}
