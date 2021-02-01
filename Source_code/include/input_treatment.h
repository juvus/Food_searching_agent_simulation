#ifndef INPUT_TREATMENT_H_
#define INPUT_TREATMENT_H_

#include <utils.h>

/* Enumerator for button treatment */
enum Button_Type {
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_COUNT,
};
typedef enum Button_Type Button_Type_t;

/* Structure for storing the key button state in nice form */
struct Button {
    u32 vk_code;
    b32 is_pressed;
    b32 is_changed;
};
typedef struct Button Button_t;

/* Structure for input from mouse and keyboard */
struct Input {
    V2_u32_t mouse;
    Button_t buttons[BUTTON_COUNT];
};
typedef struct Input Input_t;

/* Function for the raw input treatment and preparing user input */
void prepare_user_input(u32 vk_code, b32 was_down, b32 is_down, Input_t *user_input);

/* Reset the is_changed state of all buttons */
void reset_changed_state(Input_t *user_input);

/* Function to determine whether the button is pressed smoothly */
b32 key_is_pressed_smooth(Button_Type_t button, Input_t *user_input);

/* Function to determine whether the button is pressed iteratively */
b32 key_is_pressed_iterative(Button_Type_t button, Input_t *user_input);

#endif // INPUT_TREATMENT_H_
