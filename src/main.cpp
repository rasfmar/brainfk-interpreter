#include <bits/stdc++.h>

void help() {
    std::cout << "usage: ./a sourcecode" << std::endl;
}

static unsigned int amountOfMemory = 0xffff;

int exec(const char *src) {
    char memory[amountOfMemory];
    memset(memory, 0, amountOfMemory);
    
    unsigned short ptr = 0;
    unsigned int index = 0;
    char c = '\0';

    for (; index < strlen(src); index++) {
        switch (src[index]) {
        case '>':
            ptr++;
            break;
        case '<':
            ptr--;
            break;
        case '+':
            (*(memory + ptr))++;
            break;
        case '-':
            (*(memory + ptr))--;
            break;
        case '.':
            std::cout << *(memory + ptr);
            break;
        case ',':
            c = getchar();
            *(memory + ptr) = c;
            break;
        case '[':
            if (!(*(memory + ptr))) {
                int end = -1;
                unsigned int lvl = 0;

                // find the ]
                for (unsigned int i = index + 1; i < strlen(src); i++) {
                    if (src[i] == '[') {
                        lvl++;
                    } else if (src[i] == ']') {
                        if (!lvl) {
                            end = i;
                            break;
                        } else {
                            lvl--;
                        }
                    }
                }

                if (end > -1) {
                    index = end;
                    break;
                } else {
                    return 0;
                }
            }
            break;
        case ']':
            if (*(memory + ptr)) {
                int start = -1;
                unsigned int lvl = 0;

                // find the [
                for (unsigned int i = index - 1; i >= 0; i--) {
                    if (src[i] == ']') {
                        lvl++;
                    } else if (src[i] == '[') {
                        if (!lvl) {
                            start = i;
                            break;
                        } else {
                            lvl--;
                        }
                    }
                }

                if (start > -1) {
                    index = start;
                    break;
                } else {
                    return 0;
                }
            }
            break;
        default:
            break;
        }
    }

    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        help();
        return 1;
    } else {
        const char *src = (const char*)(argv[1]);

        if (exec(src)) {
            std::cout << std::endl << "Program terminated" << std::endl;
            return 0;
        } else {
            std::cout << std::endl << "An error occurred" << std::endl;
            return 1;
        }
    }
}

