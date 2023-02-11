class Solution {
public:
	int firstUniqChar(string s) {
        int fix = -1;
#define NIL -1
#define DUP -2
        int uniq[26]; for (char c = 'a'; c <= 'z'; c++) uniq[c-'a'] = NIL;
        int next_uniq[26]; for (char c = 'a'; c <= 'z'; c++) next_uniq[c-'a'] = NIL;
        char lch = NIL;
        for (int k = 0; k < s.size(); k++) {
            int ski = s[k]-'a';
            if (uniq[ski] == NIL) {
                if (lch != NIL) next_uniq[lch-'a'] = k;
                lch = s[k];
            }
            if (uniq[ski] == NIL && fix == NIL) {
                uniq[ski] = k; fix = k;
            } else if (uniq[ski] == NIL && fix != NIL) { /* TYPO here fix == NIL */
                uniq[ski] = k;
            } else if (uniq[ski] != NIL && fix == uniq[ski]) {
                uniq[ski] = DUP;
                while (fix != NIL && uniq[s[fix]-'a'] == DUP) {
                    fix = next_uniq[s[fix]-'a'];
                    //cerr << "* fix now " << fix << " next_uniq " << next_uniq[s[fix]-'a'] << endl;
                }
                if (fix == NIL) lch = NIL;
            } else { // uniq[ski] != NIL && fix != uniq[ski]
                uniq[ski] = DUP;
            }
            //cerr << "s[k] " << s[k] << " fix " << fix << " next_uniq " << next_uniq[s[fix]-'a'] << endl;
        }
        return fix;
    }
};
