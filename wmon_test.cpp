#include <ctime>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "wmon.hpp"

int main()
{
  wmon wm("test", 1, 64);

  while (true)
  {
    double rr = (double)std::rand() / (double)(RAND_MAX)*5;
    std::time_t result = std::time(nullptr);

    wm.push_metric("cosmob", "ttime=" + std::to_string(rr), result);
    wm.push_metric("cosmob", "ttime1=" + std::to_string(rr), result);
    wm.push_metric("cosmob", "ttime2=" + std::to_string(rr), result);
    wm.push_metric("cosmob", "ttime3=" + std::to_string(rr), result);
    wm.push_metric("cosmob", "ttime4=" + std::to_string(rr), result);
    wm.push_metric("cosmob", "ttime5=" + std::to_string(rr), result);

    usleep(rr * 1e6);
    std::cout << "t " << rr << "," << result << std::endl;
  }
}
