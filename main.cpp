#include <iostream>
#include "RtMidi.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        RtMidiIn midiin;

        std::cout << "isPortOpen: " << midiin.isPortOpen() << std::endl;
    } catch (RtMidiError &error) {
        // Handle the exception here
        error.printMessage();
    }
    return 0;
}
