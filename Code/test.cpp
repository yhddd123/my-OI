#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
bool mbe;

int n;
char s[maxn];

// 线性SA - DC3/Skew算法
struct LinearSA {
    int sa[maxn], rk[maxn];
    int wa[maxn], wb[maxn], wv[maxn], ws[maxn];
    int r[maxn * 3]; // 扩大数组大小避免越界
    int height[maxn];
    int tb; // 用于DC3算法的辅助变量
    
    // 比较函数
    bool cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    
    // 辅助函数
    int F(int x) { return x / 3 + (x % 3 == 1 ? 0 : tb); }
    int G(int x) { return x < tb ? x * 3 + 1 : (x - tb) * 3 + 2; }
    int c0(int *r, int a, int b) { return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2]; }
    int c12(int k, int *r, int a, int b) {
        if (k == 2) return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
        else return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
    }
    
    // 基数排序
    void sort(int *r, int *a, int *b, int n, int m) {
        int i;
        for (i = 0; i < n; i++) wv[i] = r[a[i]];
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[wv[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--) b[--ws[wv[i]]] = a[i];
    }
    
    // DC3算法核心 - 修复版本
    void dc3(int *r, int *sa, int n, int m) {
        int i, j, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
        int *rn = r + n, *san = sa + n;
        
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; i++) if (i % 3 != 0) wa[tbc++] = i;
        sort(r + 2, wa, wb, tbc, m);
        sort(r + 1, wb, wa, tbc, m);
        sort(r, wa, wb, tbc, m);
        
        for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
            rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
        
        if (p < tbc) dc3(rn, san, tbc, p);
        else for (i = 0; i < tbc; i++) san[rn[i]] = i;
        
        for (i = 0; i < tbc; i++) if (san[i] < tb) wb[ta++] = san[i] * 3;
        if (n % 3 == 1) wb[ta++] = n - 1;
        sort(r, wb, wa, ta, m);
        
        for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
        for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
            sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
        for (; i < ta; p++) sa[p] = wa[i++];
        for (; j < tbc; p++) sa[p] = wb[j++];
    }
    
    // 计算height数组
    void calheight(int *r, int *sa, int n) {
        int i, j, k = 0;
        for (i = 1; i <= n; i++) rk[sa[i]] = i;
        for (i = 0; i < n; height[rk[i++]] = k)
            for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; k++);
    }
    
    void init(char *str) {
        // 将字符串转换为整数数组
        for (int i = 0; i < n; i++) r[i] = str[i + 1] - 'a' + 1;
        r[n] = r[n + 1] = 0;
        tb = (n + 1) / 3;
        dc3(r, sa, n + 1, 27);
        calheight(r, sa, n);
    }
} t1, t2;

void work(){
    scanf("%s",s+1);n=strlen(s+1);
    t1.init(s);
    reverse(s+1,s+n+1);
    t2.init(s);
    reverse(s+1,s+n+1);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}