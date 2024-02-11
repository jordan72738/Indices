#include <iostream>
#include <vector>
#include <string>

using namespace std;

string longestCommonSubstring(const string& A, const string& B) {
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int length = 0, endIndex = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i-1] == B[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > length) {
                    length = dp[i][j];
                    endIndex = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Display the 2D grid (lookup table)
    cout << "Lookup Table:" << endl;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return A.substr(endIndex - length, length);
}

int main() {
    string str1, str2;

    // Prompt for input strings
    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    string lcs = longestCommonSubstring(str1, str2);

    cout << "Longest Common Substring: " << lcs << endl;

    return 0;
}