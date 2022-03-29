// Copyright 2022 Shevelyova Darya photodoshfy@gmail.com

#include <http_server.hpp>

namespace po = boost::program_options;  // from <boost/program_options.hpp>

int main(int argc, char *argv[]) {

  std::shared_ptr<std::timed_mutex> mutex =
      std::make_shared<std::timed_mutex>();
  std::shared_ptr<JsonStorage> storage =
      std::make_shared<JsonStorage>("../suggestions.json");
  std::shared_ptr<CallSuggestions> suggestions =
      std::make_shared<CallSuggestions>();

  // Проверяем аргументы командной строки.
  try {
    if (argc != 3) {
      std::cerr << "Usage: suggestion_server <address> <port>\n"
                << "Example:\n"
                << "    http-server-sync 0.0.0.0 8080\n";
      return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<uint16_t>(std::atoi(argv[2]));
    // io_context требуется для всех операций ввода/вывода
    net::io_context ioc{1};
    // Акцептор получает входящие соединения
    tcp::acceptor acceptor {ioc, { address, port }};
    std::thread{suggestion_updater, storage, suggestions, mutex}.detach();
    for (;;) {
      // Это получит новое соединение
      tcp::socket socket{ioc};
      // Блокируем, пока не получим соединение
      acceptor.accept(socket);
      // Запускаем сессию, передавая владение сокетом
      std::thread{std::bind(
                      &do_session,
                      std::move(socket),
                      suggestions,
                      mutex)}.detach();
    }
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
