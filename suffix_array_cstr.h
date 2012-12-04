//============================================================================
// Name        : suffix_array_cstr.h
// Author      : enzam
// Created At  : Jul 8, 2012 7:00 PM
// Description : None
// Accepted	   :
//============================================================================


#ifndef SUFFIX_ARRAY_CSTR_H_
#define SUFFIX_ARRAY_CSTR_H_

#include "template.h"

template<size_t MAXLEN>
struct SuffixArrayCStr {
private:
	bool lexSort;

	char *str;
	int slen, step;
	int sa[MAXLEN], key[MAXLEN], pos[24][MAXLEN], bsize[MAXLEN];

	struct sacomp {
		int *key;
		sacomp(int *key) : key(key) {}
		bool operator()(int i, int j) {
			return key[i] < key[j];
		}
	};

	void buildSuffixArray() {
	    int i, j, k, H;

	    for (i = 0; i < slen; i++) {
	        sa[i] = i;
	        key[i] = str[i];
	    }
	    sort(sa, sa+slen, sacomp(key));

	    for (i = 0; i < slen; i = j) {
	        for (j = i + 1; j < slen && str[sa[j]] == str[sa[i]]; j++);
	        bsize[i] = j - i;
	    }

	    for (H = 1, step = 1; H < 2*slen; step++, H *= 2) {
	        for (i = 0; i < slen; i += bsize[i]) {
	            for (j = 0; j < bsize[i]; j++)
	                pos[step][sa[i + j]] = i;
	                //pos[sa[i + j]] = i;
	        }

	        for (i = 0; i < slen; i++) {
	            key[i] = (i + H < slen ? pos[step][i + H] : (lexSort?-1:MAXLEN));
	            //key[i] = (i + H < N ? pos[i + H] : -1);
	        }

	        for (i = 0; i < slen;) {
	            k = i + bsize[i];
	            sort(sa+i, sa+k, sacomp(key));
	            while (i < k) {
	                for (j = i + 1; j < k && key[sa[i]] == key[sa[j]]; j++);
	                bsize[i] = j - i;
	                i = j;
	            }
	        }
	    }
	}

public:
	SuffixArrayCStr(bool lexSort = true) : lexSort(lexSort) {}

	void setString(char *instr) {
		str = instr;
		slen = ssz(instr);
		buildSuffixArray();
	}

	int getPos(int i) { return pos[step-1][i]; }
	int getIdx(int i) { return sa[i]; }

	bool isSubstr(const char* pattern) {
	    int len = ssz(pattern);
	    if (len == 0) return true;

	    int left = 0, right = slen-1;
	    while (left <= right) {
	        int mid = (left + right) / 2;
	        int t = strncmp(str+sa[mid], pattern, len);
	        if (t == 0)
	            return true;
	        else if (t < 0)
	            left = mid + 1;
	        else
	            right = mid - 1;
	    }
	    return false;
	}

	int lcp(int x, int y) {
	    int k, ret = 0;
	    x = getIdx(x), y = getIdx(y);
	    if (x == y) return slen - x;
	    for (k = step - 1; k > 0 && x < slen && y < slen; k --) {
	        if (pos[k][x] == pos[k][y]) {
	            int add = 1<<(k-1);
	            x += add, y += add, ret += add;
	        }
	    }
	    return ret;
	}
};

#endif /* SUFFIX_ARRAY_CSTR_H_ */
