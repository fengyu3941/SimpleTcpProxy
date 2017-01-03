#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class tcpproxy_connection:public boost::enable_shared_from_this<tcpproxy_connection>,
    private boost::noncopyable
{
public:
    //Contruct a connection with the given io_service, the analysing server address and port

    explicit tcpproxy_connection(boost::asio::io_service& io_service, 
            tcp::endpoint& ana_endpoint);

    ~tcpproxy_connection();

    //Start the asyncronous connection to analysing server

    void start();

    tcp::socket& login_clt_sock();

private:
    //Handle completion of connection to analysing server

    void handle_connect_to_ana_server(const boost::system::error_code& e);

    //Handle completion of login client socket read

    void handle_login_clt_sock_read(const boost::system::error_code& e, 
            std::size_t bytes_transferred);

    //Handle completion of analysing server socket write

    void handle_ana_srv_sock_write(const boost::system::error_code& e);

    //Handle completion of analysing server socket read

    void handle_ana_srv_sock_read(const boost::system::error_code& e, 
            std::size_t bytes_transferred);

    //Handle completion of login client socket write

    void handle_login_clt_sock_write(const boost::system::error_code& e);

    //Strand to ensure the connection's handles are not called concurrently

    boost::asio::io_service::strand strand_;

    //analysing server endpoint

    tcp::endpoint ana_endpoint_;

    //socket to the flex login client

    tcp::socket login_clt_sock_;

    //socket to analysing server

    tcp::socket ana_srv_sock_;

    //buffer used to recieve data from the login client

    boost::array<char, 1024> clt_buffer_;
    
    //buffer used to recieve data from the analysing server

    boost::array<char, 1024> srv_buffer_;
};

typedef boost::shared_ptr<tcpproxy_connection> tcpproxy_connection_ptr;