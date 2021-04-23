#include "../pch/pch.hpp"

#include "linearlist.hpp"

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

template <class TT>
TT& Chain<TT>::getByStudentCode(int code) {
    Node<TT>* p = m_first_node;
    for (int i = 0; i < m_size; i++) {
        if ((p->data).code == code) {
            return p->data;
        };
        p = p->next;
    };
    throw runtime_error("no matched student code\n");
};

template <class TT>
TT& Chain<TT>::getByStudentName(const std::string& name) {
    Node<TT>* p = m_first_node;
    for (int i = 0; i < m_size; i++) {
        if ((p->data).name == name) {
            return p->data;
        };
        p = p->next;
    };
    throw runtime_error("no matched student name\n");
};

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
