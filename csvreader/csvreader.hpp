#pragma once

#include "../pch/pch.hpp"

template <class TT>
struct Node {
    explicit Node(const TT data, Node<TT>* next = nullptr)
        : data(data), next(next){};

    TT data;
    Node<TT>* next;
};

template <class TT>
class Chain {
  public:
    Chain();
    void checkIndex(int index);
    int length() { return m_size; };
    int index(TT& data);             // get the index of data if matched
    TT& get(int index);              // get data by node's index
    TT& getByStudentCode(int code);  // iter table, return matched record one
    TT& getByStudentName(const std::string& name);  // return matched record one
    void append(TT& data);
    void insert(int index, TT& data);
    void erase(int index);
    void display() const;

  private:
    Node<TT>* m_first_node;
    int m_size;
};

struct CSVRow {
    CSVRow() { next = nullptr; };
    explicit CSVRow(istream& s);
    friend ostream& operator<<(ostream& out, const CSVRow& rr);
    // 重载结构体 CSVRow 的流输出运算符
    friend ofstream& operator<<(ofstream& file, const CSVRow& rr);
    // 输出到文件流的运算符
    bool operator==(const CSVRow& r) const;
    // 重载 CSVRow 之间的比较运算符
    // 比较依据为 `account`, `identity`, `book`

    string account;
    string identity;
    string book;
    string date;
    CSVRow* next;
};

struct CSVRowCombi {
    CSVRowCombi() = default;
    explicit CSVRowCombi(istream& /*s*/) { next = nullptr; };
    explicit CSVRowCombi(const CSVRow& row_lend,
                         const CSVRow& row_return = CSVRow());
    friend ostream& operator<<(ostream& out, const CSVRowCombi& rr);
    // 重载结构体 CSVRow 的流输出运算符
    friend ofstream& operator<<(ofstream& file, const CSVRowCombi& rr);
    // 输出到文件流的运算符
    bool operator==(const CSVRowCombi& r) const;
    // 重载 CSVRow 之间的比较运算符
    // 比较依据为 `account`, `identity`, `book`

    string account;
    string identity;
    string book;
    string lend_date;
    string return_date;
    CSVRowCombi* next{};
};

template <class TT>
class CSVReader {
  public:
    CSVReader() = default;
    explicit CSVReader(istream& s);
    // TT& begin() { return m_chain.get(0); };
    TT& get(int index) { return m_chain.get(index); };
    void append(TT& row) { m_chain.append(row); };
    void display() const { m_chain.display(); };
    int size() { return m_chain.length(); };
    void scanToFile(string& filepath);

  private:
    Chain<TT> m_chain;
};
