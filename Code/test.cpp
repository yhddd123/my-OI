#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int mod = 998244353;

inline int ksm(int a, int b = mod - 2) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return ans;
}

inline void inc(int &u, int v) {
    u += v;
    if (u >= mod) u -= mod;
}

inline void dec(int &u, int v) {
    u -= v;
    if (u < 0) u += mod;
}

namespace poly {
    const int gen = 3;
    const int invg = ksm(3);
    
    void init_to(vector<int> &to, int n) {
        to[0] = 0;
        for (int i = 1; i < n; i++) {
            to[i] = (to[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
        }
    }
    
    void ntt(vector<int> &a, int fl) {
        int n = a.size();
        vector<int> to(n);
        init_to(to, n);
        
        for (int i = 0; i < n; i++) {
            if (i < to[i]) {
                swap(a[i], a[to[i]]);
            }
        }
        
        for (int l = 2; l <= n; l <<= 1) {
            int wlen = ksm(fl == 1 ? gen : invg, (mod - 1) / l);
            int k = l >> 1;
            for (int i = 0; i < n; i += l) {
                int w = 1;
                for (int j = 0; j < k; j++) {
                    int u = a[i + j];
                    int v = 1ll * a[i + j + k] * w % mod;
                    inc(a[i + j] = u, v);
                    dec(a[i + j + k] = u, v);
                    w = 1ll * w * wlen % mod;
                }
            }
        }
        
        if (fl == -1) {
            int inv = ksm(n);
            for (int i = 0; i < n; i++) {
                a[i] = 1ll * a[i] * inv % mod;
            }
        }
    }
    
    vector<int> mul(const vector<int> &a, const vector<int> &b) {
        int n = a.size() - 1, m = b.size() - 1;
        int k = 1;
        while (k < n + m + 1) k <<= 1;
        
        vector<int> A(a);
        vector<int> B(b);
        A.resize(k);
        B.resize(k);
        
        ntt(A, 1);
        ntt(B, 1);
        
        for (int i = 0; i < k; i++) {
            A[i] = 1ll * A[i] * B[i] % mod;
        }
        
        ntt(A, -1);
        A.resize(n + m + 1);
        return A;
    }
}

// 测试代码
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 测试：2^23大小的NTT
    const int n = 1 << 23;
    vector<int> a(n, 1);
    vector<int> b(n, 1);
    
    // 执行NTT
    poly::ntt(a, 1);
    poly::ntt(b, 1);
    
    // 点乘
    for (int i = 0; i < n; i++) {
        a[i] = 1ll * a[i] * b[i] % mod;
    }
    
    // 逆NTT
    poly::ntt(a, -1);
    
    cout << "NTT completed successfully!" << endl;
    cout << "Result size: " << a.size() << endl;
    cout << "First 10 values: ";
    for (int i = 0; i < 10 && i < (int)a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    
    return 0;
}