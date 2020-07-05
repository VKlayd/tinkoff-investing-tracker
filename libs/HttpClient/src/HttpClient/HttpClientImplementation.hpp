//
// Created by klayd on 7/4/20.
//

#pragma once

#include <HttpClient/HttpClient.hpp>
#include <optional>
#include <queue>
#include <string>

namespace HttpClient
{
class HttpClientImplementation
{
public:
    HttpClientImplementation();
    void setUrl(const std::string&);
    void setPort(uint16_t);
    void setBearer(const std::string&);

    void sendRequest(const std::string&);
    std::string getResponse();

private:
    std::optional<std::string> _url;
    std::optional<uint16_t> _port;
    std::optional<std::string> _bearer;

    std::queue<std::string> _responses;
};
}// namespace HttpClient
