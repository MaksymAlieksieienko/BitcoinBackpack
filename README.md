# BitcoinBlockBuilder

This C++ console application builds a Bitcoin block by selecting transactions from a CSV file. The aim is to maximize the total fee while ensuring the block size does not exceed 1 MB.

## Task Description

The program processes a CSV file where each line includes three parameters:
- **tx_id** – Unique transaction identifier.
- **tx_size** – Transaction size in bytes.
- **tx_fee** – Transaction fee in satoshi.

### Requirements:
- The input file can contain up to 100,000 transactions.
- The block size must not exceed 1,000,000 bytes (1 MB).
- Transactions are chosen to maximize the total fee.

### Algorithm:
The project uses a greedy algorithm:
1. **Read CSV Data:** Import transactions from the CSV file.
2. **Sort Transactions:** Order transactions by their fee-to-size ratio (tx_fee/tx_size) in descending order.
3. **Build Block:** Add transactions sequentially until the block size limit is reached.

- **Time Complexity:** O(n log n) (due to sorting)
- **Space Complexity:** O(n)

*Note:* While the greedy approach is very efficient, it does not always guarantee the absolute optimal solution, unlike dynamic programming approaches.

## Project Structure

- **main.cpp** – Contains the main logic: reading the CSV file, sorting transactions, building the block, and measuring time and memory.
- **transaction.h** – Defines the `Transaction` structure.
- **utils.h** – Provides auxiliary functions for reading transactions from a CSV file.
- **transactions.csv** – A sample CSV file for testing. Example format:
  ```
  tx_id,tx_size,tx_fee
  tx1,250,5000
  tx2,300,7500
  ...
  ```

## Compilation and Execution

### Compilation

**Using g++ (e.g., on Windows with MinGW):**
1. Open a terminal and navigate to the directory containing `main.cpp`.
2. Compile with:
   ```bash
   g++ -std=c++17 -O2 main.cpp -o BitcoinBlockBuilder -lpsapi
   ```

**Using Visual Studio:**
1. Create a new Console App project.
2. Add `main.cpp`, `transaction.h`, and `utils.h` to the project.
3. Ensure the C++ language standard is set to ISO C17 (/std:c17).
4. Build the project.

### Running

1. Ensure that `transactions.csv` is in the same directory as the executable.
2. Run the program from the command line:
   ```bash
   ./BitcoinBlockBuilder transactions.csv
   ```
3. The program will display:
   - List of selected transaction IDs.
   - Number of transactions included in the block.
   - Total block size in bytes.
   - Total transaction fee (extracted commission, multiplied by 100).
   - Block construction time in milliseconds.
   - Peak memory usage.

## Performance Measurement

- **Construction Time:**  
  Measured using `std::chrono::high_resolution_clock`.

- **Memory Usage:**  
  Peak memory is determined via the Windows API `GetProcessMemoryInfo`, providing an overall estimate of consumed memory during execution.