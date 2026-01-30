#include "indexer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <windows.h>

// Helper function to extract filename from path
std::string getFileName(const std::string& path) {
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

std::string Indexer::cleanWord(const std::string& word) {
    std::string cleaned;
    for (char c : word) {
        if (std::isalnum(c)) {
            cleaned += std::tolower(c);
        }
    }
    return cleaned;
}

void Indexer::indexFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Cant open: " << filePath << std::endl;
        return;
    }
    
    // Extract just the filename from the path
    std::string fileName = getFileName(filePath);
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        
        while (iss >> word) {
            std::string cleanedWord = cleanWord(word);
            if (!cleanedWord.empty()) {
                index[cleanedWord][fileName]++;
            }
        }
    }
    
    file.close();
    std::cout << "Indexed: " << fileName << std::endl;
}

void Indexer::indexDirectory(const std::string& dirPath) {
    std::cout << "\nReading files from: " << dirPath << std::endl;
    
    std::string searchPath = dirPath + "\\*.txt";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Cant find txt files in: " << dirPath << std::endl;
        return;
    }
    
    int fileCount = 0;
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::string fullPath = dirPath + "\\" + findData.cFileName;
            indexFile(fullPath);
            fileCount++;
        }
    } while (FindNextFileA(hFind, &findData) != 0);
    
    FindClose(hFind);
    
    if (fileCount == 0) {
        std::cout << "No txt files here." << std::endl;
    } else {
        std::cout << "Loaded " << fileCount << " files." << std::endl;
    }
}

std::vector<std::pair<std::string, int>> Indexer::search(const std::string& keyword) {
    std::vector<std::pair<std::string, int>> results;
    
    std::string cleanedKeyword = cleanWord(keyword);
    
    if (cleanedKeyword.empty()) {
        return results;
    }
    
    auto it = index.find(cleanedKeyword);
    if (it != index.end()) {
        for (const auto& fileFreq : it->second) {
            results.push_back({fileFreq.first, fileFreq.second});
        }
        
        // Sort by frequency in descending order
        std::sort(results.begin(), results.end(),
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second;
            });
    }
    
    return results;
}

void Indexer::displayIndex() {
    std::cout << "\nAll words:" << std::endl;
    for (const auto& wordEntry : index) {
        std::cout << "\"" << wordEntry.first << "\" -> ";
        for (const auto& fileFreq : wordEntry.second) {
            std::cout << "[" << fileFreq.first << ": " << fileFreq.second << "] ";
        }
        std::cout << std::endl;
    }
}

int Indexer::getTotalWords() {
    return index.size();
}

int Indexer::getTotalFiles() {
    std::set<std::string> files;
    for (const auto& wordEntry : index) {
        for (const auto& fileFreq : wordEntry.second) {
            files.insert(fileFreq.first);
        }
    }
    return files.size();
}
