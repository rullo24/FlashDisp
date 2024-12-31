#include "utils.h"
#include "status.h"

int alternate_background_colour(Color *curr_colour) {
    int res = SUCCESS;   
    Color colour_1 = COLOUR_1;
    Color colour_2 = COLOUR_2;

    // check if current colour is colour_1 
    if (curr_colour->r == colour_1.r && curr_colour->g == colour_1.g && curr_colour->b == colour_1.b && curr_colour->a == colour_1.a) {
        *curr_colour = colour_2; // flipping colour
    } else if (curr_colour->r == colour_2.r && curr_colour->g == colour_2.g && curr_colour->b == colour_2.b && curr_colour->a == colour_2.a) {
        *curr_colour = colour_1; // flipping colour
    } else { // colour invalid --> return err
        res = INVALID_COLOUR_ERR;
    }

    return res;
}

int get_centred_x_from_window_w(int box_w, int screen_w) {
    return (screen_w - box_w) / 2; // integer div may truncate
}

bool end_game_keys_pressed() {
    if (((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C))) || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_W))) {
        return true;   
    }
    return false;
}