#include "dataset.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dataset_number>\n", argv[0]);
        return 1;
    }

    int dataset_number = atoi(argv[1]);

    // Define the dataset based on the argument
    #if defined(SMALL_H)
        #include "small.h"
    #elif defined(OWN_SMALL_H)
        #include "own_small.h"
    #else
        #error "No dataset defined"
    #endif

    return 0;
}
