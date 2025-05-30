#include "../../include/utils/Utils.h"
#include <cstdlib>

using namespace std;

int randBtw(int n1, int n2) {
    return n1 + rand() % (n2 - n1 + 1);
}