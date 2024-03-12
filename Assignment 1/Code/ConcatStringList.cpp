#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

class CharALNode
{
    private:
        char* CharArrayList;
        CharALNode* _next;
        int _len;
        bool _deleted;

    public:
        CharALNode(const char* s)
        {
            _len = 0;
            while(true)
            {
                if(s[_len] != '\0') _len++;
                else break;
            }
            CharArrayList = new char[this->_len + 1];
            for(int i = 0; i < _len; i++)
            {
                CharArrayList[i] = s[i];
            }
            CharArrayList[this->_len] = '\0';
            _next = NULL;
            _deleted = false;
        }

        bool _get_deleted() const
        {
            return _deleted;
        }

        void _set_deleted()
        {
            _deleted = true;
        }

        int _get_len() const
        {
            return _len;
        }

        char _get_char(int index) const
        {
            return CharArrayList[index];
        }

        int _get_index(char c) const
        {
            for(int i = 0; i < _len; i++)
            {
                if(CharArrayList[i] == c) return i;
            }
            return -1;
        }

        CharALNode* _get_next() const
        {
            return _next;
        }

        char* _get_array_list() const
        {
            return CharArrayList;
        }

        void _connect(CharALNode* other)
        {
            _next = other;
        }

        ~CharALNode()
        {
            delete[] CharArrayList;
            _next = NULL;
            _len = 0;
            _deleted = true;
        }
};

class RefNode
{
    public:
        CharALNode* _first;
        RefNode* _next;
        int _first_refs;

    public:
        RefNode(CharALNode* s, int ref)
        {
            _first = s;
            _next = NULL;
            _first_refs = ref;
        }
        ~RefNode()
        {
            _first = NULL;
            _next = NULL;
            _first_refs = 0;
        }
};

class DelNode
{
    public:
        RefNode* _first;
        RefNode* _second;
        DelNode* _next;
    public: 
        DelNode(RefNode* fi, RefNode* se)
        {
            _first = fi;
            _second = se;
            _next = NULL;
        }
        ~DelNode()
        {
            _first = NULL;
            _second = NULL;
            _next = NULL;
        }
};

ConcatStringList::ConcatStringList(const char* s)
{
    _head = new CharALNode(s);
    _tail = _head;
    _len = _head->_get_len();
    refList.insert(_head, 2);
}

int ConcatStringList::length() const
{
    return _len;
}

char ConcatStringList::get(int index) const
{
    if(index < 0 || index >= _len)
    {
        throw out_of_range("Index of string is invalid!");
    }
    CharALNode* p = _head;
    while(true)
    {
        if(p->_get_len() <= index)
        {
            index -= p->_get_len();
            p = p->_get_next();
        }
        else return p->_get_char(index);
    }
    return '\0';
}

int ConcatStringList::indexOf(char c) const
{
    int res = 0;
    int id;
    CharALNode* p = _head;
    while(true)
    {
        id = p->_get_index(c);
        if(id < 0)
        {
            res += p->_get_len();
            if(p == _tail) break;
            p = p->_get_next();
        }
        else return res + id;
    }
    return -1;
}

std::string ConcatStringList::toString() const
{
    string s = "";
    CharALNode* p = _head;
    int length = 0;
    while(true)
    {
        length += p->_get_len();
        for(int i = 0; i < p->_get_len(); i++)
        {
            s += p->_get_char(i);
        }
        if(length == _len) break;
        p = p->_get_next();
    }
    return s;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList & otherS) const
{
    ConcatStringList s = *this;
    (s._tail)->_connect(otherS._head);
    s._tail = otherS._tail;
    s._len = this->_len + otherS._len;
    refList.modify(s._head, 1);
    refList.modify(s._tail, 1);
    return s;
}

ConcatStringList ConcatStringList::subString(int from, int to) const
{
    if(from < 0 || to > _len || from >= _len || to <= 0)
    {
        throw out_of_range("Index of string is invalid!");
    }
    if(from >= to)
    {
        throw logic_error("Invalid range");
    }

    to--;
    int id = 0;
    CharALNode* p = _head;
    while(id + p->_get_len() <= from)
    {
        id += p->_get_len();
        p = p->_get_next();
    }

    char* cas = new char[min(id + p->_get_len() - from, to - from + 1) + 1];
    for(int i = from - id; i < min(to - id + 1, p->_get_len()); i++)
    {
        cas[i - from + id] = p->_get_char(i);
    }
    cas[min(id + p->_get_len() - from, to - from + 1)] = '\0';
    ConcatStringList ans(cas);
    delete[] cas;

    if(id + p->_get_len() > to)
    {
        return ans;
    }

    id += p->_get_len();
    p = p->_get_next();
    CharALNode* node;

    while(id + p->_get_len() <= to)
    {
        node = new CharALNode(p->_get_array_list());
        (ans._tail)->_connect(node);
        ans._tail = node;
        ans._len += node->_get_len();
        id += node->_get_len();
        p = p->_get_next();
    }

    cas = new char[to - id + 2];
    for(int i = 0; i <= to - id + 1; i++)
    {
        cas[i] = p->_get_char(i);
    }
    cas[to - id + 1] = '\0';

    CharALNode* string_tail = new CharALNode(cas);
    delete[] cas;
    (ans._tail)->_connect(string_tail);
    ans._tail = string_tail;
    ans._len += string_tail->_get_len();
    //
    refList.modify(ans._head, -1);
    refList.insert(ans._tail, 1);
    return ans;
}

