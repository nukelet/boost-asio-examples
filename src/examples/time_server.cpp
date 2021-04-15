#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <string>
#include <ctime>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::endpoint tcp_endpoint{tcp::v4(), 50000};
tcp::socket tcp_socket{ioservice};
tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
std::string data;

void write_handler(const boost::system::error_code &ec,
        std::size_t bytes_transferred)
{
    if (!ec) {
        // tcp_socket.shutdown(tcp::socket::shutdown_send);
    }
}

void accept_handler(const boost::system::error_code &ec)
{
    if (!ec) {
        // std::time(TIME* t) returns the current time
        // and puts it in t if t is not nullptr
        std::time_t now = std::time(nullptr);
        data = std::ctime(&now);
        async_write(tcp_socket, buffer(data), write_handler);
        // tcp_acceptor.async_accept(tcp_socket, accept_handler);
    }
}

int main(int argc, char** argv)
{
    tcp_acceptor.listen();
    tcp_acceptor.async_accept(tcp_socket, accept_handler);
    ioservice.run();

    return 0;
}
