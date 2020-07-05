//
// Created by klayd on 7/5/20.
//

#include "HttpClientBuilderImplementation.hpp"
namespace HttpClient
{
void HttpClientBuilderImplementation::setUrl(const std::string& url)
{
    _url = url;
}
void HttpClientBuilderImplementation::setPort(uint16_t port)
{
    _port = port;
}
void HttpClientBuilderImplementation::setBearer(const std::string& bearer)
{
    _bearer = bearer;
}
std::unique_ptr<HttpClientImplementation> HttpClientBuilderImplementation::build()
{
    auto result = std::make_unique<HttpClientImplementation>();
    if (_url.has_value())
    {
        result->setUrl(_url.value());
    }
    if (_port.has_value())
    {
        result->setPort(_port.value());
    }
    if (_bearer.has_value())
    {
        result->setBearer(_bearer.value());
    }
    return result;
}
}// namespace HttpClient
