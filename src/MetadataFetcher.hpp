#ifndef METADATAFETCHER_HPP
#define METADATAFETCHER_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <cstdio>
#include <string>

class MetadataFetcher {
public:
    MetadataFetcher();
    ~MetadataFetcher();
    void FetchMetadata(const std::string &file, const std::string &output_file = "");
};

#endif // !METADATAFETCHER_HPP
