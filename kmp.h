//============================================================================
// Name        : kmp.h
// Author      : enzam
// Created At  : Jun 7, 2012 11:09:58 AM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef KMP_H_
#define KMP_H_

#include "template.h"

class KMP {
	string pattern;
	vi failFunc;

	void genFailFunction() {
		int len = pattern.size();
		failFunc.resize(len + 1);

		failFunc[0] = failFunc[1] = 0;

		FORab(i, 2, len) {
			int j = failFunc[i - 1];
			while(j && pattern[j] != pattern[i - 1]) j = failFunc[j];
			if(pattern[j] == pattern[i - 1]) j++;
			failFunc[i] = j;
		}
	}

public:
	void setPattern(const string &str) {
		pattern = str;
		genFailFunction();
	}

	KMP() {}
	KMP(const string &str) {
		setPattern(str);
	}

	const vi& getFailFuncArray() const { return failFunc; }

	/**
	 * Returns the max match in a position in the array maxMatch
	 */
	void getMaxMatch(const string &str, vi& maxMatch) const {
	    int slen = str.size();
	    //int plen = pattern.size();
	    maxMatch.resize(slen);
	    int pidx = 0;
	    FOR(sidx, slen) {
	        while(pidx && str[sidx] != pattern[pidx]) pidx = failFunc[pidx];
	        if(str[sidx] == pattern[pidx]) {
	            pidx++;
	            maxMatch[sidx] = pidx;
	            //if(pidx == plen) pidx = 0;
	        }
	    }
	}
	vi getMaxMatch(const string &str) const {
		vi maxMatch; getMaxMatch(str, maxMatch);
		return maxMatch;
	}
};

#endif /* KMP_H_ */
