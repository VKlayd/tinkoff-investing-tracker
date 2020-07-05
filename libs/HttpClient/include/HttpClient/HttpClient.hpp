//
// Created by klayd on 7/4/20.
//
#pragma once

#include <memory>

namespace HttpClient
{

class HttpClientImplementation;
class HttpClient
{
public:
    HttpClient(HttpClient&& prev) noexcept;
    ~HttpClient();

    void sendRequest(const std::string&);
    std::string getResponse();

private:
    HttpClient();
    std::unique_ptr<HttpClientImplementation> _pimpl;
    friend class HttpClientBuilder;
};

class HttpClientBuilderImplementation;

class HttpClientBuilder
{
public:
    HttpClientBuilder();
    HttpClientBuilder& setUrl(const std::string&);
    HttpClientBuilder& setPort(uint16_t);
    HttpClientBuilder& setBearer(const std::string&);
    HttpClient build();
    ~HttpClientBuilder();

    HttpClientBuilder(const HttpClientBuilder&) = delete;
    HttpClientBuilder(HttpClientBuilder&&) noexcept;

private:
    std::unique_ptr<HttpClientBuilderImplementation> _pimpl;
};

}// namespace HttpClient
