#pragma once

#include "../csvreader/csvreader.hpp"

namespace func {
inline CSVReader<CSVRowCombi> csvreaderCombiner(CSVReader<CSVRow>& reader1,
                                                CSVReader<CSVRow>& reader2) {
    CSVReader<CSVRowCombi> csvreader_combi;
    for (int i = 0; i < reader1.size(); i++) {
        for (int j = 0; j < reader2.size(); j++) {
            try {
                auto row1 = reader1.get(i);
                auto row2 = reader2.get(j);
                if (row1 == row2) {
                    // 借书的行 == 还书的行，则结合两行数据并追加到链表尾部
                    CSVRowCombi row_combi(row1, row2);
                    csvreader_combi.append(row_combi);
                    break;
                };
                if (j == reader2.size() - 1) {
                    // 如果借书的行没有在还书记录找到，则设为`尚未归还`
                    CSVRowCombi row_combi(row1);
                    csvreader_combi.append(row_combi);
                };
            } catch (const runtime_error& exc) {
                cout << exc.what();
            }
        }
    }
    return csvreader_combi;
};
// 合并两个 csv
}  // namespace func
