#include "Server.h"

Server::Server(const std::string &address, unsigned short port)
    : ioc_(), acceptor_(ioc_, {net::ip::make_address(address), port}) {
  Logger::log("Server started on " + address + ":" + std::to_string(port));
  start_accept();
}

void Server::run() { ioc_.run(); }

void Server::start_accept() {
  acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
    if (!ec) {
      Logger::log("New connection accepted");
      hande_accept(ec, std::move(socket));
    }
    start_accept();
  });
}

void Server::hande_accept(beast::error_code ec, tcp::socket socket) {
  if (ec) {
    Logger::error("Error accepting connection: " + ec.message());
    return;
  }

  beast::flat_buffer buffer;
  http::request<http::string_body> req;
  http::read(socket, buffer, req);

  http::response<http::string_body> res;
  handle_request(req, res);

  http::write(socket, res);
}

void Server::handle_request(http::request<http::string_body> &req,
                            http::response<http::string_body> &res) {
  std::string path = req.target().to_string();
  Logger::log("Handling request: " + std::string(req.method_string()) + " " +
              path);

  if (req.method() == http::verb::get) {
    std::string content = FileHandler::read_file(path);
    if (!content.empty()) {
      res.result(http::status::ok);
      res.body() = content;
    } else {
      res.result(http::status::not_found);
      res.body() = "File not found";
    }
  } else if (req.method() == http::verb::post) {
    if (FileHandler::whrite_file(path, req.body())) {
      res.result(http::status::created);
      res.body() = "File created";
    } else {
      res.result(http::status::internal_server_error);
      res.body() = "Failed to create file";
    }
  } else if (req.method() == http::verb::delete_) {
    if (FileHandler::delete_file(path)) {
      res.result(http::status::ok);
      res.body() = "File deleted";
    } else {
      res.result(http::status::internal_server_error);
      res.body() = "Failed to delete file";
    }
  } else {
    res.result(http::status::bad_request);
    res.body() = "Unsupported HTTP method";
  }

  res.prepare_payload();
}