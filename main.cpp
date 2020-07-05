#include <HttpClient/HttpClient.hpp>
#include <cxxopts.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

int main(int argc, char** argv)
{
    cxxopts::Options options("Tinkoff Watcher",
                             "Program to fetch and store the account information.");
    options.add_options()("t,token", "Tinkoff token", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);
    auto token  = result["token"].as<std::string>();

    auto client = HttpClient::HttpClientBuilder()
                          .setBearer(token)
                          .setUrl("https://api-invest.tinkoff.ru/openapi/")
                          .build();
    client.sendRequest("portfolio");
    auto response = client.getResponse();

    using json        = nlohmann::json;
    auto jsonResponse = json::parse(response);

    std::cout << jsonResponse.dump(4) << std::endl;
}
