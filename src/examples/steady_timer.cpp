#include <boost/asio/steady_timer.hpp>
#include <boost/asio/io_service.hpp>

#include <iostream>
#include <chrono>
#include <thread>

using namespace boost::asio;

int main(int argc, char** argv) 
{
    io_service ioservice;

    steady_timer timer{ioservice, std::chrono::seconds{2}};
    timer.async_wait([](const boost::system::error_code &ec) {
            std::cout << "message 1\n";
            });

    steady_timer timer2{ioservice, std::chrono::seconds{2}};
    timer2.async_wait([](const boost::system::error_code &ec) {
            std::cout << "message 2\n";
            });

    std::thread thread1{[&ioservice]() { ioservice.run(); }};
    std::thread thread2{[&ioservice]() { ioservice.run(); }};
    
    thread1.join();
    thread2.join();

    return 0;
}
