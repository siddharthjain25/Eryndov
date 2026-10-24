#pragma once
#include <string>
#include <filesystem>

inline std::string GetLatestNetworkName(const std::string& path) {
    int maxVersion = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path.empty() ? "." : path)) {
        if (entry.path().extension() == ".nnue") {
            std::string filename = entry.path().stem().string();
            if (filename.find("eryndov-") == 0) {
                try {
                    int version = std::stoi(filename.substr(8));
                    if (version > maxVersion) maxVersion = version;
                } catch (...) {}
            }
        }
    }
    if (maxVersion == 0) return "eryndov.nnue";
    char buf[32];
    snprintf(buf, sizeof(buf), "eryndov-%02d.nnue", maxVersion);
    return std::string(buf);
}
