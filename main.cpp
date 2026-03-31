#include <iostream>
#include <cstring>
using namespace std;

const long long MOD = 1000000007;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long dp[MAXN][MAXN];

// dp[l][r] counts non-crossing trees on LINEAR segment [l,r]
long long solveLinear(int l, int r) {
    if (l > r) return 1;
    if (l == r) return 1;

    if (dp[l][r] != -1) return dp[l][r];

    long long result = 0;

    // Choose edge (l, k)
    for (int k = l + 1; k <= r; k++) {
        if (adj[l][k] == 0) continue;

        long long left = solveLinear(l + 1, k - 1);
        long long right = solveLinear(k + 1, r);

        result = (result + left * right % MOD) % MOD;
    }

    dp[l][r] = result;
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

    if (n == 2) {
        cout << adj[0][1] << endl;
        return 0;
    }

    long long answer = 0;

    // For circular arrangement: try each edge (i, j) as the "first" edge
    // This edge splits the circle into two arcs
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j] == 0) continue;

            // Use edge (i, j)
            // Arc 1: nodes between i and j (clockwise, not including i, j)
            // Arc 2: nodes between j and i (clockwise, not including j, i)

            int arc1_size = (j - i - 1 + n) % n;
            int arc2_size = (i - j - 1 + n) % n;

            if (arc1_size + arc2_size != n - 2) continue; // Sanity check

            memset(dp, -1, sizeof(dp));

            long long cnt1 = 1, cnt2 = 1;

            if (arc1_size > 0) {
                // Map nodes (i+1) mod n, (i+2) mod n, ..., (j-1) mod n to 0, 1, ..., arc1_size-1
                int temp_adj1[MAXN][MAXN];
                for (int x = 0; x < arc1_size; x++) {
                    for (int y = 0; y < arc1_size; y++) {
                        int orig_x = (i + 1 + x) % n;
                        int orig_y = (i + 1 + y) % n;
                        temp_adj1[x][y] = adj[orig_x][orig_y];
                    }
                }

                int old_adj[MAXN][MAXN];
                memcpy(old_adj, adj, sizeof(adj));
                memcpy(adj, temp_adj1, sizeof(temp_adj1));

                cnt1 = solveLinear(0, arc1_size - 1);

                memcpy(adj, old_adj, sizeof(adj));
            }

            memset(dp, -1, sizeof(dp));

            if (arc2_size > 0) {
                int temp_adj2[MAXN][MAXN];
                for (int x = 0; x < arc2_size; x++) {
                    for (int y = 0; y < arc2_size; y++) {
                        int orig_x = (j + 1 + x) % n;
                        int orig_y = (j + 1 + y) % n;
                        temp_adj2[x][y] = adj[orig_x][orig_y];
                    }
                }

                int old_adj[MAXN][MAXN];
                memcpy(old_adj, adj, sizeof(adj));
                memcpy(adj, temp_adj2, sizeof(temp_adj2));

                cnt2 = solveLinear(0, arc2_size - 1);

                memcpy(adj, old_adj, sizeof(adj));
            }

            answer = (answer + cnt1 * cnt2 % MOD) % MOD;
        }
    }

    cout << answer << endl;
    return 0;
}
