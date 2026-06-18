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

int main() {
    cout << "Programming Challenge A. Let's Go!!!" << endl;

    GWindow window;
    if (+window.Create(100, 100, 800, 600, GWindowStyle::WINDOWEDLOCKED)) {

        GRasterSurface surface;
        if (+surface.Create(window)) {

            int frames = 0;
            auto start = std::chrono::high_resolution_clock::now();
            while (+window.ProcessWindowEvents()) {
                // known issue: Clear() does not affect Present() unless Update() calls occur.
                if (+surface.Clear(0xFF000000)) {

                    unsigned int *pixels;
                    unsigned short width, height;
                    if (+surface.LockUpdateBufferWrite(&pixels, width, height)) {

                        // This is where we can update the surface
                        for (unsigned int y = 0; y < height; ++y) {
                            for (unsigned int x = 0; x < width; ++x) {
                                unsigned int noise = rand() % 256;
                                pixels[y * width + x] = 0xFF000000 | noise | noise << 8 | noise << 16;
                            }
                        }

                        surface.UnlockUpdateBufferWrite();
                    }
                    surface.Present();

                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end - start;

                    if (elapsed.count() > 1.0) {

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
