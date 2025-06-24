#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "transaction.h"

inline bool readTransactions(const std::string& filePath, std::vector<Transaction>& transactions) {
    std::ifstream csvFile(filePath);
    if (!csvFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return false;
    }

    std::string line;
    bool headerSkipped = false;
    while (std::getline(csvFile, line)) {
        // Skip header line if present
        if (!headerSkipped) {
            if (line.find("tx_id") != std::string::npos) {
                headerSkipped = true;
                continue;
            }
            headerSkipped = true;
        }

        std::stringstream ss(line);
        std::string token;
        Transaction tx;

        // Extract transaction ID
        if (!std::getline(ss, token, ',')) continue;
        tx.tx_id = token;

        // Extract transaction size (in bytes)
        if (!std::getline(ss, token, ',')) continue;
        try {
            tx.tx_size = std::stoi(token);
        }
        catch (...) {
            std::cerr << "Invalid transaction size: " << token << std::endl;
            continue;
        }

        // Extract transaction fee
        if (!std::getline(ss, token, ',')) continue;
        try {
            tx.tx_fee = std::stoll(token);
        }
        catch (...) {
            std::cerr << "Invalid transaction fee: " << token << std::endl;
            continue;
        }

        transactions.push_back(tx);
    }

    csvFile.close();
    return true;
}

#endif