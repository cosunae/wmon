#include <ctime>
#include <iostream>
#include "wmon_c.h"
#include "wmon.hpp"

size_t timestamp() {
    return std::time(nullptr);
}

wmon* wmon_init() {
    return new wmon(1);
}
void wmon_push_metric(const wmon* wm, const char* measurement, const char* fieldvalpair, size_t timestamp) {
    wm->push_metric(measurement, fieldvalpair, timestamp);
}
void wmon_destroy(wmon* wm) {
    delete wm;
}
