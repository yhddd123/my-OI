// Problem: P9563 [SDCPC 2023] Be Careful 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9563
// Memory Limit: 1024 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2026-01-26 15:44:18
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=1e9;
bool mbe;


inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int n,m,k,ans;
pair<pii,pii> a[maxn];

//by gemini
const int INV2 = ksm(2);
const int INV6 = ksm(6);
const int INV30 = ksm(30);
inline int sum0(int n) {return n;}
inline int sum1(int n) {return n * (n + 1) % mod * INV2 % mod;}
inline int sum2(int n) {return n * (n + 1) % mod * (2 * n + 1) % mod * INV6 % mod;}
inline int sum3(int n) {
    int s1 = n * (n + 1) % mod * INV2 % mod;
    return s1 * s1 % mod;
}
inline int sum4(int n) {
    int n2 = n * n % mod;
    return n * (n + 1) % mod * (2 * n + 1) % mod * (3 * n2 % mod + 3 * n - 1 + mod) % mod * INV30 % mod;
}
inline int sum_range(int L, int R, int p) {
    if (L > R) return 0;
    if(p==2)return (sum2(R) - sum2(L - 1) + mod) % mod;
    if(p==3)return (sum3(R) - sum3(L - 1) + mod) % mod;
    if(p==4)return (sum4(R) - sum4(L - 1) + mod) % mod;
}
// 获取 Nx(i) = Ai * i + Bi 的系数
void get_coeffs(int i_sample, int n, int a, int b, int &A, int &B) {
    // Nx(i) = min(a-1, n-i) - max(0, b-i+1) + 1
    int val_min = (a - 1 < n - i_sample) ? (a - 1) : (n - i_sample);
    int val_max = (0 > b - i_sample + 1) ? 0 : (b - i_sample + 1);
    
    // 判定当前的解析式形态
    bool min_is_fixed = (a - 1 <= n - i_sample);
    bool max_is_fixed = (0 >= b - i_sample + 1);

    if (min_is_fixed && max_is_fixed) { // (a-1) - 0 + 1
        A = 0; B = a;
    } else if (min_is_fixed && !max_is_fixed) { // (a-1) - (b-i+1) + 1
        A = 1; B = a - b - 1;
    } else if (!min_is_fixed && max_is_fixed) { // (n-i) - 0 + 1
        A = -1; B = n + 1;
    } else { // (n-i) - (b-i+1) + 1
        A = 0; B = n - b;
    }
    A = (A % mod + mod) % mod;
    B = (B % mod + mod) % mod;
}

int calc(int a, int b, int c, int d) {
    int pl = max(b - a + 2, d - c + 2);
    int pr = min(n, m);
    if (pl > pr) return 0;

    // 关键转折点收集
    vector<int> pts = {pl, pr + 1};
    int critical[] = {n - a + 1, n - a + 2, b + 1, b + 2, m - c + 1, m - c + 2, d + 1, d + 2};
    for (int p : critical) {
        if (p >= pl && p <= pr + 1) pts.push_back(p);
    }
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    int ans = 0;
    for (size_t i = 0; i < pts.size() - 1; ++i) {
        int L = pts[i], R = pts[i+1] - 1;
        if (L > R) continue;

        int Ax, Bx, Ay, By;
        get_coeffs(L, n, a, b, Ax, Bx);
        get_coeffs(L, m, c, d, Ay, By);

        // 多项式系数: k^2 * (Ax*k + Bx) * (Ay*k + By)
        int c4 = Ax * Ay % mod;
        int c3 = (Ax * By % mod + Bx * Ay % mod) % mod;
        int c2 = Bx * By % mod;

        int res = (c4 * sum_range(L, R, 4) % mod + 
                  c3 * sum_range(L, R, 3) % mod + 
                  c2 * sum_range(L, R, 2) % mod) % mod;
        ans = (ans + res) % mod;
    }
    return (int)ans;
}

// int calc(int a,int b,int c,int d){
	// int pl=max(b-a+2,d-c+2),pr=min(n,m),ans=0;
	// // cout<<pl<<" "<<pr<<"\n";
	// for(int i=pl;i<=pr;i++){
		// (ans+=i*i*(min(a-1,n-i)-max(b-i+1,0ll)+1)*(min(c-1,m-i)-max(d-i+1,0ll)+1))%mod;
	// }
	// // cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<ans<<"\n";
	// return ans;
// }

void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++)a[i]={{read(),i},{read(),i}};
	sort(a+1,a+k+1);
	// for(int i=1;i<=min(n,m);i++)(ans+=i*i*(n-i+1)*(m-i+1))%=mod;
	ans=sum4(min(n,m))-(n+m+2)*sum3(min(n,m))+(n+1)*(m+1)%mod*sum2(min(n,m));
	for(int i=1;i<=k;i++){
		ans-=calc(a[i].fi.fi,a[i].fi.fi,a[i].se.fi,a[i].se.fi);
		int pre=0,suf=0;
		for(int j=i+1;j<=k;j++){
			bool fl=0;if(a[i].se>a[j].se)swap(a[i].se,a[j].se),fl=1;
			if((!pre||a[pre].se<a[i].se)&&(!suf||a[suf].se>a[j].se)){
				ans+=calc(a[i].fi.fi,a[j].fi.fi,a[i].se.fi,a[j].se.fi);
				if(pre)ans-=calc(a[i].fi.fi,a[j].fi.fi,a[pre].se.fi,a[j].se.fi);
				if(suf)ans-=calc(a[i].fi.fi,a[j].fi.fi,a[i].se.fi,a[suf].se.fi);
				if(pre&&suf)ans+=calc(a[i].fi.fi,a[j].fi.fi,a[pre].se.fi,a[suf].se.fi);
			}
			if(fl)swap(a[i].se,a[j].se);
			if(a[i].se>a[j].se&&(!pre||a[pre].se<a[j].se))pre=j;
			if(a[i].se<a[j].se&&(!suf||a[suf].se>a[j].se))suf=j;
		}
	}
	ans%=mod,ans+=mod,ans%=mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}