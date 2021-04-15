#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>

#include <iostream>
#include <ctime>
#include <string>

std::string make_daytime_string()
{
    std::time_t now = std::time(nullptr);
    return std::ctime(&now);
}

using namespace boost::asio::ip;

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 50000));

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string message = make_daytime_string();

            boost::system::error_code error;
            boost::asio::write(socket, boost::asio::buffer(message), error);
            if (error) {
                std::cout << error.message() << std::endl;
            }
        }
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
