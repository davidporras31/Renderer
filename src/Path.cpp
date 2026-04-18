#include "../include/Path.h"

std::filesystem::path sanitizePath(const std::filesystem::path &basePath, const std::filesystem::path &relativePath)
{
    std::filesystem::path normalized = std::filesystem::weakly_canonical(basePath / relativePath);
    std::filesystem::path canonical = std::filesystem::weakly_canonical(basePath);
    if(normalized.string().find(canonical.string()) != 0)
        throw std::runtime_error("path traversal error: " + basePath.string() + " | " + relativePath.string());
    return normalized;
}