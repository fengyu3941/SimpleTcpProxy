#include "tcpproxy_server.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

tcpproxy_server::tcpproxy_server(unsigned short local_port,
        const std::string& ana_address,
        unsigned short ana_port,
        std::size_t thread_pool_size)
    :thread_pool_size_(thread_pool_size),
    acceptor_(io_service_),
    local_endpoint_(tcp::v4(), local_port),
    analysing_server_endpoint_(boost::asio::ip::address::from_string(ana_address), ana_port),
    new_connection_(new tcpproxy_connection(io_service_, analysing_server_endpoint_))
{
    acceptor_.open(local_endpoint_.protocol());
    acceptor_.set_option(tcp::acceptor::reuse_address(true));
    acceptor_.bind(local_endpoint_);
    acceptor_.listen();
    acceptor_.async_accept(new_connection_->login_clt_sock(),
            boost::bind(&tcpproxy_server::handle_accept,this,
                boost::asio::placeholders::error));
}

void tcpproxy_server::run()
{
    std::vector<boost::shared_ptr<boost::thread>> threads; 
    for(std::size_t i= 0; i < thread_pool_size_;++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
            boost::bind(&boost::asio::io_service::run,&io_service_)));
        threads.push_back(thread);
    }

    for(std::size_t i= 0; i < threads.size();++i)
    {
        threads[i]->join();
    }
}

void tcpproxy_server::stop()
{
    io_service_.stop();
}

void tcpproxy_server::handle_accept(const boost::system::error_code& e)
{
    if(!e)
    {
        new_connection_->start();
        new_connection_.reset(new tcpproxy_connection(io_service_,
            analysing_server_endpoint_));

        acceptor_.async_accept(new_connection_->login_clt_sock(),
            boost::bind(&tcpproxy_server::handle_accept,this,
                boost::asio::placeholders::error));
    }
}