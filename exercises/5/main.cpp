#include <cstdio>
#include <iostream>
#include <unordered_map>

struct Logger {
  virtual ~Logger() = default;
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {

  ConsoleLogger(const char* tag) : tag{ tag } {

  }
  
  void log_transfer(long from, long to, double amount) override {
    printf("[cons] %s %ld -> %ld: %f\n", tag, from, to, amount);
  }

private:
  const char* tag;
};

struct FileLogger : Logger {
  void log_transfer(long from, long to, double amount) override {
    printf("[file] %ld,%ld,%f\n", from, to, amount);
  }
};

struct AccountDatabase {
  virtual double retrieve(long id) = 0;
  virtual void setAmount(long id, double amounts) = 0;
  virtual ~AccountDatabase() = default;
};

struct Bank {
  Bank(AccountDatabase* accountDatabase) : accountDatabase{ accountDatabase } {

  }
  
  void set_logger(Logger* new_logger) {
    logger = new_logger;
  }
  void make_transfer(long from, long to, double amount) {
    accountDatabase->setAmount(from, accountDatabase->retrieve(from) - amount);
    accountDatabase->setAmount(to, accountDatabase->retrieve(to) + amount);
    
    if (logger) {
      logger->log_transfer(from, to, amount);
    }
  }
private:
  Logger* logger{};
  AccountDatabase* accountDatabase;
};

struct InMemoryAccountDatabase : AccountDatabase {

  InMemoryAccountDatabase() {

  }

  double retrieve(long id) override {
    std::cout << "account " << id << ": " << database[id] << std::endl;
    return database[id];
  }

  void setAmount(long id, double amounts) override {
    database[id] = amounts;
  }
  std::unordered_map<long, double> database;
};

int main() {
  InMemoryAccountDatabase db;
  db.setAmount(1001, 2000);
  db.retrieve(1001);
  Bank bank {&db};
  ConsoleLogger logger {"console logger"};
  db.setAmount(1000, 10000);
  db.setAmount(2000, 5000);
  bank.set_logger(&logger);
  bank.make_transfer(1000, 2000, 4000);
  db.retrieve(1000);
  db.retrieve(2000);
  return 0;
}
