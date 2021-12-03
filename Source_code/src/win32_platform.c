/*
===============================================================================
Win32 platform with code for creation window and main game loop
===============================================================================
*/

/* Standard includes: */
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>

/* Program includes: */
#include <utils.h>
#include <simulation.h>
#include <input_treatment.h>
#include <simulation_constants.h>

/* Other variables */
static Render_Buffer_t render_buffer;  /* Buffer for the whole window image */
static Input_t user_input = {0};  /* Structure storing the user input data */
static b32 is_running;  /* Flag for the simulation running indication */

/* Static functions */
/* Function for window messages processing */
static LRESULT CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param);


int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    /* Entry point for the windows application */
    /* Avoid warning messages about not used function parameters */

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    /* Create a window class */
    WNDCLASS window_class = {0};
    
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_callback;
    window_class.lpszClassName = "Simulation";

    /* Register the window class (as ANSI window) */
    RegisterClassA(&window_class);

    /* Create a window and return a window handle */
    HWND window; /* Handle to the main game window */
    DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU;
    window = CreateWindowEx(0, window_class.lpszClassName, "Simulation", dwStyle,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0);
       
    /* Check if the window was successfully created */
    if (window == NULL) {
        assert(0 && "ERROR: Window was not successfully created");
    }
    
    /* Prearation for the main processing loop */
    is_running = true;  
    HDC hdc = GetDC(window);  /* Handele to the drawing content */
    MSG message = {0};  /* Message structure that is used in callback function */
   
    /* Window message processing loop */
    while (is_running)
    {
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        /* Process a simulation tick */
        simulation_calculate_tick(&user_input, &render_buffer);

        /* Render the calculated bitmap */
        StretchDIBits(hdc, 0, 0, (int)render_buffer.width, (int)render_buffer.height, 0, 0,
        (int)render_buffer.width, (int)render_buffer.height, render_buffer.bitmap_memory,
        &render_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

        /* Sleep for some time */
        Sleep(1);
    }

    /* Free the used resources */
    VirtualFree(render_buffer.bitmap_memory, 0, MEM_RELEASE);
    ReleaseDC(window, hdc);    
}

/* 
================================================================================
Realization of the static functions 
================================================================================
*/

static LRESULT CALLBACK 
window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    /* Callback function definition. Messages processing routines */

    LRESULT result = 0;

    switch (message)
    {
        /* Window closing and destroying: */
        case WM_CLOSE:
        case WM_DESTROY:
        {
            is_running = false;
        } break;

        /* Creation of the window: */
        case WM_CREATE:
        {
            /* Retrieves the coordinates of a window's client area */
            RECT rect;  /* Rectangle to hold screen coordinates */

            GetClientRect(window, &rect);
            render_buffer.width = (u32)(rect.right - rect.left);
            render_buffer.height = (u32)(rect.bottom - rect.top);

            /* Memory allocation with windows layer VirtualAlloc function */
            SIZE_T mem_size = sizeof(u32) * render_buffer.width * render_buffer.height;
            render_buffer.bitmap_memory = VirtualAlloc(0, mem_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            /* Fill the bitmap_info structure */
            render_buffer.bitmap_info.bmiHeader.biSize = sizeof(render_buffer.bitmap_info.bmiHeader);
            render_buffer.bitmap_info.bmiHeader.biWidth = render_buffer.width;
            render_buffer.bitmap_info.bmiHeader.biHeight = render_buffer.height;
            render_buffer.bitmap_info.bmiHeader.biPlanes = 1;
            render_buffer.bitmap_info.bmiHeader.biBitCount = 32;
            render_buffer.bitmap_info.bmiHeader.biCompression = BI_RGB;            
        }
        
        /* Pressing of the different keys: */
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {    
            /* Getting the raw key codes */
            u32 vk_code = (u32)w_param;
            b32 was_down = ((l_param & (1 << 30)) != 0);
            b32 is_down = ((l_param & (1 << 31)) == 0);
        
            /* Prepare the user input from the raw keyboard codes */
            reset_changed_state(&user_input);
            prepare_user_input(vk_code, was_down, is_down, &user_input);
        } break;

        /* Process the mouse movement in the window */
        case WM_MOUSEMOVE:
        {
            POINT mouse_pointer;  /* Structure containing mouse pointer coordinates */
            GetCursorPos(&mouse_pointer); /* Global cursor position */
            ScreenToClient(window, &mouse_pointer); /* Local cursor position */
            user_input.mouse.x = mouse_pointer.x;
            user_input.mouse.y = render_buffer.height - mouse_pointer.y;
        } break;

        /* Default message */
        default:
        { 
            result = DefWindowProcA(window, message, w_param, l_param);
        }
    }
    return result;
}
