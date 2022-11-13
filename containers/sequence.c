#include "sequence.h"

sequence_t sequence_create() {
    sequence_t result = (sequence_t) {0, NULL};
    return result;
}

sequence_t sequence_element(ll value) {
    ll *s = malloc(sizeof(ll));
    *s = value;
    sequence_t result = (sequence_t) {1, s};
    return result;
}

sequence_t sequence_add(sequence_t sequence, ll value) {
    size_t size = sequence.size + 1;
    ll *s = calloc(size, sizeof(ll));
    memcpy(s, sequence.s, (size - 1) * sizeof(ll));
    s[size - 1] = value;
    sequence_t result = (sequence_t) {size, s};
    return result;
}

ll sequence_get(sequence_t sequence, size_t i) {
    return sequence.s[i];
}

ll sequence_first(sequence_t sequence) {
    return sequence.s[0];
}

ll sequence_last(sequence_t sequence) {
    return sequence.s[sequence.size - 1];
}

void sequence_destroy(sequence_t *sequence) {
    free(sequence->s);
}
