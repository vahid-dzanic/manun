# manun
manun is a marshalling / unmarshalling library, which requires only a C++17 compatible compiler.

## installation
### prerequisites
cmake, c++17 capable compiler and [stdex](https://github.com/vahid-dzanic/stdex)

### build and install on linux
```bash
git clone https://github.com/vahid-dzanic/manun.git
mkdir -p manun/build
cd manun/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DMANUN_BUILD_WITH_EXAMPLE=OFF -DMANUN_BUILD_WITH_TESTS=OFF
sudo make install
```

## usage
```c++
//main.cpp
#include <manun/includes>
#include <iostream>

int main(int, char**) {

  std::cout << "input: ";
  std::vector<std::string> vec_input{"Hell", "o ", "World!"};
  for (const auto& val : vec_input) {
    std::cout << val;
  }
  std::cout << std::endl;

  ///////////////////////////////////////////////////////////////////////////////////
  // convert to string
  auto string_container = manun::convert::to_string(vec_input);
  ///////////////////////////////////////////////////////////////////////////////////

  std::cout << "serialized input: " << string_container << std::endl;

  ///////////////////////////////////////////////////////////////////////////////////
  // convert to back value
  std::vector<std::string> vec_output = manun::convert::to_value(string_container);
  ///////////////////////////////////////////////////////////////////////////////////

  std::cout << "output: ";
  for (const auto& val : vec_output) {
    std::cout << val;
  }
  std::cout << std::endl;

  return 0;
}
```

## License
[LGPLv3](https://choosealicense.com/licenses/lgpl-3.0/)
