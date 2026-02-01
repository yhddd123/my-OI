// Problem: P3809 【模板】后缀排序
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3809
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-01 10:15:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char s[maxn];
int sa[maxn],id[maxn],rk[maxn<<1],tmp[maxn<<1],t[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	int w=128;
	for(int i=1;i<=n;i++)++t[rk[i]=s[i]];
	for(int i=1;i<=w;i++)t[i]+=t[i-1];
	for(int i=n;i;i--)sa[t[rk[i]]--]=i;
    for(int len=1;len<n;len<<=1){
    	int cur=0;for(int i=n-len+1;i<=n;i++)id[++cur]=i;
    	for(int i=1;i<=n;i++)if(sa[i]>len)id[++cur]=sa[i]-len;
    	for(int i=1;i<=w;i++)t[i]=0;
    	for(int i=1;i<=n;i++)t[tmp[i]=rk[i]]++;
    	for(int i=1;i<=w;i++)t[i]+=t[i-1];
    	for(int i=n;i;i--)sa[t[rk[id[i]]]--]=id[i];
    	int p=0;
        for(int i=1;i<=n;i++){
            if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])rk[sa[i]]=p;
            else rk[sa[i]]=++p;
        }
        w=p;
        if(w==n)break;
    }
	for(int i=1;i<=n;i++)printf("%lld ",sa[i]);
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