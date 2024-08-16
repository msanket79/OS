// main.c

// Function declarations
void start();
extern void main();

__attribute__((section(".entry"))) void start() {

    // Call the main function
    main();
    // Infinite loop to prevent exit
    while (1) { }
}

