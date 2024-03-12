#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class CharALNode;
class RefNode;
class DelNode;

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
    CharALNode* _head;
    CharALNode* _tail;
    int _len;

public:
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
    class ReferencesList {
        // TODO: may provide some attributes
        public:
            int _node_count;
            RefNode* _head ;
            RefNode* _deleted_head;

        public:
            ReferencesList();
            void add_deleted(CharALNode* s);
            RefNode* find_node(CharALNode* s);
            void insert(CharALNode* s, int ref);
            void insert_node(RefNode* s);
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;
            void modify(CharALNode* s, int add);
            void clear();
    };

    class DeleteStringList {
        // TODO: may provide some attributes
        public:
            int _node_count;
            DelNode* _head;
            DelNode* _tail;

        public:
            DeleteStringList();
            void insert(RefNode* fi, RefNode* se);
            int size() const;
            std::string totalRefCountsString() const;
            void modify();
    };
};

#endif // __CONCAT_STRING_LIST_H__