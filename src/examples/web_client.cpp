#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <array>
#include <string>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::resolver resolv{ioservice};
tcp::socket tcp_socket{ioservice};
std::array<char, 4096> bytes;

int read_counter = 0;

void read_handler(const boost::system::error_code &ec,
        std::size_t bytes_transferred)
{
    if (!ec) {
        read_counter++;
        std::cout.write(bytes.data(), bytes_transferred);
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }

    else {
        std::cout << ec << std::endl;
    }

    std::cout << "terminating read_handler" << std::endl;
}

void connect_handler(const boost::system::error_code &ec)
{
    if (!ec) {
        std::string r =
            "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n"; 
        write(tcp_socket, buffer(r));
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }

    std::cout << "terminating connect_handler" << std::endl;
}

void resolve_handler(const boost::system::error_code &ec,
        tcp::resolver::iterator it)
{
    if (!ec) {
        tcp_socket.async_connect(*it, connect_handler);
    }

    std::cout << "terminating resolve_handler" << std::endl;
}

int main(int argc, char** argv)
{
    tcp::resolver::query q{"theboostcpplibraries.com", "80"};
    resolv.async_resolve(q, resolve_handler);
    ioservice.run();
    std::cout << "reads: " << read_counter << std::endl;
}
