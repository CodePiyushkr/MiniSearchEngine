#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <map>
#include <vector>

class Indexer {
private:
    // word -> { filename : frequency }
    std::map<std::string, std::map<std::string, int>> index;
    
    // Helper function to clean and normalize words
    std::string cleanWord(const std::string& word);
    
public:
    // Index all .txt files from a directory
    void indexDirectory(const std::string& dirPath);
    
    // Index a single file
    void indexFile(const std::string& filePath);
    
    // Search for a keyword and return matching files with frequencies
    // Returns vector of pairs: (filename, frequency) sorted by frequency (descending)
    std::vector<std::pair<std::string, int>> search(const std::string& keyword);
    
    // Display all indexed words (for debugging)
    void displayIndex();
    
    // Get total number of indexed words
    int getTotalWords();
    
    // Get total number of indexed files
    int getTotalFiles();
};

#endif // INDEXER_H
