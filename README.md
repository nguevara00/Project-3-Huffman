# Project 3: Huffman Encoding (Part 2 - BST and Priority Queue)

## Student Information
**Name:** Nicholas Guevara  
**Student ID:** 002-85-1971

## Collaboration & Sources

This project is my own work and I wrote the code myself, with the following collaboration:

I asked for conceptual assistance from ChatGPT for:
- Explaining the <optional> standard header
- Explaining errors and recommending alternative approaches in file and directory name handling for the input/output functions
- Verifying algorithm correctness (especially ordering logic in the priority queue and BST traversal)
- Troubleshooting differences produced by the test script
- Identifying redundant file validation statements

I asked for help from Dr. Kooshesh with regards to:
- Usage of the PriorityQueue class in this phase
- Output format for the PriorityQueue::print() function


## Implementation Details

- **Design** 
    -  Part 2 focuses on tokenizing input text, building a BST to count word frequences, constructing a priority queue using a vector, and generating the .tokens and .freq output files. The program also prints five required BST statistics to standard output.

- **Data Structures**
    - `BinSearchTree`** – Custom BST implementation with recursive insertion, traversal, and height calculation.  
        - Stores words and their counts.  
        - Provides `inorderCollect()` to produce a lexicographically sorted list of `(word, count)` pairs.  
    - **`PriorityQueue`** – Simulated priority queue implemented using `std::vector<TreeNode*>`.  
        - Sorted by descending frequency, ascending word (deterministic).  
        - Non-owning; memory is freed by the caller.  
        - Provides `insert`, `findMin`, `extractMin`, `deleteMin`, and `print`.  
    - **`TreeNode`** – Basic node structure holding a word, frequency, and left/right pointers.

- **Algorithms**
    - **BST Insertion:** Recursive, O(log n) average, O(n) worst case.  
    - **In-Order Traversal:** Lexicographic output of all nodes.  
    - **Priority Queue Construction:** Initial sort via `std::sort()`; insertion maintains sorted order.  
    - **File I/O:** Uses `std::ofstream` for writing `.tokens` and `.freq` with error handling provided by `utils.cpp`.

## Testing & Status

- **Status** Program successfully compiles, runs, and produces expected outputs.
- **Testing** Using the provided scripts on Blue, `.tokens` and `.freq` output matches reference outputs exactly.
- **Known Issues** None.
