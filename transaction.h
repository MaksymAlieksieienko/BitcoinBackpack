#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction {
    std::string tx_id;
    int tx_size;
    long long tx_fee;
};

#endif