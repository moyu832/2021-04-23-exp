#include "./csvreader.hpp"

template <class TT>
Chain<TT>::Chain() {
    m_first_node = nullptr;
    m_size = 0;
};

template <class TT>
void Chain<TT>::checkIndex(int index) {
    if (index < 0 || index >= m_size) {
        std::stringstream exc;
        exc << "*** Error ***" << std::endl;
        exc << "invalid index: " << index << endl;
        exc << "m_size: " << m_size << endl;
        exc << "*************" << endl;
        throw runtime_error(exc.str());
    };
};

template <class TT>
int Chain<TT>::index(TT& data) {
    Node<TT>* p = m_first_node;
    for (int i = 0; i < m_size; i++) {
        if (p->data == data) {
            // ::==:: operator overloading required
            return i;
        };
        p = p->next;
    };
    throw runtime_error("no matched index\n");
};

template <class TT>
TT& Chain<TT>::get(int index) {
    checkIndex(index);
    Node<TT>* p = m_first_node;
    for (int i = 0; i < index; i++) {
        p = p->next;
    };
    return p->data;
};

// template <class TT>
// TT& Chain<TT>::getByStudentCode(int code) {
//     Node<TT>* p = m_first_node;
//     for (int i = 0; i < m_size; i++) {
//         if ((p->data).code == code) {
//             return p->data;
//         };
//         p = p->next;
//     };
//     throw runtime_error("no matched student code\n");
// };

// template <class TT>
// TT& Chain<TT>::getByStudentName(const std::string& name) {
//     Node<TT>* p = m_first_node;
//     for (int i = 0; i < m_size; i++) {
//         if ((p->data).name == name) {
//             return p->data;
//         };
//         p = p->next;
//     };
//     throw runtime_error("no matched student name\n");
// };

template <class TT>
void Chain<TT>::append(TT& data) {
    if (m_size == 0) {
        m_first_node = new Node<TT>(data);
    } else {
        auto* p = m_first_node;
        for (int i = 0; i < m_size - 1; i++) {
            p = p->next;
        };
        p->next = new Node<TT>(data);
    };
    m_size++;
};

template <class TT>
void Chain<TT>::insert(int index, TT& data) {
    if (index < 0 || index > m_size) {
        // checkIndex only validate the index
        // but insert function allow insert to the end of chain
        throw runtime_error("invalid index to insert\n");
    }
    if (index == 0) {
        m_first_node = new Node<TT>(data);
    } else {
        auto* p = m_first_node;
        for (int i = 0; i < index - 1; i++) {
            p = p->next;
        };
        p->next = new Node<TT>(data, p->next);
    };
    m_size++;
};

template <class TT>
void Chain<TT>::erase(int index) {
    checkIndex(index);
    Node<TT>* delete_node = nullptr;
    if (index == 0) {
        delete_node = m_first_node;
        m_first_node = m_first_node->next;
    } else {
        auto* p = m_first_node;
        for (int i = 0; i < index - 1; i++) {
            // stay in the front of index, and delete the next
            p = p->next;
        }
        delete_node = p->next;
        p->next = p->next->next;
    }
    delete delete_node;
    m_size--;
};

template <class TT>
void Chain<TT>::display() const {
    Node<TT>* p = m_first_node;
    for (int i = 0; i < m_size; i++) {
        cout << "**********" << endl;
        cout << "索引  " << i << endl;
        // ::<<:: operator overloading required
        cout << p->data;
        p = p->next;
        if (i == m_size - 1) {
            cout << "**********" << endl;
        }
    }
};

CSVRow::CSVRow(istream& s) {
    // 参数 s: 单行数据，示例 `012345,2020440002,DK234,2011-6-5`
    next = nullptr;
    string cell;
    getline(s, cell, ',');
    account = cell;
    getline(s, cell, ',');
    identity = cell;
    getline(s, cell, ',');
    book = cell;
    getline(s, cell, ',');
    date = cell;
};

bool CSVRow::operator==(const CSVRow& r) const {
    return (account == r.account && identity == r.identity && book == r.book)
               ? true
               : false;
};

ostream& operator<<(ostream& out, const CSVRow& rr) {
    out << "account:   " << rr.account << endl;
    out << "identity:  " << rr.identity << endl;
    out << "book:      " << rr.book << endl;
    out << "date:      " << rr.date << endl;
    return out;
};

ofstream& operator<<(ofstream& file, const CSVRow& rr) {
    file << rr.account << ',';
    file << rr.identity << ',';
    file << rr.book << ',';
    file << rr.date << endl;
    return file;
};

CSVRowCombi::CSVRowCombi(const CSVRow& row_lend, const CSVRow& row_return) {
    // 合并两行的数据
    next = nullptr;
    account = row_lend.account;
    identity = row_lend.identity;
    book = row_lend.book;
    lend_date = row_lend.date;
    return_date = row_return.date.empty() ? "尚未归还" : row_return.date;
};

ostream& operator<<(ostream& out, const CSVRowCombi& rr) {
    out << "account:      " << rr.account << endl;
    out << "identity:     " << rr.identity << endl;
    out << "book:         " << rr.book << endl;
    out << "lend_date:    " << rr.lend_date << endl;
    out << "return_date:  " << rr.return_date << endl;
    return out;
}

ofstream& operator<<(ofstream& file, const CSVRowCombi& rr) {
    file << rr.account << ',';
    file << rr.identity << ',';
    file << rr.book << ',';
    file << rr.lend_date << ',';
    file << rr.return_date << endl;
    return file;
};

bool CSVRowCombi::operator==(const CSVRowCombi& r) const {
    return (account == r.account && identity == r.identity && book == r.book)
               ? true
               : false;
};

template <class TT>
CSVReader<TT>::CSVReader(istream& s) {
    string cell;
    while (getline(s, cell, '\n')) {
        stringstream cell_buffer;
        cell_buffer << cell;
        TT row_obj(cell_buffer);
        m_chain.append(row_obj);
    };
};

template <class TT>
void CSVReader<TT>::scanToFile(string& filepath) {
    ofstream file(filepath);
    const int chain_size = size();
    for (int i = 0; i < chain_size; i++) {
        file << this->get(i);
    };
    file.close();
};

template class Chain<CSVRow>;
template class Chain<CSVRowCombi>;

template class CSVReader<CSVRow>;
template class CSVReader<CSVRowCombi>;
