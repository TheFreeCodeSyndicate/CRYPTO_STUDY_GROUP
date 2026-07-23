#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
ref: 
    - https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Algebraic.html
*/

// important: 'A' + (j + i % 26) % 26

char get_encrypted_letter(int pl_index, int kl_index) {
    // used to be a debug statement here.
    return 'A' + (kl_index + pl_index % 26) % 26;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // __FILE__ is NOT the file name. It's the source name during compilation.
        fprintf(stdout, "USAGE: %s [key] [phrase]\n", argv[0]);
        return 1;
    }

    int key_len = strlen(argv[1]);
    int phrase_len = strlen(argv[2]);

    char *key = argv[1];
    char *phrase = argv[2];

    int key_index = 0;
    for (int i = 0; i < phrase_len; i++) {
        if (!isalpha(phrase[i])) {
            putchar(phrase[i]);
            continue;
        }
        // this should be it's own check but whatever for now.
        if (!isalpha(key[key_index % key_len])) {
            key_index++;
        }

        putchar(get_encrypted_letter(
            toupper(phrase[i]) - 'A',
            toupper(key[key_index % key_len]) - 'A'
        ));

        key_index++;
    }

    return 0;
}