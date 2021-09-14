#pragma once

#include <string>
#include <ctime>
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

class wmon
{
    int loglevel_;
    std::string token_;
    std::string url_;
    std::string tags_;
    std::string org_;
    std::string bucket_;
    bool active_;
    //TODO fix static allocation
    std::string msg_;
    const int sizelimit_;
    static constexpr int timelimit_ = 120;
    std::time_t lastupdate_;

    RestClient::Connection *conn_;

public:
    wmon(std::string bucket, int loglevel, int sizelimit = 100000);
    ~wmon();

    bool active() const;

    void push_metric(std::string measurement, std::string fieldvalpair, unsigned long timestamp, std::string jobtags = "");
    void flush_metrics();
    bool shouldupdate() const;
};
