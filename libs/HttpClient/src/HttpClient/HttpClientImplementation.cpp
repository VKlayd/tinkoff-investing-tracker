//
// Created by klayd on 7/4/20.
//

#include "HttpClientImplementation.hpp"
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <sstream>
#include <thread>

namespace HttpClient
{

struct MethodClass
{
private:
    MethodClass();

public:
    MethodClass(std::ostream* stream) : mStream(stream), writeRound(0) {}

    // Helper Class for reading result from remote host
    size_t write(curlpp::Easy* handle, char* ptr, size_t size, size_t nmemb)
    {
        ++writeRound;

        curlpp::options::Url url;
        handle->getOpt(url);

        // Calculate the real size of the incoming buffer
        size_t realsize = size * nmemb;
        //std::cerr << "write round: " << writeRound << ", url: " << url.getValue() << std::endl;
        mStream->write(ptr, realsize);
        // return the real size of the buffer...
        return realsize;
    };

    // Public member vars
    std::ostream* mStream;
    unsigned writeRound;
};

HttpClientImplementation::HttpClientImplementation()
{
    try
    {
        curlpp::initialize();
    }
    catch (curlpp::LogicError& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError& e)
    {
        std::cout << e.what() << std::endl;
    }
}
void HttpClientImplementation::sendRequest(const std::string& req)
{
    if (!_url.has_value())
    {
        throw std::runtime_error("URL is not defined");
    }
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    request.setOpt(new curlpp::options::Url(_url.value() + req));

    std::list<std::string> httpHeader;
    httpHeader.emplace_back("accept: application/json");
    if (_bearer.has_value())
    {
        httpHeader.emplace_back("Authorization: Bearer " + _bearer.value());
    }

    request.setOpt(new curlpp::options::HttpHeader(httpHeader));

    std::ostringstream output;
    MethodClass mObject(&output);
    // Set the writer callback to enable cURL
    // to write result in a memory area
    using namespace std::placeholders;
    curlpp::options::WriteFunction* test = new curlpp::options::WriteFunction(
            std::bind(&MethodClass::write, &mObject, &request, _1, _2, _3));
    request.setOpt(test);

    // Even easier version. It does the same thing
    // but if you need to download only an url,
    // this is the easiest way to do it.

    request.perform();
    _responses.emplace(output.str());
}
void HttpClientImplementation::setUrl(const std::string& url)
{
    _url = url;
}
void HttpClientImplementation::setPort(uint16_t port)
{
    _port = port;
}
void HttpClientImplementation::setBearer(const std::string& bearer)
{
    _bearer = bearer;
}
std::string HttpClientImplementation::getResponse()
{
    auto result = _responses.front();
    _responses.pop();
    return result;
}
}// namespace HttpClient