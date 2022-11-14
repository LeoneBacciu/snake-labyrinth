#include "sequence.h"

sequence_t sequence_create() {
    sequence_t result = (sequence_t) {0, NULL};
    return result;
}

sequence_t sequence_element(int value) {
    int *s = malloc(sizeof(int));
    *s = value;
    sequence_t result = (sequence_t) {1, s};
    return result;
}

sequence_t sequence_add(sequence_t sequence, int value) {
    size_t size = sequence.size + 1;
    int *s = calloc(size, sizeof(int));
    memcpy(s, sequence.s, (size - 1) * sizeof(int));
    s[size - 1] = value;
    sequence_t result = (sequence_t) {size, s};
    return result;
}

int sequence_get(sequence_t sequence, size_t i) {
    return sequence.s[i];
}

int sequence_first(sequence_t sequence) {
    return sequence.s[0];
}

int sequence_last(sequence_t sequence) {
    return sequence.s[sequence.size - 1];
}

void sequence_destroy(sequence_t *sequence) {
    free(sequence->s);
}

void sequence_free(sequence_t *sequence) {
    sequence_destroy(sequence);
    free(sequence);
}
