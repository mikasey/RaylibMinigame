#include <string>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


class Game{
private:
// Window properties
	const char* win_name = "Game!!!";
	int win_width = 800, win_height = 600, win_target_fps = 60;

// Camera properties
	Vector3 camera_pos{0, 0, 0};
	Vector3 camera_rot{0, 0, 0};
	float camera_zoom = 1.f;

// Texture resources
	class Textures{
	public:
		const char* folder = "assets/textures/";
		enum{
			no_texture = 0,
			cat,
			heart,
			count
		};
		const char* texture_names[count]{
			"null_texture.png",
			"cat.png",
			"uwu_heart.png"
		};
		Texture2D* game_textures = nullptr;
	}Textures;

// Audio resources
	class Sounds{
	public:
		const char* folder = "assets/sounds/";
		enum{
			test_sound = 0,
			oof,
			count
		};
		const char* sound_names[count]{
			"test.ogg",
			"OOF.ogg"
		};
		Sound* game_sounds = nullptr;
	}Sounds;

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
		Textures.game_textures = new Texture2D[Textures::count];
		Sounds.game_sounds = new Sound[Sounds::count];

		for(int i = 0; i < Sounds::count; i++){
			file_name = Sounds.folder;
			Sounds.game_sounds[i] = LoadSound((file_name + Sounds.sound_names[i]).c_str());
		}
		for(int i = 0; i < Textures::count; i++){
			file_name = Textures.folder;
			Textures.game_textures[i] = LoadTexture((file_name + Textures.texture_names[i]).c_str());
		}

		PlaySound(Sounds.game_sounds[Sounds::oof]);
	}

	void UnloadResources(){
	// Unload all sounds
		for(int i = 0; i < Sounds::count; i++){
			UnloadSound(Sounds.game_sounds[i]);
		}
	// Unload all Texture2D
		for(int i = 0; i < Textures::count; i++){
			UnloadTexture(Textures.game_textures[i]);
		}

		delete[] Textures.game_textures;
		delete[] Sounds.game_sounds;
	}

	void GameLoop(){
		while(!WindowShouldClose()){
			// PullEvents();

			if(IsKeyPressed(KEY_SPACE)) {
				PlaySound(Sounds.game_sounds[Sounds::test_sound]);
			}

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
			const int texture_x = screen_width / 2 - Textures.game_textures[Textures::heart].width / 2;
			const int texture_y = screen_height / 2 - Textures.game_textures[Textures::heart].height / 2;
			DrawTexture(Textures.game_textures[Textures::cat], screen_width - Textures.game_textures[Textures::cat].width, screen_height - Textures.game_textures[Textures::cat].height, WHITE);
			DrawTexture(Textures.game_textures[Textures::heart], texture_x, texture_y, WHITE);
			const char* text = "OMG! IT WORKS!";
			const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
			DrawText(text, screen_width / 2 - (int)(text_size.x) / 2, texture_y + Textures.game_textures[Textures::heart].height + (int)(text_size.y), 20, BLACK);


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