ConcatStringList ConcatStringList::reverse() const
{
    CharALNode* p = _head;
    CharALNode* node;
    char* cas;
    cas = new char[p->_get_len() + 1];
    for(int i = p->_get_len() - 1; i >= 0; i--)
    {
        cas[p->_get_len() - 1 - i] = p->_get_char(i);
    }
    cas[p->_get_len()] = '\0';
    ConcatStringList ans(cas);
    delete[] cas;

    if(p == _tail)
    {
        return ans;
    }

    p = p->_get_next();
    while(true)
    {
        cas = new char[p->_get_len() + 1];
        for(int i = p->_get_len() - 1; i >= 0; i--)
        {
            cas[p->_get_len() - 1 - i] = p->_get_char(i);
        }
        cas[p->_get_len()] = '\0';
        node = new CharALNode(cas);
        delete[] cas;

        node->_connect(ans._head);
        ans._head = node;
        ans._len += node->_get_len();
        if(p == _tail) break;
        p = p->_get_next();
    }
    refList.modify(ans._tail, -1);
    refList.insert(ans._head, 1);
    return ans;
}

ConcatStringList::~ConcatStringList()
{
    refList.modify(_head, -1);
    refList.modify(_tail, -1);
    delStrList.insert(refList.find_node(_head), refList.find_node(_tail));
    delStrList.modify();
    _head = NULL;
    _tail = NULL;
    _len = 0;
}

ConcatStringList::ReferencesList::ReferencesList()
{
    _node_count = 0;
    _head = NULL;
    _deleted_head = NULL;
}

void ConcatStringList::ReferencesList::add_deleted(CharALNode* s)
{
    RefNode* tmp = _deleted_head;
    _deleted_head = new RefNode(s, 0);
    _deleted_head->_next = tmp;
}

RefNode* ConcatStringList::ReferencesList::find_node(CharALNode* s)
{
    RefNode* p = _head;
    while(p != NULL)
    {
        if(p->_first == s) return p;
        p = p->_next;
    }
    return p;
}

void ConcatStringList::ReferencesList::insert(CharALNode* s, int ref)
{
    if(_head == NULL)
    {
        _head = new RefNode(s, ref);
        _node_count = 1;
    }
    else
    {
        RefNode* p = _head;
        RefNode* pre = _head;
        while(p != NULL && p->_first_refs < ref && p->_first_refs != 0)
        {
            pre = p;
            p = p->_next;
        }
        if(p == pre)
        {
            _head = new RefNode(s, ref);
            _head->_next = p;
        }
        else
        {
            RefNode* tmp = new RefNode(s, ref);
            pre->_next = tmp;
            tmp->_next = p;
        }
        _node_count += 1;
    }
}

void ConcatStringList::ReferencesList::insert_node(RefNode* s)
{
    if(_head == NULL)
    {
        _head = s;
        _node_count = 1;
    }
    else if(s->_first_refs == 0)
    {
        RefNode* p = _head;
        while(p->_next != NULL) p = p->_next;
        p->_next = s;
        s->_next = NULL;
        _node_count += 1;
    }
    else
    {
        RefNode* p = _head;
        RefNode* pre = _head;
        while(p != NULL && p->_first_refs < s->_first_refs && p->_first_refs != 0)
        {
            pre = p;
            p = p->_next;
        }
        if(p == pre)
        {
            _head = s;
            _head->_next = p;
        }
        else
        {
            pre->_next = s;
            s->_next = p;
        }
        _node_count += 1;
    }
}

int ConcatStringList::ReferencesList::size() const
{
    return _node_count;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if(index >= _node_count || index < 0)
    {
        throw out_of_range("Index of references list is invalid!");
    }
    RefNode* p = _head;
    for(int i = 0; i < index; i++)
    {
        p = p->_next;
    }
    return p->_first_refs;
}

