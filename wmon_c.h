#pragma once

#include "wmon.hpp"
extern "C"
{
    wmon *wmon_init(const char *bucket);
    void wmon_push_metric(wmon *wm, const char *measurement, const char *fieldvalpair, size_t timestamp);
    void wmon_push_metric_tag(wmon *wm, const char *measurement, const char *fieldvalpair, size_t timestamp, const char *tag);
    void wmon_destroy(wmon *wm);
    size_t timestamp();
}
