// Source: https://github.com/simdjson/simdjson/blob/master/README.md
#include <iostream>
#include "simdjson.h"
using namespace simdjson;
int main(int argc, char** argv)
{
  ondemand::parser parser;
  padded_string json = padded_string::load(argv[1]);
  ondemand::document tweets = parser.iterate(json);
  std::cout << uint64_t(tweets["search_metadata"]["count"]) << " results." << std::endl;
}
