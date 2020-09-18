#include <bits/stdc++.h>

void help() {
    std::cout << "usage: ./bf fileName.bf" << std::endl;
}

static unsigned int amountOfMemory = 0xffff;

int exec(std::string src) {
    char memory[amountOfMemory];
    memset(memory, 0, amountOfMemory);
    
    unsigned short ptr = 0;
    unsigned int index = 0;
    char c = '\0';

    for (; index < src.length(); index++) {
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
                for (unsigned int i = index + 1; i < src.length(); i++) {
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
        std::ifstream t(argv[1]);
        std::stringstream buffer;
        buffer << t.rdbuf();

        int result = exec(buffer.str());
        std::cout << std::endl;

        return result;
    }
}

