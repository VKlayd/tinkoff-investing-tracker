//
// Created by klayd on 7/4/20.
//

#include "HttpClientBuilderImplementation.hpp"
#include "HttpClientImplementation.hpp"
#include <HttpClient/HttpClient.hpp>

namespace HttpClient
{

HttpClient::HttpClient(HttpClient&& prev) noexcept : _pimpl(std::move(prev._pimpl)) {}
void HttpClient::sendRequest(const std::string& request)
{
    _pimpl->sendRequest(request);
}

std::string HttpClient::getResponse()
{
    return _pimpl->getResponse();
}

HttpClient::HttpClient() {}

HttpClient::~HttpClient() = default;
HttpClientBuilder::HttpClientBuilder() : _pimpl(std::make_unique<HttpClientBuilderImplementation>())
{
}

HttpClientBuilder& HttpClientBuilder::setUrl(const std::string& url)
{
    _pimpl->setUrl(url);
    return *this;
}

HttpClientBuilder& HttpClientBuilder::setPort(uint16_t port)
{
    _pimpl->setPort(port);
    return *this;
}

HttpClientBuilder& HttpClientBuilder::setBearer(const std::string& bearer)
{
    _pimpl->setBearer(bearer);
    return *this;
}

HttpClient HttpClientBuilder::build()
{
    auto result   = HttpClient();
    result._pimpl = _pimpl->build();
    return result;
}

HttpClientBuilder::~HttpClientBuilder() = default;

}// namespace HttpClient