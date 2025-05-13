#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to solve 0-1 Knapsack problem
int knapsack(int W, const vector<int>& wt, const vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> val(n), wt(n);
    cout << "Enter values of the items:\n";
    for (int i = 0; i < n; i++) cin >> val[i];

    cout << "Enter weights of the items:\n";
    for (int i = 0; i < n; i++) cin >> wt[i];

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    int maxProfit = knapsack(W, wt, val, n);
    cout << "Maximum value in knapsack = " << maxProfit << endl;

    return 0;
    
}
