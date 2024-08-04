#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#define SIZE 1024

int main()
{
    // TODO rewrite string to char*
    char in[SIZE] = "    \naaa\n wow loL\n";
    int strlen_ = strlen(in);
    int currentIndex = 0;
    char res[SIZE];

    int index = 0;
    bool isPrinted = false;
    // TODO меньше strlen
    // while (in[index] != '\0') {
    while (index < strlen_)
        if (in[index] == '\t' || in[index] == ' ' || in[index] == '\n') {
            ++index;
            continue;
        }

        int start = index;
        int end = start;

        // TODO меньше strlen
        while (in[end] != '\t' && in[end] != ' ' && end < strlen_ && in[end] != '\n') {
            ++end;
        }
        int afterWord = end;
        --end;

        bool isPalindrom = true; // можно возле start хранить (типа ah, al)
        while (start < end) {
            if (in[start] != in[end]) {
                isPalindrom = false;
                break;
            }

            ++start;
            --end;
        }

        if (isPalindrom) {
            if (isPrinted) {
                res[currentIndex] = ' ';
                ++currentIndex;
            }
            isPrinted = true;
            while (index < afterWord) {
                res[currentIndex] = in[index];
                ++currentIndex;
                ++index;
            }
        }

        index = afterWord;
    }
    res[currentIndex] = 0;
    // current index = size of output

    std::cout << res;
    return 0;
}
