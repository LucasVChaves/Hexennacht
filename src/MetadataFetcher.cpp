#include "MetadataFetcher.hpp"

MetadataFetcher::MetadataFetcher() {
  std::cout<< "Initializing Metadata Fetcher..." << std::endl; 
}

MetadataFetcher::~MetadataFetcher() {}

void MetadataFetcher::FetchMetadata(const std::string &file, const std::string &output_file) {
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
