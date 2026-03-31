#include <iostream>
#include <cstring>
using namespace std;

const long long MOD = 1000000007;
const int MAXN = 505;

int n;
int orig_adj[MAXN][MAXN];
int adj[MAXN][MAXN];
long long dp[MAXN][MAXN];

long long solve(int l, int r) {
    if (l > r) return 1;
    if (l == r) return 1;

    if (dp[l][r] != -1) return dp[l][r];

    long long result = 0;

    for (int k = l + 1; k <= r; k++) {
        if (adj[l][k] == 0) continue;

        long long left = solve(l + 1, k - 1);
        long long right = solve(k + 1, r);

        result = (result + left * right % MOD) % MOD;
    }

    dp[l][r] = result;
    return result;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> orig_adj[i][j];
        }
    }

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    long long answer = 0;

    // Sum over all possible gaps
    for (int gap = 0; gap < n; gap++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int orig_i = (gap + 1 + i) % n;
                int orig_j = (gap + 1 + j) % n;
                adj[i][j] = orig_adj[orig_i][orig_j];
            }
        }

        memset(dp, -1, sizeof(dp));
        long long ways = solve(0, n - 1);
        answer = (answer + ways) % MOD;
    }

    cout << answer << endl;
    return 0;
}
