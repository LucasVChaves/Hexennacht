#include "Hexdumper.hpp"

Hexdumper::Hexdumper() {
    std::cout << "Hexdumper created" << std::endl;
}

Hexdumper::~Hexdumper() {}

void Hexdumper::Hexdump(const std::string &file, const std::string &output_file) {
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
