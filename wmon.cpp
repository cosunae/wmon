#include <chrono>
#include "wmon.hpp"
#include <iostream>

namespace detail
{
    std::string getenv(const char *var)
    {
        char *c = std::getenv(var);
        if (!c)
            return "";
        return std::string(c);
    }
}

wmon::wmon(std::string bucket, int loglevel, int sizelimit) : bucket_(bucket), loglevel_(loglevel), lastupdate_(std::time(nullptr)), sizelimit_(sizelimit)
{
    url_ = detail::getenv("WMON_URL");
    token_ = detail::getenv("WMON_TOKEN");
    tags_ = detail::getenv("WMON_TAGS");
    org_ = detail::getenv("WMON_ORG");

    active_ = !token_.empty() && !url_.empty() && !tags_.empty() && !org_.empty() && !bucket_.empty();
    if (loglevel_ > 0 && !active_)
    {
        std::cout << "WMON warning : required env variables WMON_XXX not defined in current shell" << std::endl;
        return;
    }
    // initialize RestClient
    RestClient::init();

    if (!active())
        return;
    // get a connection object
    conn_ = new RestClient::Connection(url_);
}

wmon::~wmon()
{
    flush_metrics();
}

bool wmon::active() const
{
    return active_;
}

bool wmon::shouldupdate() const
{
    std::time_t now = std::time(nullptr);
    return msg_.size() > sizelimit_ || (now - lastupdate_) > timelimit_;
}
void wmon::flush_metrics()
{
    // std::cout << "WMON ................... flush metrics " << std::endl;
    // std::cout << msg_ << std::endl;

    auto start = std::chrono::steady_clock::now();
    RestClient::Response r = conn_->post("/api/v2/write?org=" + org_ + "&bucket=" + bucket_ + "&precision=s", msg_);
    // std::cout << "Resp : " << r.code << "," << r.body << "," << std::endl;
    auto end = std::chrono::steady_clock::now();

    auto ptime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (msg_.find('\n') <= msg_.size())
    {
        std::string firstline = msg_.substr(0, msg_.find('\n'));

        size_t tstamps;
        try
        {
            tstamps = std::stoll(firstline.substr(firstline.find_last_of(' ') + 1, firstline.size()));
        }
        catch (const std::invalid_argument &ia)
        {
            std::cerr << "Invalid argument: " << ia.what() << " casting " << firstline << '\n';
        }

        std::string lastline = msg_.substr(msg_.find_last_of('\n'), msg_.size());

        size_t tstampe;
        try
        {
            tstampe = std::stoll(lastline.substr(lastline.find_last_of(' ') + 1, lastline.size()));
        }
        catch (const std::invalid_argument &ia)
        {
            std::cerr << "Invalid argument: " << ia.what() << " casting " << lastline << '\n';
        }

        double overhead = (ptime / 1000.0) / (tstampe - tstamps);

        msg_.clear();
        msg_ = "wmon,timelimit=" + std::to_string(timelimit_) + " push_time=" + std::to_string(ptime) + " " + std::to_string(std::time(nullptr)) + "\n";
        msg_ += "wmon,timelimit=" + std::to_string(timelimit_) + " dt=" + std::to_string(tstampe - tstamps) + " " + std::to_string(std::time(nullptr)) + "\n";
        msg_ += "wmon,timelimit=" + std::to_string(timelimit_) + " overhead=" + std::to_string(overhead) + " " + std::to_string(std::time(nullptr));
    }
    else
    {
        msg_.clear();
    }

    lastupdate_ = std::time(nullptr);
}
void wmon::push_metric(std::string measurement, std::string fieldvalpair, unsigned long timestamp, std::string jobtags)
{
    if (!active())
        return;

    // set headers
    RestClient::HeaderFields headers;
    headers["Accept"] = "application/json";
    headers["Authorization"] = "Token " + token_;

    conn_->SetHeaders(headers);

    conn_->AppendHeader("Content-Type", "text/plain");
    std::string tags = tags_ + (jobtags.empty() ? std::string() : "," + jobtags);
    std::string msg = measurement + "," + tags + " " + fieldvalpair + " " + std::to_string(timestamp);
    auto update = shouldupdate();
    if (msg_.empty())
    {
        msg_ = msg;
    }
    else if (!update)
    {
        msg_ += '\n' + msg;
    }
    else
    {
        msg_ += '\n' + msg;
        flush_metrics();
    }
}
