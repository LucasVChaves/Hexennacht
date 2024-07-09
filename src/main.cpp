#include <iostream>
#include <string>
#include "../lib/CLI11.hpp" // Had to do with relative path otherwise vim would scream about it
#include "Hexdumper.hpp"

void fetchMetadata(const std::string &file, const std::string &output_file = "") {
    std::string command = "exiftool " + file;
    std::array<char, 128> buffer;
    std::string result;

    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Failed to run exiftool" << std::endl;
        return;
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    if (output_file.empty()) {
        std::cout << "Metadata for file " << file << ":\n" << result << std::endl;
    } else {
        std::ofstream ofs(output_file);
        if (!ofs) {
            std::cerr << "Failed to create output file: " << output_file << std::endl;
            return;
        }
        ofs << result;
        ofs.close();
    }
}

int main(int argc, char** argv) {
    CLI::App app("Metafetch: Metadata extraction and Hexdump");

    std::string file_path;
    std::string output_file;
    bool optHexdump = false;
    bool optFetchMetadata = false;
    bool optEditMetadata = false;
    bool optManipulateHex = false;

    app.add_option("-F, --file", file_path, "File to process")->required()->check(CLI::ExistingFile);
    app.add_option("-o, --output", output_file, "Path to output txt file");
    app.add_flag("-d, --hexdump", optHexdump, "Performs hexdump on file");
    app.add_flag("-f, --fetch-metadata", optFetchMetadata, "Fetches the file's metadata");
    app.add_flag("-e, --edit-metadata", optEditMetadata, "Enables the metadata editor");
    app.add_flag("-m, --hex-manipulation", optManipulateHex, "Enables hex manipulation");

    CLI11_PARSE(app, argc, argv);

    if(optHexdump){
        std::cout << "Hexdumping " + file_path << std::endl;
        if(!output_file.empty()) std::cout << "Writing output to " << output_file << std::endl;
        Hexdumper hexdumper;
        hexdumper.Hexdump(file_path, output_file);
    } 
    else if(optFetchMetadata) {
        std::cout << "Fetching metada from " + file_path << std::endl;
        if(!output_file.empty()) std::cout << "Writing output to " << output_file << std::endl;
        fetchMetadata(file_path, output_file);
    } 
    else if(optEditMetadata) {
        std::cout << "Opening metadata editor..." << std::endl;
        std::cout << "WIP" << std::endl;
    } 
    else if(optManipulateHex) {
        std::cout << "Opening hex editor..." << std::endl;
        std::cout << "WIP" << std::endl;
    }
    else {
        std::cerr << "A valid option is required." << std::endl;
        std::cout << "Try 'metafetch --help'." << std::endl;
    }

    return 0;
}
