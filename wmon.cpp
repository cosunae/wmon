#include "wmon.hpp"
#include <iostream>

namespace detail {
    std::string getenv(const char* var) {
        char *c = std::getenv(var);
        if(!c) return "";
        return std::string(c);
    }
}

wmon::wmon(int loglevel) : loglevel_(loglevel) {
        url_ = detail::getenv("WMON_URL");
        token_ = detail::getenv("WMON_TOKEN");
        tags_ = detail::getenv("WMON_TAGS");
        org_ = detail::getenv("WMON_ORG");
        bucket_ = detail::getenv("WMON_BUCKET");

        active_ = !token_.empty() && !url_.empty() && !tags_.empty() && !org_.empty() && !bucket_.empty();
        if(loglevel_ > 0 && !active_)  {
            std::cout << "WMON warning : required env variables WMON_XXX not defined in current shell" << std::endl;
            return;
        }
        // initialize RestClient
        RestClient::init();

        if(!active()) return;
        // get a connection object
        conn_ = new RestClient::Connection(url_);

    }
    bool wmon::active() const {
        return active_;
    }

    void wmon::push_metric(std::string measurement, std::string fieldvalpair, unsigned long timestamp, std::string jobtags) {
        if (!active()) return;

        // set headers
        RestClient::HeaderFields headers;
        headers["Accept"] = "application/json";
        headers["Authorization"] = "Token "+token_;

        conn_->SetHeaders(headers);

        conn_->AppendHeader("Content-Type", "text/plain");
        std::string tags = tags_ + (jobtags.empty() ? std::string() : ","+jobtags );
        std::string msg = measurement+","+tags +" "+fieldvalpair+" "+std::to_string(timestamp);
        if(! msg.size() ) {
            msg_ = msg;
        }
        else if (msg_.size() < limit_) {
            msg_ += '\n'+msg; 
        }
        if(msg.size() > limit_) {
          RestClient::Response r = conn_->post("/api/v2/write?org="+org_+"&bucket="+bucket_+"&precision=s", msg_);
          msg_.clear();
        }
    }

