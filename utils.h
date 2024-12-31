#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>
#include <stdbool.h>

int alternate_background_colour(Color *curr_colour);
int get_centred_x_from_window_w(int box_w, int screen_w);
bool end_game_keys_pressed();

#endif