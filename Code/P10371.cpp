// Problem: P10371 「LAOI-4」石头
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10371
// Memory Limit: 512 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2024-04-26 14:14:44
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=10000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,s,a[maxn];ll ans;
namespace GenHelper
{
    unsigned z1, z2, z3, z4, b;
    unsigned rand_()
    {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}
void srand_(unsigned x, int n)
{
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    if (!x)
        return;
    for (int i = 1; i <= n; ++i)
    {
        int j = rand_() % i + 1, k;
        k = a[i], a[i] = a[j], a[j] = k;
    }
}

int b[maxn],pre[maxn],nxt[maxn];
int l[maxn][2],r[maxn][2];
void work(){
	n=read();s=read();srand_(s,n);ans=n;
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)pre[i]=i-1,nxt[i]=i+1;
	pre[0]=0,nxt[0]=1,pre[n+1]=n,nxt[n+1]=n+1;
	for(int i=1;i<=n;i++)b[a[i]]=i;
	for(int i=1;i<=n;i++){
		int pos=b[i];
		l[pos][0]=pre[pos],l[pos][1]=pre[pre[pos]];
		r[pos][0]=nxt[pos],r[pos][1]=nxt[nxt[pos]];
		ans+=min(pos-l[pos][0]-1,r[pos][0]-pos-1);
		pre[nxt[pos]]=pre[pos],nxt[pre[pos]]=nxt[pos];
	}
	// for(int i=1;i<=n;i++)cout<<l[i][0]<<" "<<r[i][0]<<" "<<l[i][1]<<" "<<r[i][1]<<"\n";
	// printf("%lld\n",ans);
	for(int i=1;i<=n;i++){
		int x=r[l[i][0]][0]-l[i][0]+l[i][1];
		if(i<=x&&x<r[i][0])++ans;
		x=l[r[i][0]][0]-r[i][0]+r[i][1];
		if(l[i][0]<x&&x<=i)++ans;
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
