#include "EFile.h"

using namespace std;

std::string File::GetFilePath()
{
    return filesystem::current_path().string();
}

bool File::SetFilePath(const std::string& filepath)
{
    std::error_code ec;
    std::filesystem::current_path(filepath, ec);

    return !ec;
}
