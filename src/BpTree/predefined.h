#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <cstring>
#include <string>

namespace bpt {

/* predefined B+ info */
#define BP_ORDER 20

/* key/value type */
struct key_t {
    int k;

    key_t(const int &key = 0)
    {
        k = key;
    }
};

inline int keycmp(const key_t &a, const key_t &b)
{
	if(a.k < b.k)
		return -1;
	if(a.k == b.k)
		return 0;
	if(a.k > b.k)
		return 1;
}

#define OPERATOR_KEYCMP(type) \
    bool operator< (const key_t &l, const type &r) {\
        return keycmp(l, r.key) < 0;\
    }\
    bool operator< (const type &l, const key_t &r) {\
        return keycmp(l.key, r) < 0;\
    }\
    bool operator== (const key_t &l, const type &r) {\
        return keycmp(l, r.key) == 0;\
    }\
    bool operator== (const type &l, const key_t &r) {\
        return keycmp(l.key, r) == 0;\
    }

}

const int VALUE_SIZE = 1024;

struct value_t
{
	char str[VALUE_SIZE];
	
	value_t(const char* s = "")
	{
		memset(str, 0, sizeof(str));
		strcpy(str, s);
	}
};

inline int valuecmp(const value_t &a, const value_t &b)
{
	int x = strlen(a.str) - strlen(b.str);
	return x == 0 ? strcmp(a.str, b.str) : x;
}

#define OPERATOR_VALUECMP(type) \
    bool operator< (const value_t &l, const type &r) {\
        return valuecmp(l, r) < 0;\
    }\
    bool operator== (const value_t &l, const type &r) {\
        return valuecmp(l, r) == 0;\
    }\

#endif
