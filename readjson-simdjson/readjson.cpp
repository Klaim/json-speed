#include <iostream>
#include <filesystem>
#include <fstream>
#include <print>
#include <thread>
#include <chrono>

#include <simdjson.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::print(std::cerr, "error: missing path to json file");
        return EXIT_FAILURE;
    }

    const auto json_file_path = std::filesystem::absolute(argv[1]);

    if (not std::filesystem::exists(json_file_path))
    {
        std::print(std::cerr,"path does not exist: '{}'", json_file_path.generic_string());
        return EXIT_FAILURE;
    }

    if (std::filesystem::is_directory(json_file_path))
    {
        std::print(std::cerr,"path is a directory: '{}'", json_file_path.generic_string());
        return EXIT_FAILURE;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    {
        using namespace simdjson;
        ondemand::parser parser;
        // std::print("read: '{}'", json_file_path.generic_string());
        padded_string json = padded_string::load(json_file_path.generic_string());
        ondemand::document tweets = parser.iterate(json);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
