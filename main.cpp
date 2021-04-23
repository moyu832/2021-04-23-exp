#include "csvreader/csvreader.hpp"
#include "func/func.hpp"
#include "pch/pch.hpp"

int main() {
    // due to filesystem absolute path required c++17, impl downgrade to string
    string file_lend_path = "./test/lend.csv";
    string file_return_path = "./test/return.csv";
    string out_path = "./out.csv";
    // 将借书表存为 chain_lend
    ifstream filelend(file_lend_path);
    CSVReader<CSVRow> chain_lend(filelend);
    filelend.close();
    // 将还书表存为 chain_return
    ifstream filereturn(file_return_path);
    CSVReader<CSVRow> chain_return(filereturn);
    filereturn.close();
    CSVReader<CSVRowCombi> chain_combi =
        func::csvreaderCombiner(chain_lend, chain_return);
    chain_combi.scanToFile(out_path);
    return 0;
}
