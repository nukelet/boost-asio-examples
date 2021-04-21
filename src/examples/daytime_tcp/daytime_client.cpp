#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>

#include <iostream>
#include <array>

using namespace boost::asio::ip;

int main(int argc, char** argv)
{
    try {
        if (argc != 2) {
            std::cout << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;

        // resolvers take a host name and a service name
        // and return a list of endpoints
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
            resolver.resolve(argv[1], "50000");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        while(true) {
            std::array<char, 4096> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }

    } catch (std::exception& e) {
        std::cout << "(exception) " << e.what() << std::endl;
    }
}
