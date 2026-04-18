#ifndef PATH_H
#define PATH_H

#include <filesystem>
#include <string>

std::filesystem::path sanitizePath(const std::filesystem::path &basePath, const std::filesystem::path &relativePath);

#endif // PATH_H