std::string ConcatStringList::ReferencesList::refCountsString() const
{
    if(_node_count == 0)
    {
        return "RefCounts[]";
    }
    string s = "RefCounts[";
    RefNode* p = _head;
    for(int i = 0; i < _node_count; i++)
    {
        string num = "";
        int val = p->_first_refs;
        if(val == 0) num = "0";
        while(val)
        {
            num  = (char)(val % 10 + 48) + num;
            val /= 10;
        }
        s += num;
        if(i == _node_count - 1) break;
        s += ",";
        p = p->_next;
    }
    s += "]";
    return s;
}

void ConcatStringList::ReferencesList::modify(CharALNode* s, int add)
{
    RefNode* tmp;
    if(_node_count == 1)
    {
        tmp = _head;
        tmp->_first_refs += add;
        _head = NULL;
        _node_count--;
    }
    else
    {
        RefNode* pre = _head;
        RefNode* p = _head;
        while(p->_first != s)
        {
            pre = p;
            p = p->_next;
        }
        if(p == _head)
        {
            tmp = _head;
            tmp->_first_refs += add;
            _head = _head->_next;
            _node_count--;
        }
        else
        {
            tmp = p;
            tmp->_first_refs += add;
            pre->_next = p->_next;
            _node_count--;
        }
    }
    insert_node(tmp);
}

void ConcatStringList::ReferencesList::clear()
{
    RefNode* tmp;
    while(_head != NULL)
    {
        tmp = _head;
        _head = _head->_next;
        delete tmp;
    }

    while(_deleted_head != NULL)
    {
        tmp = _deleted_head;
        _deleted_head = _deleted_head->_next;
        delete tmp->_first;
        delete tmp;
    }
    _node_count = 0;
    _head = NULL;
    _deleted_head = NULL;
}

ConcatStringList::DeleteStringList::DeleteStringList()
{
    _head = NULL;
    _tail = NULL;
    _node_count = 0;
}

void ConcatStringList::DeleteStringList::insert(RefNode* fi, RefNode* se)
{
    if(_head == NULL)
    {
        _head = new DelNode(fi, se);
        _tail = _head;
        _node_count = 1;
    }
    else
    {
        DelNode* tmp = _tail;
        _tail = new DelNode(fi, se);
        tmp->_next = _tail;
        _node_count += 1;
    }
}

int ConcatStringList::DeleteStringList::size() const
{
    return _node_count;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    if(_node_count == 0)
    {
        return "TotalRefCounts[]";
    }
    string s = "TotalRefCounts[";
    DelNode* p = _head;
    for(int i = 0; i < _node_count; i++)
    {
        string num = "";
        int val = (p->_first)->_first_refs;
        if(p->_first != p->_second) val += (p->_second)->_first_refs;
        if(val == 0) num = "0";
        while(val)
        {
            num  = (char)(val % 10 + 48) + num;
            val /= 10;
        }
        s += num;
        if(i == _node_count - 1) break;
        s += ",";
        p = p->_next;
    }
    s += "]";
    return s;
}

void ConcatStringList::DeleteStringList::modify()
{
    DelNode* pre = _head;
    DelNode* p = _head;
    while(p != NULL)
    {
        if(((p->_first)->_first_refs == 0) && ((p->_second)->_first_refs == 0))
        {
            _node_count--;
            if(pre == p)
            {
                CharALNode* _start = (p->_first)->_first;
                CharALNode* _finish = (p->_second)->_first;
                p = _head->_next;
                pre = p;
                delete _head;
                _head = p;
                if(_head == NULL) _tail = NULL;
                if(_start->_get_deleted()) continue;
                CharALNode* tmp;
                while(true)
                {
                    if(_start == _finish)
                    {
                        if(_start->_get_deleted() == false)
                        {
                            _start->_set_deleted();
                            refList.add_deleted(_start);
                        }
                        break;
                    }
                    tmp = _start->_get_next();
                    if(_start->_get_deleted() == false)
                    {
                        _start->_set_deleted();
                        refList.add_deleted(_start);
                    }
                    else break;
                    _start = tmp;
                }
            }
            else
            {
                CharALNode* _start = (p->_first)->_first;
                CharALNode* _finish = (p->_second)->_first;
                pre->_next = p->_next;
                delete p;
                p = pre->_next;
                if(p == NULL) _tail = pre;
                if(_start == NULL) continue;
                CharALNode* tmp;
                while(true)
                {
                    if(_start == _finish)
                    {
                        if(_start->_get_deleted() == false)
                        {
                            _start->_set_deleted();
                            refList.add_deleted(_start);
                        }
                        break;
                    }
                    tmp = _start->_get_next();
                    if(_start->_get_deleted() == false)
                    {
                        _start->_set_deleted();
                        refList.add_deleted(_start);
                    }
                    else break;
                    _start = tmp;
                }
            }
        }
        else
        {
            pre = p;
            p = p->_next;
        }
    }

    if(_node_count == 0)
    {
        _head = NULL;
        _tail = NULL;
        if((refList._head)->_first_refs == 0) refList.clear();
    }
}