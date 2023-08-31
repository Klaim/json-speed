#include <iostream>
#include <filesystem>
#include <fstream>
#include <print>

#include <nlohmann/json.hpp>

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

    std::ifstream json_file{json_file_path};
    if (json_file.fail())
    {
        std::print(std::cerr,"failed to open file: '{}'", json_file_path.generic_string());
        return EXIT_FAILURE;
    }

    auto parsed_data [[maybe_unusued]] = nlohmann::json::parse(json_file);

}
