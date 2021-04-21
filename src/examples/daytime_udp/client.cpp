#include <boost/asio/ip/udp.hpp>
#include <boost/asio/io_context.hpp>

#include <iostream>
#include <array>

using namespace boost::asio::ip;

int main(int argc, char** argv)
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: client.o <host>" << std::endl;
        }

        boost::asio::io_context io_context;
        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint = *resolver.resolve(udp::v4(), argv[1], "50000").begin();

        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> buf = {{ 0 }};
        socket.send_to(boost::asio::buffer(buf), receiver_endpoint);

        std::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), len);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
