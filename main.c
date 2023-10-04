#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Change constants for different manipulations
#define NUMBERS_COUNT 10
#define MIN_NUMBER 1
#define MAX_NUMBER 200
#define INITIAL_SIZE 5

typedef unsigned int positive;

struct object {
    positive number;
    char show_index;
};


// Generating NUMBERS_COUNT of random numbers and storing it into the pointer
positive *generate_numbers() {
    positive *to_return = (positive *) malloc(sizeof(positive) * NUMBERS_COUNT);

    for (int i = 0; i < NUMBERS_COUNT; i++) {
        to_return[i] = rand() % (MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER;
    }

    return to_return;
}


void fill_object(struct object to_fill[], const positive * source) {
    for (int i = 0; i < NUMBERS_COUNT; i++) {
        to_fill[i].number = source[i];
        to_fill[i].show_index = 0;
    }
}


// checking if target is inside to_fill[]
char check_answer(struct object to_fill[], positive target) {
    for (int i = 0; i < NUMBERS_COUNT; i++) {
        if (to_fill[i].number == target && to_fill[i].show_index == 0) {
            to_fill[i].show_index = 1;
            return 1;
        }
    }
    return 0;
}


void print_object(struct object to_print[]) {
    for (int i = 0; i < NUMBERS_COUNT; i++) {
        if (to_print[i].show_index)
            printf("%d ", to_print[i].number);
        else{
            positive temp = to_print[i].number;
            while (temp != 0) {
                printf("_");
                temp /= 10;
            }
            printf(" ");
        }
    }
    printf("\n");
}


// checking if user guessed all the numbers
char win_condition(struct object obj[]) {
    for (int i = 0; i < NUMBERS_COUNT; i++) {
        if (!obj[i].show_index)
            return 0;
    }
    return 1;
}


int main() {
    // Generating seed random from current time
    srand(time(NULL));

    printf("----------Numbers Game-----------\n"
           "Think of %d numbers from %d..%d range. Try to guess them\n"
           "Input 'q' in order to exit and show results\n", NUMBERS_COUNT, MIN_NUMBER, MAX_NUMBER);

    positive * generated = generate_numbers();
    struct object numbers_to_guess[NUMBERS_COUNT];
    fill_object(numbers_to_guess, generated);

    char *input = (char *) malloc(sizeof(char) * INITIAL_SIZE);
    int current_size = INITIAL_SIZE;

    while (1) {
        print_object(numbers_to_guess);

        printf("Your input:");
        scanf("%s", input);
        if (input[0] == 'q') {
            printf("The right answer was\n");
            int tmp = 0;
            for (int i = 0; i < NUMBERS_COUNT; i++) {
                printf("%d ", numbers_to_guess[i].number);
                if (numbers_to_guess[i].show_index == 1)
                    tmp++;
            }
            printf("You guessed %d numbers\n", tmp);
            break;
        }

        positive current_input = atoi(input);
        if (current_input < MIN_NUMBER || current_input > MAX_NUMBER)
            printf("The range is %d..%d\n", MIN_NUMBER, MAX_NUMBER);
        else {
            if (check_answer(numbers_to_guess, current_input))
                printf("Good Job!\n");
            else
                printf("Close Enough!\n");
        }

        if (win_condition(numbers_to_guess)) {
            printf("Congrats you won this hard game!\n");
            break;
        }
        // Increasing memory size of input if length is exceeded
        if (strlen(input) + 1 >= current_size) {
            input = (char *) realloc(input, strlen(input) + 1);

            if (input == NULL) {
                fprintf(stderr, "There was a memory error\n");
                free(input);
                free(generated);
                return 1;
            }
        }

    }

    free(generated);
    free(input);
    return 0;
}
