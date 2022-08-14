#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <cstdio>
#include <stdexcept>

struct TimerClass {

  TimerClass(const char* name) {
    timeval tv;
    gettimeofday(&tv, nullptr);
    timestamp = tv.tv_usec;
    is_moved_from = false;
    size_t size = strlen(name);
    this->name = new char[size];
    std::strncpy(this->name, name, size);
  }

  ~TimerClass() {
    if (!is_moved_from) {
      timeval tv;
      gettimeofday(&tv, nullptr);
      suseconds_t age = tv.tv_usec - timestamp;
      std::cout << "age of timer " << name << ": " << age << std::endl;
      delete[] name;
    }
  }

  TimerClass(const TimerClass& other) : timestamp { other.timestamp } {
    size_t size = strlen(other.name);
    name = new char[size];
    std::strncpy(name, other.name, size);
  }

  TimerClass& operator=(const TimerClass& other) {
    if (this != &other) {
      delete[] name;
      timestamp = other.timestamp;
      size_t size = strlen(other.name);
      name = new char[size];
      std::strncpy(name, other.name, size);
    }
    return *this;
  }

  TimerClass(TimerClass&& other) noexcept :timestamp {other.timestamp}, name { other.name } {
    other.timestamp = 0;
    other.is_moved_from = true;
    other.name = nullptr;
  }

  TimerClass& operator=(TimerClass&& other) noexcept {
    if (this != &other) {
      delete[] name;
      timestamp = other.timestamp;
      name = other.name;
      other.timestamp = 0;
      other.is_moved_from = true;
      other.name = nullptr;
    }
    return *this;
  }
  
  suseconds_t timestamp;
  char* name;
private:
  bool is_moved_from;
};

struct SimpleString {

  SimpleString(size_t max_size) : max_size { max_size }, length{} {
    if (max_size == 0) {
      throw std::runtime_error{"max size must be at least 1"};
    }
    buffer = new char[max_size];
    buffer[0] = 0;
  }

  ~SimpleString() {
    delete[] buffer;
  }

  SimpleString(const SimpleString& other) : max_size{ other.max_size }, buffer{ new char[other.max_size] }, length{ other.length } {
    std::strncpy(buffer, other.buffer, other.max_size);
  }

  SimpleString& operator=(const SimpleString& other) {
    if (this != &other) {
      delete[] buffer;
      buffer = new char[other.max_size];
      length = other.length;
      max_size = other.max_size;
      std::strncpy(buffer, other.buffer, max_size);
    }
    return *this;
  }

  SimpleString(SimpleString&& other) noexcept
    : max_size{ other.max_size },
      buffer{ other.buffer },
      length {other.length} {
    other.max_size = 0;
    other.buffer = nullptr;
    other.length = 0;
  }

  SimpleString& operator=(SimpleString&& other) noexcept {
    if (this != &other) {
      delete[] buffer;
      max_size = other.max_size;
      buffer = other.buffer;
      length = other.length;
      other.max_size = 0;
      other.buffer = nullptr;
      other.length = 0;
    }
    return *this;
  }
  
  void print(const char* tag) const {
    printf("%s: %s", tag, buffer);
  }
  
  bool append_line(const char* x) {
    size_t x_len = strlen(x);
    if (x_len + length + 2 > max_size) {
      return false;
    }
    std::strncpy(buffer + length, x, x_len);
    length += x_len;
    buffer[length] = '\n';
    length += 1;
    buffer[length] = 0;
    return true;
  }
  
private:
  size_t max_size;
  char* buffer;
  size_t length;
};

int main(){
  const char* test = "abc123";
  std::cout << strlen(test) <<std::endl;
  TimerClass tm{"tm"};
  std::cout << "tm: " << tm.timestamp << std::endl;
  TimerClass tmcpy1{ tm };
  std::cout << "tmcpy1: " << tmcpy1.timestamp << std::endl;
  TimerClass tmcpy2 = tm;
  std::cout << "tmcpy2: " << tmcpy2.timestamp << std::endl;
  TimerClass tmmv {std::move(tm)};
  std::cout << "tmmv: " << tmmv.timestamp << std::endl;
  tm.timestamp = 0;
  std::cout << "tmmv: " << tmmv.timestamp << std::endl;
  std::cout << "tm: " << tm.timestamp << std::endl;
  TimerClass tmmvo = std::move(tmmv);
  std::cout << "tmmvo: " << tmmvo.timestamp << std::endl;

  TimerClass tmmath{ "math" };
  int a = 100000;
  while(a--) {}
  SimpleString simplestring{50};
  simplestring.append_line("have a nice day");
  simplestring.append_line("nice");
  simplestring.print("A");
  SimpleString sscopy {simplestring};
  sscopy.print("Copy");
  SimpleString sscopyop = simplestring;
  sscopyop.print("CopyOp");
  SimpleString ssmove {std::move(simplestring)};
  ssmove.print("Move");
  simplestring.print("MovedA");
  SimpleString ssmoveop = std::move(ssmove);
  ssmoveop.print("MoveOp");
  ssmove.print("Move");
  return 0;
}
