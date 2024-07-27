#include<debugDisplay.h>

void main() {
    // Simple main function
    int  i=0x12;
    debugClrScr(0x18);
    debugGoToXY(4,4);
    debugSetColor(0x17);
    debugPrintf("+=============================\n");
    debugPrintf("=         FalconOS            =\n");
    debugPrintf("+=============================\n");
    // const char* hello = "Hello there this is sanket !";

    // char* video_memory = (char*) 0xb8000;
    // while (*hello) {
    //     *video_memory++ = *hello++;
    //     *video_memory++ = 0x07; // Attribute-byte: light gray on black screen
    // }

    // Loop indefinitely
    while (1) { }
}
