#include <iostream>
#include <string>
#include <limits>
#include "indexer.h"

void displayHeader() {
    std::cout << "\n";
    std::cout << "========================================" << std::endl;
    std::cout << "        Mini Search Engine" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\n";
}

void displayMenu() {
    std::cout << "\nWhat do you want to do?" << std::endl;
    std::cout << "1. Search a word" << std::endl;
    std::cout << "2. Show stats" << std::endl;
    std::cout << "3. Show all indexed words" << std::endl;
    std::cout << "4. Reload files" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << "> ";
}

void performSearch(Indexer& indexer) {
    std::string keyword;
    std::cout << "\nType a word: ";
    std::cin >> keyword;
    
    auto results = indexer.search(keyword);
    
    if (results.empty()) {
        std::cout << "\nNothing found for \"" << keyword << "\"" << std::endl;
    } else {
        std::cout << "\nFound \"" << keyword << "\" in " << results.size() << " file(s):" << std::endl;
        std::cout << "\n Rank   File                   Count" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        
        int rank = 1;
        for (const auto& result : results) {
            printf(" %3d    %-20s   %d\n", rank++, result.first.c_str(), result.second);
        }
    }
}

void displayStats(Indexer& indexer) {
    std::cout << "\nStats:" << std::endl;
    std::cout << "Words: " << indexer.getTotalWords() << std::endl;
    std::cout << "Files: " << indexer.getTotalFiles() << std::endl;
}

int main() {
    displayHeader();
    
    Indexer indexer;
    
    // Default data directory path (relative to executable)
    std::string dataDir = "data";
    
    // Index all files in the data directory
    indexer.indexDirectory(dataDir);
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        std::cin >> choice;
        
        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                performSearch(indexer);
                break;
            case 2:
                displayStats(indexer);
                break;
            case 3:
                indexer.displayIndex();
                break;
            case 4:
                std::cout << "Folder path (leave empty for 'data'): ";
                {
                    std::string newDir;
                    std::getline(std::cin, newDir);
                    if (newDir.empty()) {
                        newDir = "data";
                    }
                    indexer = Indexer(); // Reset indexer
                    indexer.indexDirectory(newDir);
                }
                break;
            case 5:
                running = false;
                std::cout << "\nBye!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid option, try again." << std::endl;
        }
    }
    
    return 0;
}
