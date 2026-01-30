# Mini Search Engine (C++)

A console-based search engine that indexes text files and allows keyword searching with ranked results.

## 🎯 Objective

Build a search engine that:
- Reads multiple `.txt` files from a folder
- Indexes words from files
- Searches keywords entered by user
- Shows file names where keywords appear
- Ranks files based on word frequency

## 🧠 Concepts Used (Interview-Friendly)

- `map<string, map<string, int>>` - Nested map for word-file-frequency mapping
- String processing and cleaning
- File handling with C++ streams
- Sorting algorithms
- Filesystem operations (C++17)

## 📁 Project Structure

```
MiniSearchEngine/
├── main.cpp          # Main program with user interface
├── indexer.cpp       # Indexer implementation
├── indexer.h         # Indexer class declaration
├── data/             # Sample text files
│   ├── file1.txt     # Data Structures & Algorithms
│   ├── file2.txt     # Machine Learning & AI
│   ├── file3.txt     # Web Development
│   └── file4.txt     # Cloud Computing & DevOps
└── README.md         # This file
```

## ⚙️ How It Works

1. **Indexing Phase:**
   - Read each `.txt` file from the `data/` directory
   - Break content into words
   - Clean words (lowercase, remove punctuation)
   - Store in index: `word → { file_name : frequency }`

2. **Search Phase:**
   - User enters a keyword
   - Look up keyword in the index
   - Display matching files sorted by frequency (highest first)

## 🔧 Compilation

### Using g++ (MinGW on Windows)

```bash
g++ -std=c++17 -o search_engine main.cpp indexer.cpp
```

### Using Visual Studio Developer Command Prompt

```bash
cl /EHsc /std:c++17 main.cpp indexer.cpp /Fe:search_engine.exe
```

## 🚀 Running the Program

```bash
./search_engine
```

Or on Windows:
```bash
search_engine.exe
```

## 📋 Features

1. **Search for a keyword** - Find files containing a specific word
2. **Display index statistics** - Show total words and files indexed
3. **Display full index** - Debug view of all indexed words
4. **Re-index files** - Reload files from a directory
5. **Exit** - Close the program

## 💡 Sample Usage

```
╔══════════════════════════════════════════╗
║       MINI SEARCH ENGINE (C++)           ║
║    Console-Based Keyword Search Tool     ║
╚══════════════════════════════════════════╝

=== Indexing files from: data ===
Indexed: file1.txt
Indexed: file2.txt
Indexed: file3.txt
Indexed: file4.txt
Total files indexed: 4

--- Menu ---
1. Search for a keyword
2. Display index statistics
3. Display full index (debug)
4. Re-index files
5. Exit
Enter choice: 1

Enter keyword to search: learning

✅ Found "learning" in 2 file(s):

+------+----------------------+------------+
| Rank |      File Name       | Frequency  |
+------+----------------------+------------+
|    1 | file2.txt            |          8 |
|    2 | file1.txt            |          1 |
+------+----------------------+------------+
```

## 🎓 Learning Outcomes

- Understanding of indexing and search concepts
- Practical use of STL containers (map, vector, set)
- File I/O operations in C++
- String manipulation and text processing
- Sorting with custom comparators
- Modern C++ filesystem library

## 📝 Interview Discussion Points

1. **Why use `map<string, map<string, int>>`?**
   - Efficient O(log n) lookup for words
   - Automatically sorted keys
   - Easy to track per-file frequencies

2. **How would you scale this?**
   - Use hash maps for O(1) lookup
   - Implement inverted index
   - Add TF-IDF ranking
   - Distribute across multiple machines

3. **What optimizations are possible?**
   - Stop word removal
   - Stemming (running → run)
   - Caching frequent queries
   - Concurrent file indexing

---

*Built as a portfolio project demonstrating C++ proficiency and understanding of search engine fundamentals.*
