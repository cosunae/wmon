#include <ctime>
#include <iostream>
#include "wmon_c.h"
#include "wmon.hpp"

size_t timestamp()
{
    return std::time(nullptr);
}

wmon *wmon_init(const char *bucket)
{
    return new wmon(bucket, 1);
}
void wmon_push_metric(wmon *wm, const char *measurement, const char *fieldvalpair, size_t timestamp)
{
    wm->push_metric(measurement, fieldvalpair, timestamp);
}
void wmon_push_metric_tag(wmon *wm, const char *measurement, const char *fieldvalpair, size_t timestamp, const char *jobtags)
{
    wm->push_metric(measurement, fieldvalpair, timestamp, jobtags);
}
void wmon_destroy(wmon *wm)
{
    delete wm;
}
