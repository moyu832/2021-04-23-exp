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
