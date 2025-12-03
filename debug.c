#include <stdio.h>
#include <stdlib.h>

int main() {
    int height;
    char empty, obstacle, full;
    
    int result = scanf("%d%c%c%c\n", &height, &empty, &obstacle, &full);
    printf("Result: %d\n", result);
    if (result == 4) {
        printf("Height: %d\n", height);
        printf("Empty: '%c' (%d)\n", empty, empty);
        printf("Obstacle: '%c' (%d)\n", obstacle, obstacle);
        printf("Full: '%c' (%d)\n", full, full);
    }
    return 0;
}
