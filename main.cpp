#include <chrono>
#include <iostream>
using namespace std;

#define GATEWARE_ENABLE_CORE
#define GATEWARE_ENABLE_SYSTEM
#define GATEWARE_ENABLE_GRAPHICS

#define GATEWARE_DISABLE_GOPENGLSURFACE
#define GATEWARE_DISABLE_GDIRECTX11SURFACE
#define GATEWARE_DISABLE_GDIRECTX12SURFACE
#define GATEWARE_DISABLE_GVULKANSURFACE

#include "gateware-main/Gateware.h"
using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;

// Example visual effects
void TV_Static(unsigned int* pixels, unsigned int width, unsigned int height);
void MovingWaveform(float totalTime, unsigned int* pixels, unsigned int width, unsigned int height);

int main() {
    cout << "Programming Challenge A. Let's Go!!!" << endl;

    GWindow window;
    if (+window.Create(100, 100, 800, 600, GWindowStyle::WINDOWEDLOCKED)) {
        GRasterSurface surface;
        if (+surface.Create(window)) {
            int frames = 0;
            float time = 0;
            auto start = std::chrono::high_resolution_clock::now();
            const auto initalTime = start;
            while (+window.ProcessWindowEvents()) {
                // known issue: Clear() does not affect Present() unless Update() calls occur.
                if (+surface.Clear(0xFF000000)) {
                    unsigned int *pixels;
                    unsigned short width, height;
                    if (+surface.LockUpdateBufferWrite(&pixels, width, height)) {
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<float> total = end - initalTime;
                        
                        // This is where we can update the surface
                        MovingWaveform(total.count(), pixels, width, height);
                        //TV_Static(pixels, width, height);

                        surface.UnlockUpdateBufferWrite();
                    }
                    surface.Present();
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<float> elapsed = end - start;
                    if (elapsed.count() > 1.0f) {
                        char buffer[128];
                        sprintf(buffer, "[Your Project/Title/Name Here] FPS %i", frames);
                        window.SetWindowName(buffer);
                        start = std::chrono::high_resolution_clock::now();
                        frames = 0;
                    }
                    else ++frames;
                }
            }
        }
    }
    return 0;
}

void TV_Static(unsigned int* pixels, unsigned int width, unsigned int height) {
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int noise = rand() % 256;
            pixels[y * width + x] = 0xFF000000 | noise | noise << 8 | noise << 16;
        }
    }
}

void MovingWaveform(float totalTime, unsigned int* pixels, unsigned int width, unsigned int height) {
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            // plot wave when close
            float amp = height>>2, freq = 1, h_shift = totalTime, v_shift = height>>2;
            float Yexpected = (height>>2) + amp * sinf(freq * (G_DEGREE_TO_RADIAN_F(x) - h_shift)) + v_shift;
            if (G_ABSOLUTE_COMPARISON(y, Yexpected, 100))
                pixels[y * width + x] = 0xFFFF6E00; // fullsail orange
            else
                pixels[y * width + x] = 0xFFFFFFFF; // white background
        }
    }
}
