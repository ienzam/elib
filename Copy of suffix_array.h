//============================================================================
// Name        : suffix_array.h
// Author      : enzam
// Created At  : Jul 6, 2012 2:29:34 PM
// Description : None
// Accepted	   : YES, uva - GATTACA, livearchive - Hidden Password
//============================================================================


#ifndef SUFFIX_ARRAY_H_
#define SUFFIX_ARRAY_H_

#include "template.h"

template<size_t MAXLEN>
struct SuffixArray {
private:
	struct Entry {
	    int nr[2], idx;
	    friend bool operator<(const Entry &a, const Entry& b) {
	        return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
	    }
	}sa[MAXLEN];
	int pos[24][MAXLEN];
	char *str;
	int slen;
	int step;
	bool lexSort;

	//builds the suffix array, str is the string
	//pos[i] stores the position of suffix starts at i.
	//sa[i] stores the index of i-th suffix array
	void buildSuffixArray() {
	    int N = slen, i, cnt;
	    step = 0;
	    for (i = 0; i < N; i ++)
	        pos[step][i] = str[i];

        for (cnt = 1, step = 1; cnt >> 1 < N; cnt <<= 1, step++) {
	        for (i = 0; i < N; i ++) {
	            sa[i].nr[0] = pos[step-1][i];
	            sa[i].nr[1] = i + cnt < N ? pos[step-1][i + cnt] : (lexSort ? -1 : N);
	            sa[i].idx = i;
	        }
	        sort(sa, sa + N);
	        for (i = 0; i < N; i ++)
	        	pos[step][i] = pos[step - 1][i];
	        for (i = 0; i < N; i ++)
	            pos[step][sa[i].idx] =
	            		i > 0 &&
	            		sa[i].nr[0] == sa[i - 1].nr[0] &&
	            		sa[i].nr[1] == sa[i - 1].nr[1] ?
	            				pos[step][sa[i - 1].idx] : i;
	    }
        step--;

	}

public:
	SuffixArray(bool lexSort = true) : lexSort(lexSort) {}

	void setString(char instr[]) {
		str = instr;
		slen = strlen(instr);
		buildSuffixArray();
	}

	int getPos(int i) { return pos[step][i]; }
	int getIdx(int i) { return sa[i].idx; }

	int lcp(int x, int y) // longest common prefix of xth and yth lexicographically sorted suffixes
	{
	    int k, ret = 0;
	    x = sa[x].idx, y = sa[y].idx;
	    if (x == y) return slen - x;
	    for (k = step - 1; k >= 0 && x < slen && y < slen; k--) {
	        if (pos[k][x] == pos[k][y]) {
	            int add = 1<<k;
	            x += add, y += add, ret += add;
	        }
	    }
	    return ret;
	}

	bool isSubstr(const char* pattern) {
	    int len = strlen(pattern);
	    if (len == 0) return true;

	    int left = 0, right = slen-1;
	    while (left <= right) {
	        int mid = (left + right) / 2;
	        int t = strncmp(str+sa[mid].idx, pattern, len);
	        if (t == 0)
	            return true;
	        else if (t < 0)
	            left = mid + 1;
	        else
	            right = mid - 1;
	    }
	    return false;
	}

};

#endif /* SUFFIX_ARRAY_H_ */
