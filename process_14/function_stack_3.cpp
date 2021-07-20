//
// Created by rere on 2021/7/19.
//

#include <cstdio>

int func_2() {
    return -1;
}

int func_1(int a, int b, int c) {
    int e, f;
    long long g;

    e = 1;
    f = 2;
    g = 3;

    func_2();

    e = a + b + c;

    return e ;
}

int main(int argc, char* argv[]) {
    int f = 0;
    int g = 1;
    f = func_1(1, 2, 3);

    printf("value: %d\n", f);
    return 0;
}