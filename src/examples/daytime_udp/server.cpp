#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>

#include <iostream>
#include <array>
#include <ctime>
#include <string>

using namespace boost::asio::ip;

std::string daytime_message()
{
    std::time_t now = std::time(nullptr);
    return std::string(std::ctime(&now));
}

int main(int argc, char** argv)
{
    try {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 50000));

        while (true) {
            std::array<char, 128> recv_buf;
            udp::endpoint remote_endpoint;
            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
            std::cout << "Received ping from remote (" << remote_endpoint.port() << "): " <<
                recv_buf.data() << std::endl; 
            std::string message = daytime_message();
            boost::system::error_code error;
            socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, error);
            if (error) {
                std::cerr << error << std::endl;
                break;
            }
        }

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
