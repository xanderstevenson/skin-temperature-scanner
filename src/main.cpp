/*
Copyright 2020 ****************************

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <chrono> // Include necessary for using the chrono library
#include <thread> // Include necessary for using the thread library
#include "constants.h" // Include constants used in the program
#include "ThermalCamera.h" // Include the ThermalCamera header file

int main() {
    ThermalCamera thermal_camera; // Create a ThermalCamera object
    
    // Calculate frame time using the constants defined in constants.h
    auto frame_time = std::chrono::microseconds(FRAME_TIME_MICROS + OFFSET_MICROS);
    
    // Main loop that runs while the thermal camera is operational
    while (thermal_camera.running()) {
        auto start = std::chrono::system_clock::now(); // Record the start time

        thermal_camera.handle_events(); // Process input and events
        thermal_camera.update(); // Update the state of the thermal camera
        thermal_camera.render(); // Render the output (e.g., to a screen or file)

        auto end = std::chrono::system_clock::now(); // Record the end time
        // Calculate the elapsed time for the frame processing
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Sleep for the remaining time of the frame to maintain a consistent frame rate
        std::this_thread::sleep_for(std::chrono::microseconds(frame_time - elapsed));
    }
    thermal_camera.clean(); // Perform any necessary cleanup before exiting
    exit(EXIT_SUCCESS); // Exit the program successfully
}
