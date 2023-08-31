#include <iostream>
#include <filesystem>
#include <fstream>
#include <print>
#include <chrono>
#include <thread>

#include <boost/json.hpp>

auto read_file(std::ifstream& stream) -> std::string
{
    constexpr auto read_size = std::size_t(4096);
    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size))
    {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

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
        std::print(std::cerr, "path does not exist: '{}'", json_file_path.generic_string());
        return EXIT_FAILURE;
    }

    if (std::filesystem::is_directory(json_file_path))
    {
        std::print(std::cerr, "path is a directory: '{}'", json_file_path.generic_string());
        return EXIT_FAILURE;
    }

    std::ifstream json_file{json_file_path};
    if (json_file.fail())
    {
        std::print(std::cerr, "failed to open file: '{}'", json_file_path.generic_string());
        return EXIT_FAILURE;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    const auto json_data = read_file(json_file);

    boost::json::parser parser;
    parser.write(json_data);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
