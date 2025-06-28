// Problem: P5444 [APIO2019] 奇怪装置
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5444
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-05-12 22:51:46
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a,b,g,ans;
vector<pii> p;
void work(){
	n=read();a=read(),b=read();g=a/__gcd(a,b+1)*b;
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		if(r-l+1>=g){printf("%lld\n",g);return ;}
		l%=g,r%=g;
		if(l<=r)p.pb({l,r});
		else p.pb({0,r}),p.pb({l,g-1});
	}
	sort(p.begin(),p.end());
	int lst=-1;
	for(auto[l,r]:p){
		if(r>lst){
			ans+=r-max(lst+1,l)+1;
			lst=r;
		}
	}
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