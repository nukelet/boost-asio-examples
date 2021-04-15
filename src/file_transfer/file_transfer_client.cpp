#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>

#include <iostream>
#include <fstream>
#include <array>

using namespace boost::asio::ip;

#define CHUNK_SIZE 8192

int main(int argc, char** argv)
{
    try {
        if (argc != 3) {
            std::cerr << "Usage: file_transfer_client.o <host> <filename>" << std::endl; 
            return 1;
        }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
            resolver.resolve(argv[1], "50000");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);
       
        std::string filename = argv[2];
        std::ofstream file(filename, std::ios::binary);

        while (true) {
            std::array<char, CHUNK_SIZE> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(
                    boost::asio::buffer(buf),
                    error
                    );

            if (error == boost::asio::error::eof) {
                break; 
            }
            
            file.write(buf.data(), len);
        }

    } catch (std::error_code& error) {
        std::cerr << error.message() << std::endl;
        return 1;
    }
}
