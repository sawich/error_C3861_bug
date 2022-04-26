// error_C3861_bug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <spanstream>

template<class T>
concept CIStream = requires { std::derived_from<T, std::basic_istream<typename T::char_type, typename T::traits_type>>; };

template <CIStream TStream>
class basic_ibinarystream : public TStream
{
public:
  using stream_type = TStream;

  [[nodiscard]] auto int8(void)->int8_t
  {
    return 0;
  }

  [[nodiscard]] auto uint8(void)->uint8_t
  {
    return 0;
  }

  [[nodiscard]] auto int16(void)->int16_t
  {
    return 0;
  }

  [[nodiscard]] auto uint16(void)->uint16_t
  {
    return 0;
  }

  [[nodiscard]] auto int32(void)->int32_t
  {
    return 0;
  }

  [[nodiscard]] auto uint32(void)->uint32_t
  {
    return 0;
  }

  [[nodiscard]] auto int64(void)->int64_t
  {
    return 0;
  }

  [[nodiscard]] auto uint64(void)->uint64_t
  {
    return 0;
  }

  [[nodiscard]] auto single(void)->float_t
  {
    return 0;
  }

  template <std::regular T>
  [[nodiscard]] auto scalar(void)->T
  {
    return T{};
  }

  template<typename ...Args>
  basic_ibinarystream(Args &&... _args) : TStream{ std::forward<Args>(_args)... }
  {}
};

template<class T>
concept CIBinaryStream = requires { std::derived_from<T, basic_ibinarystream<typename T::stream_type>>; };

template <CIBinaryStream TIBinaryStream>
class basic_ichunkstream : public TIBinaryStream
{
public:
  auto test() -> void
  {
    // Ok
    this->single();
    
    // Ok
    TIBinaryStream::single();
    
    // error C3861: 'single': identifier not found
    single();
  }

  template<typename ...Args>
  basic_ichunkstream(Args &&... _args) : TIBinaryStream{ std::forward<Args>(_args)... }
  {}
};

using ispanbinarystream = basic_ibinarystream<std::ispanstream>;
using ispanchunkstream = basic_ichunkstream<ispanbinarystream>;

int main()
{
  std::span<char> span;
  ispanchunkstream s{ span };
  s.test();
}