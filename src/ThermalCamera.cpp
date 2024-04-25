// Include necessary header files
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "ThermalCamera.h"
#include "constants.h"
#include "colormap.h"
#include <math.h>
#include <string>

// ThermalCamera constructor
ThermalCamera::ThermalCamera() {
    // Log copyright info
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "=== ThermalCamera, Copyright 2020 Ava-X ===");
    // Get and set the resource path
    char *base_path = SDL_GetBasePath();
    if (base_path) {
        resource_path = std::string(base_path) + "../resources";
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Resource path: %s\n", resource_path.c_str());
    }
    // Initialize SDL and the sensor
    init_sdl();
    init_sensor();
    // Set flags for camera operation
    is_running = true;
    is_measuring = false;
    is_measuring_lpf = is_measuring;
    // Initialize temperature-related variables
    mean_temp = 0.0f;
    mean_temp_lpf = 0.0f;
    // Initialize animation-related variables
    timer_is_animating = 0;
    animation_frame_nr = 0;
    frame_no = 0;
}

// ThermalCamera destructor
ThermalCamera::~ThermalCamera() {
    clean();
}

// SDL initialization function
void ThermalCamera::init_sdl() {
    // Set the scale quality hint to linear
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // Log error and exit if SDL initialization fails
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init() Failed: %s\n", SDL_GetError());
        clean();
        exit(EXIT_FAILURE);
    }
    // ... (omitted for brevity, rest of the code remains unchanged)
}

// ... (omitted for brevity, rest of the code remains unchanged)

void ThermalCamera::update() {
    // Increment frame number
    frame_no++;
    // Start timing this function call
    auto start = std::chrono::system_clock::now();
    // Get frame data from the sensor
    MLX90640_GetFrameData(MLX_I2C_ADDR, frame);

    // ... (omitted for brevity, rest of the code remains unchanged)
}

// ... (omitted for brevity, rest of the code remains unchanged)

// Function to render the temperature labels
void ThermalCamera::render_temp_labels() const {
    // Set the origin for temperature labels
    SDL_Point origin = {0,  640 - 48};
    // Define text color as white
    SDL_Color text_color = {255, 255, 255, 255};
    // Render temperature message
    render_text(message, text_color, origin, 1, font32);
    // Define and render label for skin temperature
    std::string label = "Skin temperature: ";
    render_text(label, text_color, origin, 0, font32);
    // Set origin to top-left corner
    origin = {0, 0};
    
    // Convert mean temperature to Fahrenheit
    float mean_temp_far = (mean_temp_lpf * 1.8) + 32;

    // ... (omitted for brevity, rest of the code remains unchanged)
}

// ... (omitted for brevity, rest of the code remains unchanged)

// Function to take a screenshot
void ThermalCamera::screenshot() {
    // Create an SDL surface for the screenshot
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, display_width, display_height, 32, 0x00ff
