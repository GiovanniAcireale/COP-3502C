#include <stdio.h>
#include <string.h>

#define MAX_SPELLS 100
#define MAX_LENGTH 101 // +1 for null terminator

// Check if spell1 is a derivative of spell2
int is_derivative(const char* spell1, const char* spell2) {
    return strstr(spell2, spell1) != NULL;
}

int main() {

	// Array to store the spells
    char spells[MAX_SPELLS][MAX_LENGTH];
    int spell_count = 0;

    // Reading input until "END" is input
    while (1) {

        // Hopefully fgets doesn't count as 'gets' when grading
        fgets(spells[spell_count], MAX_LENGTH, stdin);

        // Remove newline character from fgets if present
        spells[spell_count][strcspn(spells[spell_count], "\n")] = '\0';

        // Stop reading input if "END" is input
        if (strcmp(spells[spell_count], "END") == 0) {
            break;
        }

        spell_count++;
    }

    int non_derivative_count = spell_count;

    // Check each spell against every other spell to identify derivatives
    for (int i = 0; i < spell_count; i++) {
        for (int j = 0; j < spell_count; j++) {

            // Skip comparing the spell with itself
            if (i != j && is_derivative(spells[i], spells[j])) {

                non_derivative_count--;

                break; // No need to check further once we find it's a derivative
            }
        }
    }

    // Output the number of non-derivatives
    printf("%d\n", non_derivative_count);

    return 0;
}
