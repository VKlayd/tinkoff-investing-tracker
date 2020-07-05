//
// Created by klayd on 7/5/20.
//

#pragma once

#include "HttpClientImplementation.hpp"

namespace HttpClient
{
class HttpClientBuilderImplementation
{
public:
    void setUrl(const std::string&);
    void setPort(uint16_t);
    void setBearer(const std::string&);
    std::unique_ptr<HttpClientImplementation> build();

private:
    std::optional<std::string> _url;
    std::optional<uint16_t> _port;
    std::optional<std::string> _bearer;
};
}// namespace HttpClient
