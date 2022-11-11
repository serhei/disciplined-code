#include <stack>

bool is_closing(char c)
{
  return c == ')' || c == '}' || c == ']';
}

char opener(char c)
{
  if (c == ')') return '(';
  if (c == '}') return '{';
  if (c == ']') return '[';
  return 0;
}

class Solution {
public:
    bool isValid(string ss) {
        char *s = ss.c_str();
        int valid_end = -1;
        int i = -1;
        bool fin = false;
        stack<int> parens;
        /* P1: "s.(lob..i) could be part of a valid prefix"
           P2: "s.(lob..valid-end) is the longest valid prefix of s.(lob..i)"
           P3: fin => "s.(lob..i+1) could not be part of a valid prefix"
           P4: "parens gives the indices of unclosed parens in s.(lob..i)" */
        while /* {P1,P2,P3,P4} */ (s[i+1] != '\0' && !fin)
            {
                char nc = s[i+1];
                char lc = parens.empty() ? '\0' : s[parens.top()];
                if (!is_closing(nc))
                    { parens.push(i+1); i++; }
                else if (parens.empty())
                    { fin = true; }
                else if (lc == opener(nc))
                    { parens.pop(); i++; }
                else
                    { fin = true; }
                if (parens.empty())
                    { valid_end = i; }
            }
        return !fin && s[i+1] == '\0' && valid_end == i;
    }
};
