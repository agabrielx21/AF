class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.length();
        int l2 = text2.length();
        int m[l1+1][l2+1];
        for (int i = 0; i <= l1; i++) {
            for (int j = 0; j <= l2; j++) {
                if (i == 0 || j == 0) {
                    m[i][j] = 0;
                } else if (text1[i-1] == text2[j-1]) {
                    m[i][j] = m[i-1][j-1] + 1;
                } else {
                    m[i][j] = max(m[i-1][j], m[i][j-1]);
                }
            }
        }
        return m[l1][l2];
    }
};