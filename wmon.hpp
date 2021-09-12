#pragma once

#include <string>
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

class wmon {
    int loglevel_;
    std::string token_;
    std::string url_;
    std::string tags_;
    std::string org_;
    std::string bucket_;
    bool active_;
    std::string msg_;
    static constexpr int limit_ = 5000;

    RestClient::Connection* conn_;

public:
    wmon(int loglevel);

    bool active() const ;

    void push_metric(std::string measurement, std::string fieldvalpair, unsigned long timestamp, std::string jobtags = "") ;
};
