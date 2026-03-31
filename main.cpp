#include <iostream>
#include <cstring>
using namespace std;

const long long MOD = 1000000007;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long dp[MAXN][MAXN];

long long solve(int i, int j) {
    if (i == j) return 1;

    int len = (j - i + n) % n;
    if (len == 0) len = n;
    if (len == 1) return adj[i][j];

    if (dp[i][j] != -1) return dp[i][j];

    long long result = 0;

    for (int k = (i + 1) % n; ; k = (k + 1) % n) {
        if (k == (j + 1) % n) break;

        if (adj[i][k] == 0) continue;

        long long left = 1, right = 1;

        int next_i = (i + 1) % n;
        int prev_k = (k - 1 + n) % n;
        if (next_i != k) {
            left = solve(next_i, prev_k);
        }

        if (k != j) {
            right = solve(k, j);
        }

        result = (result + left * right % MOD) % MOD;

        if (k == j) break;
    }

    dp[i][j] = result;
    return result;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    memset(dp, -1, sizeof(dp));

    long long answer = solve(0, n - 1);

    cout << answer << endl;
    return 0;
}
