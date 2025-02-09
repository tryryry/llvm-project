int foo(int a) {
    int x = 10;
    int y = x + 20;
    if (x > 5) {  // Now this is always true
        y = y + 5;
    }
    return y;
}