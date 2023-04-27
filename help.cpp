#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Function to calculate the sum of probabilities from i to j
double sum(vector<double>& p, int i, int j)
{
    double s = 0;
    for (int k = i; k <= j; k++)
        s += p[k];
    return s;
}

// Function to calculate the optimal cost for a subtree with keys from i to j
double optimal_cost(vector<double>& p, int i, int j, vector<vector<double>>& dp, vector<vector<int>>& root)
{
    if (dp[i][j] != -1)
        return dp[i][j];
    if (i == j)
        return dp[i][j] = p[i];
    double cost = INF;
    for (int r = root[i][j-1]; r <= root[i+1][j]; r++) {
        double c = optimal_cost(p, i, r-1, dp, root) + optimal_cost(p, r+1, j, dp, root) + sum(p, i, j);
        if (c < cost) {
            cost = c;
            root[i][j] = r;
        }
    }
    return dp[i][j] = cost;
}

// Function to construct the optimal binary search tree
struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

Node* construct_optimal_bst(vector<double>& p, vector<vector<int>>& root, int i, int j)
{
    if (i > j)
        return NULL;
    int r = root[i][j];
    Node* root_node = new Node(r);
    root_node->left = construct_optimal_bst(p, root, i, r-1);
    root_node->right = construct_optimal_bst(p, root, r+1, j);
    return root_node;
}

// Function to print the keys of the binary search tree in inorder traversal
void print_inorder(Node* root)
{
    if (root == NULL)
        return;
    print_inorder(root->left);
    cout << root->key << " ";
    print_inorder(root->right);
}

int main()
{
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<double> p(n);
    cout << "Enter the probabilities of the keys: ";
    for (int i = 0; i < n; i++)
        cin >> p[i];

    vector<vector<double>> dp(n, vector<double>(n, -1));
    vector<vector<int>> root(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        dp[i][i] = p[i];
        root[i][i] = i;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n-len; i++) {
            int j = i+len-1;
            for (int r = root[i][j-1]; r <= root[i+1][j]; r++) {
                double c = optimal_cost(p, i, r-1, dp, root) + optimal_cost(p, r+1, j, dp, root) + sum(p, i, j);
                if (c < dp[i][j]) {
                    dp[i][j] = c;
                    root[i
