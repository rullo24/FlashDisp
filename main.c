// std C includes
#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>

// raygui implementation
#define RAYGUI_IMPLEMENTATION
#include "ext/raygui.h"

// user includes
#include "status.h"
#include "utils.h"

#define WINDOW_SIZE_W 500
#define WINDOW_SIZE_H 500
#define MIN_FLASH_HZ 0
#define MAX_FLASH_HZ 100 
#define WIDGET_DEF_W 150
#define WIDGET_DEF_H 30
#define WIDGET_SPACING_H 10
#define TEXT_DEF_FONTSIZE 20

int main() {
	// init basic semi-global vars
	int res = SUCCESS;
	Color background_col = LIGHTGRAY;

	// checking if hardcoded spacing will fit within the screen
	if (WINDOW_SIZE_H <= (2 * WIDGET_DEF_H + 2 * WIDGET_SPACING_H + TEXT_DEF_FONTSIZE + (TEXT_DEF_FONTSIZE/2))) {
		fprintf(stderr, "ERROR: window size is too big for the default widget height\n");
		res = WINDOW_SIZING_ERR;
		goto out_basic;
	}
	int window_centre_h = WINDOW_SIZE_H / 2; 

	// init the window for the app
	InitWindow(WINDOW_SIZE_W, WINDOW_SIZE_H, "FreqDisp");

	// infinite loop unless functions are true
	if (!IsWindowReady()) {
		fprintf(stderr, "ERROR: failed to init the window\n");
		res = NO_INIT_WINDOW_ERR;
		goto out_close_window;
	}

	// init memory for timing purposes
	int usr_val_flash_hz = 0; // screen flashing speed
	double time_between_flashes_s = 0.0; // t[s] = 1 / f[Hz]
	double time_of_last_flash = 0.0;
	double time_since_init = 0.0;

	// variable used for storing background flashing speed (for print to GUI)
	char back_hz_to_str[11]; // size 11 used as this is the max num of chars (including \0 that a uint32_t can be)
	memset(back_hz_to_str, 0, sizeof(back_hz_to_str)); // zeroing all memory

	// defining widget sizings
	Rectangle valbox_flash_rate_size = (Rectangle){ get_centred_x_from_window_w(WIDGET_DEF_W, WINDOW_SIZE_W), (window_centre_h - TEXT_DEF_FONTSIZE/2 - WIDGET_SPACING_H - WIDGET_DEF_H), WIDGET_DEF_W, WIDGET_DEF_H }; // will be x centred
	Rectangle text_flash_hz_size = (Rectangle){ get_centred_x_from_window_w(TEXT_DEF_FONTSIZE, WINDOW_SIZE_W), (window_centre_h - TEXT_DEF_FONTSIZE/2), 0x0, TEXT_DEF_FONTSIZE }; // x, y, 0x0, fontsize
	Rectangle button_start_size = (Rectangle){ get_centred_x_from_window_w(WIDGET_DEF_W, WINDOW_SIZE_W), (window_centre_h + TEXT_DEF_FONTSIZE/2 + WIDGET_SPACING_H), WIDGET_DEF_W, WIDGET_DEF_H };

	// infinite loop runs the game
	while (1) {
		// continously gather time for frame timing
		time_since_init = GetTime();

		// moves out of infinite loop if window is to be closed
		if (WindowShouldClose() || end_game_keys_pressed()) {
			goto out_close_window;
		}

		// check if a flash should occur this drawing loop
		double time_diff = time_since_init - time_of_last_flash;
		if (time_diff >= time_between_flashes_s && time_between_flashes_s > 0.0) {
			int alternate_back_res = alternate_background_colour(&background_col); 
			if (alternate_back_res != SUCCESS) {
				fprintf(stderr, "ERROR: an invalid colour was provided to alternate the background colour to\n");
				res = alternate_back_res;
				goto out_close_window;
			}
			time_of_last_flash = time_since_init; // ensuring another Hz passes before next flash
		}

		BeginDrawing();
		
			// drawing relevant boxes
			GuiValueBox(valbox_flash_rate_size, "", &usr_val_flash_hz, MIN_FLASH_HZ, MAX_FLASH_HZ, true); // updates usr_val_flash_hz with user provided int
			int button_start_clicked = GuiButton(button_start_size, "START");
			
			// actioning the start button being clicked --> updating refreshing freq
			if (button_start_clicked || IsKeyPressed(KEY_ENTER)) {
				if (MIN_FLASH_HZ <= usr_val_flash_hz <= MAX_FLASH_HZ) { // checking value is within the specified bounds
				 	if (usr_val_flash_hz != 0) { // avoiding division by zero error
						time_between_flashes_s = 1.0 / (double)usr_val_flash_hz; // t[s] = 1 / f[Hz]
					} else {
						time_between_flashes_s = 0.0;
					}

					// attempting to write new refreshing rate as string (so that it can be printed to GUI)
					snprintf(back_hz_to_str, sizeof(back_hz_to_str), "%d", usr_val_flash_hz);
				}
			}   

			// drawing diagnostics values
			if (back_hz_to_str) { // ensuring that the string is not NULL
				DrawText(back_hz_to_str, text_flash_hz_size.x, text_flash_hz_size.y, text_flash_hz_size.height, YELLOW); // draws the current flashing speed
			}
			DrawFPS(0, 0); // simply for rationality purposes --> drawn at top left
			
			// background update
			ClearBackground(background_col);

		EndDrawing();
	}

out_close_window:
	CloseWindow();
out_basic:
	return res;
}
