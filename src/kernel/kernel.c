// main.c

// Function declarations
void start();
void main();

__attribute__((section(".entry"))) void start() {
    // Call the main function
    main();

    // Infinite loop to prevent exit
    while (1) { }
}

void main() {
    // Simple main function
    const char* hello = "Hello Kernel, this is sanket exectuing from the 32bit c compiler !";

    char* video_memory = (char*) 0xb8000;
    while (*hello) {
        *video_memory++ = *hello++;
        *video_memory++ = 0x07; // Attribute-byte: light gray on black screen
    }

    // Loop indefinitely
    while (1) { }
}
