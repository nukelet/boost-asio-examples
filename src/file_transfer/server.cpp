#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>

#include <iostream>
#include <fstream>
#include <string>

using namespace boost::asio::ip;

#define CHUNK_SIZE 8192

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: file_transfer_server.o <filename>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    std::ifstream file(filename, std::ios::binary);
    char buf[CHUNK_SIZE];

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context,
            tcp::endpoint(tcp::v4(), 50000));
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    do {
        file.read(buf, CHUNK_SIZE);
        boost::system::error_code error;
        socket.write_some(
                boost::asio::buffer(buf, file.gcount()),
                error);

        if (error) {
            std::cout << error.message() << std::endl;
        }
    } while (file.gcount() > 0);
}
