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
    std::string msg_;
    static constexpr int limit_ = 5000;
    static constexpr int timelimit_ = 120;
    std::time_t lastupdate_;

    RestClient::Connection *conn_;

public:
    wmon(int loglevel);
    ~wmon();

    bool active() const;

    void push_metric(std::string measurement, std::string fieldvalpair, unsigned long timestamp, std::string jobtags = "");
    void flush_metrics();
    bool shouldupdate() const;
};
