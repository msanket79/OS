#include<debugDisplay.h>
#include<hal.h>
void main() {
    // Simple main function
    int  i=0x12;
    debugClrScr(0x18);
    debugGoToXY(4,4);
    debugSetColor(0x17);
    debugPrintf("+=============================\n");
    debugPrintf("=         FALCONOS           =\n");
    debugPrintf("+=============================\n");

    debugSetColor (0x70);
	debugGoToXY(0,24);
	debugPrintf (" Initializing Hardware Abstraction Layer (HAL.lib)...                           ");

    halInitialize();

    getInterrupt(2);


    // Loop indefinitely
    while (1) { ;}
}
