// Giovanni Acireale, COP-3502C, Assignment 4, 10/27/24

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MOTES 500000
#define MAX_DEVICES 500000
#define M_PI acos(-1.0)  // Define Pi constant for accurate precision

// Function to calculate the volume of a magical mote (sphere)
double conjure_mote_volume(int enchantment_radius) {
    return (4.0 / 3.0) * M_PI * pow(enchantment_radius, 3);
}

// Function to calculate the volume of a containment box (device)
double conjure_device_volume(int spell_height, int spell_length, int spell_width) {
    return (double)spell_height * spell_length * spell_width;
}

// Swap function for elements in an array
void cast_swap(double* charm_a, double* charm_b) {
    double temp = *charm_a;
    *charm_a = *charm_b;
    *charm_b = temp;
}

// Partition function for quicksort
int magic_partition(double potions[], int low, int high) {
    double pivot = potions[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (potions[j] <= pivot) {
            i++;
            cast_swap(&potions[i], &potions[j]);
        }
    }
    cast_swap(&potions[i + 1], &potions[high]);
    return (i + 1);
}

// Optimized quicksort function with tail recursion
void incantation_sort(double potions[], int low, int high) {
    while (low < high) {
        int pi = magic_partition(potions, low, high);
        if (pi - low < high - pi) {
            incantation_sort(potions, low, pi - 1);
            low = pi + 1;
        }
        else {
            incantation_sort(potions, pi + 1, high);
            high = pi - 1;
        }
    }
}

int main() {
    int mote_count, device_count;
    double* mote_essences = (double*)malloc(MAX_MOTES * sizeof(double));
    double* device_chambers = (double*)malloc(MAX_DEVICES * sizeof(double));

    if (mote_essences == NULL || device_chambers == NULL) {
        fprintf(stderr, "Spell failed: Memory allocation\n");
        return 1;
    }

    // Input number of motes and devices
    scanf("%d %d", &mote_count, &device_count);

    // Read mote radii, calculate volumes, and store in mote_essences
    for (int i = 0; i < mote_count; i++) {
        int enchantment_radius;
        scanf("%d", &enchantment_radius);
        mote_essences[i] = conjure_mote_volume(enchantment_radius);
    }

    // Read device dimensions, calculate volumes, and store in device_chambers
    for (int i = 0; i < device_count; i++) {
        int spell_height, spell_length, spell_width;
        scanf("%d %d %d", &spell_height, &spell_length, &spell_width);
        device_chambers[i] = conjure_device_volume(spell_height, spell_length, spell_width);
    }

    // Sort both arrays in ascending order
    incantation_sort(mote_essences, 0, mote_count - 1);
    incantation_sort(device_chambers, 0, device_count - 1);

    // Two-pointer approach for containment
    int mote_cursor = mote_count - 1;  // Start with the largest mote
    int device_cursor = device_count - 1;  // Start with the largest device
    double uncontained_magic_sum = 0.0;

    // Process each mote from largest to smallest
    while (mote_cursor >= 0) {
        if (device_cursor >= 0 && mote_essences[mote_cursor] <= device_chambers[device_cursor]) {
            // Mote can be contained in the current device
            mote_cursor--;
            device_cursor--;
        }
        else {
            // Mote cannot be contained, add to uncontained magic sum
            uncontained_magic_sum += mote_essences[mote_cursor];
            mote_cursor--;
        }
    }

    // Output the sum of uncontained mote volumes with six decimal precision
    printf("%.6lf\n", uncontained_magic_sum);

    // Free allocated memory
    free(mote_essences);
    free(device_chambers);

    return 0;
}
