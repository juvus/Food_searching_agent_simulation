/*
===============================================================================
Module for treatment of the user input (keyboard and mouse)
===============================================================================
*/

/* Standard includes: */
#include <windows.h>
#include <stdio.h>

/* Program includes: */
#include <utils.h>
#include <input_treatment.h>

/* Static functions: */
/* Function for prepare the particular key */
static void prepare_key(u32 vk_code, b32 was_down, b32 is_down, int key, int button, 
    Input_t *user_input);

void 
prepare_user_input(u32 vk_code, b32 was_down, b32 is_down, Input_t *user_input)
{
    /* Function for the raw input treatment and preparing user input */

    prepare_key(vk_code, was_down, is_down, VK_RIGHT, BUTTON_RIGHT, user_input);
    prepare_key(vk_code, was_down, is_down, VK_LEFT, BUTTON_LEFT, user_input);
    prepare_key(vk_code, was_down, is_down, VK_UP, BUTTON_UP, user_input);
    prepare_key(vk_code, was_down, is_down, VK_DOWN, BUTTON_DOWN, user_input);
}

void
reset_changed_state(Input_t *user_input)
{
    /* Reset the is_changed state of all buttons */
    int i;
    for (i = 0; i < BUTTON_COUNT; i++) {
        user_input->buttons[i].is_changed = false;
    }
}

b32 
key_is_pressed_smooth(Button_Type_t button, Input_t *user_input)
{
    /* Function to determine whether the button is pressed smoothly */
    return (user_input->buttons[button].is_pressed);
}

b32 
key_is_pressed_iterative(Button_Type_t button, Input_t *user_input) 
{
    /* Function to determine whether the button is pressed iteratively */
    return (user_input->buttons[button].is_pressed && user_input->buttons[button].is_changed);
}

static void 
prepare_key(u32 vk_code, b32 was_down, b32 is_down, int key, int button, Input_t *user_input) 
{
    /* Function for prepare the particular key */
    b32 new_state;
    b32 is_changed = false;

    if (vk_code == key) {
        /* If button is just pressed (1, 0) */
        if ((is_down) && (!was_down)) {
            new_state = true;
            is_changed = true;
        }
        /* If button is just released (0, 1) */
        if ((!is_down) && (was_down)) {
            new_state = false;
        }
        /* If button is pressed and holding (1, 1) */
        if ((is_down) && (was_down)) {
            new_state = true;
            is_changed = true;
        }
        /* Update the is_pressed button state */
        user_input->buttons[button].is_pressed = new_state;
        user_input->buttons[button].is_changed = is_changed;
    }
}
