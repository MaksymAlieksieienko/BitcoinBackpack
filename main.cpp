#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include "transaction.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Define the maximum block size (1MB = 1,000,000 bytes)
    const int MAX_BLOCK_SIZE = 1000000;

    // Check CSV file
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <transactions_csv_file>" << endl;
        return 1;
    }
    string csvFilename = argv[1];

    vector<Transaction> transactions;
    if (!readTransactions(csvFilename, transactions)) {
        return 1;
    }

    vector<Transaction> block;
    int currentBlockSize = 0;
    long long totalFee = 0;

    // Start block construction timing
    auto startTime = chrono::high_resolution_clock::now();

    // Sort transactions by fee-per-byte ratio in descending order
    sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
        double ratioA = static_cast<double>(a.tx_fee) / a.tx_size;
        double ratioB = static_cast<double>(b.tx_fee) / b.tx_size;
        return ratioA > ratioB;
        });

    // Add transactions until the block size limit is reached
    for (const auto& tx : transactions) {
        if (currentBlockSize + tx.tx_size <= MAX_BLOCK_SIZE) {
            block.push_back(tx);
            currentBlockSize += tx.tx_size;
            totalFee += tx.tx_fee;
        }
        if (currentBlockSize >= MAX_BLOCK_SIZE)
            break;
    }

    // End block construction timing
    auto endTime = chrono::high_resolution_clock::now();
    auto constructionTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

    // Obtain peak memory usage (using Windows API)
    PROCESS_MEMORY_COUNTERS pmc;
    SIZE_T peakMemory = 0;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        peakMemory = pmc.PeakWorkingSetSize;
    }

    cout << "=== Constructed Block ===" << endl;
    for (const auto& tx : block) {
        cout << tx.tx_id << endl;
    }
    cout << "\nNumber of transactions in the block: " << block.size() << endl;
    cout << "Block size: " << currentBlockSize << " bytes" << endl;
    cout << "Total extracted fee: " << totalFee << " satoshis" << endl;
    cout << "Construction time: " << constructionTime.count() << " ms" << endl;
    cout << "Peak memory usage: " << peakMemory / 1024 << " KB" << endl;
    cout << "Probability of extracted fee value being optimal: N/A (Greedy heuristic used)" << endl;

    return 0;
}