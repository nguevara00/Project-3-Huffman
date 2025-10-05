
# Project 3: Huffman Encoding (Part 1 – Scanner)

## Student Information
**Name:** Nick Guevara  
**Student ID:** 002-85-1971
**Repository:** https://github.com/nguevara00/Project-3-Huffman.git

## Collaboration & Sources
- This project is my own work, but I asked for assistance from ChatGPT for examples on filesystem syntax, and to help visualize the tokenization logic. I wrote the code myself. 



## Implementation Details
- **Design:** The program reads an input text file and generates an output file containing each token on a separate line.

- **Data Structures:**  
  - `std::vector<std::string>` is used to store tokens in memory.  
  - `std::filesystem::path` is used to handle input and output file paths. 
- **Algorithms:**  
  - Valid characters are read sequentially
  - `readWord()` implements token extraction according to the specification.  
  - Output is written line by line using `writeVectorToFile()` from the utilities.

## Testing & Status
- **Status:** Scanner successfully tokenizes text files into `.tokens` files in `input_output/`.  
- **Testing:**  Using the scripts on blue, the program successfully compiles, runs, and produces a valid .tokens output. Diff on the tokens file and the reference tokens file returns no output, so the program is successful.
- **Known Issues:** The sample input file included a non-ASCII apostrophe, so it is ignored per the specification and the Poe's is tokenized as "poe", "s".
