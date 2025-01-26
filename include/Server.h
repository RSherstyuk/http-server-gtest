#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>

#include "FileHandler.h"
#include "Logger.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Server {
public:
  Server(const std::string &addres, unsigned short port);
  void run();

private:
  void handle_request(http::request<http::string_body> &req,
                      http::response<http::string_body> &resp);
  void start_accept();
  void hande_accept(beast::error_code ec, tcp::socket socket);

  net::io_context ioc_;
  tcp::acceptor acceptor_;
};

#endif