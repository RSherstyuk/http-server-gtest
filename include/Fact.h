#ifndef FACT_H
#define FACT_H

class Fact {
public:
  static int fact(int n) {
    if (n == 0 || n == 1) {
      return 1;
    }
    return fact(n - 1) * n;
  }
};

#endif