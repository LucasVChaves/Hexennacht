#include <iostream>
#include <string>
#include "CLI11.hpp"

void hexdump(const std::string &file, const std::string &output_file = "") {
    std::ifstream ifs(file, std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open file: " << file << std::endl;
        return;
    }

    std::ostream *out_stream = &std::cout;
    std::ofstream ofs;
    if (!output_file.empty()) {
        ofs.open(output_file, std::ios::binary);
        if (!ofs) {
            std::cerr << "Failed to open output file: " << output_file << std::endl;
            return;
        }
        out_stream = &ofs;
    }

    char buffer[16];
    size_t offset = 0;
    while (ifs.read(buffer, sizeof(buffer)) || ifs.gcount() > 0) {  
        (*out_stream) << std::setw(8) << std::setfill('0') << std::hex << offset << "  ";
        
        for (size_t i = 0; i < ifs.gcount(); ++i) {
            (*out_stream) << std::setw(2) << std::setfill('0') << std::hex << (unsigned int)(unsigned char)buffer[i] << " ";
        }

        if (ifs.gcount() < 16) {
            for (size_t i = ifs.gcount(); i < 16; ++i) {
                (*out_stream) << "   ";
            }
        }

        (*out_stream) << " ";
        for (size_t i = 0; i < ifs.gcount(); ++i) {
            char c = buffer[i];
            if (std::isprint(c)) {
                (*out_stream) << c;
            } else {
                (*out_stream) << ".";
            }
        }

        (*out_stream) << std::endl;
        offset += ifs.gcount();
    }

    if (ofs.is_open()) {
        ofs.close();
    }
}

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

  app.add_option("-F, --file", file_path, "File to process")->required()->check(CLI::ExistingFile);
  app.add_option("-o, --output", output_file, "Path to output txt file");
  app.add_flag("-d, --hexdump", optHexdump, "Performs hexdump on file");
  app.add_flag("-f, --fetch-metadata", optFetchMetadata, "Fetches the file's metadata");
  app.add_flag("-e, --edit-metadata", optEditMetadata, "Enables the metadata editor");

  CLI11_PARSE(app, argc, argv);

  if(optHexdump){
    std::cout << "Hexdumping " + file_path << std::endl;
    if(!output_file.empty()) std::cout << "Writing output to " << output_file << std::endl;
    hexdump(file_path, output_file);
  }
  
  if(optFetchMetadata) {
    std::cout << "Fetching metada from " + file_path << std::endl;
    if(!output_file.empty()) std::cout << "Writing output to " << output_file << std::endl;
    fetchMetadata(file_path, output_file);
  }

  if(optEditMetadata) {
    std::cout << "Opening metadata editor..." << std::endl;
    //TODO
  }

  return 0;
}
