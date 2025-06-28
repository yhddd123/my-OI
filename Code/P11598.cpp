// Problem: P11598 [NOISG 2018 Finals] Safety
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11598
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-04-16 18:01:30
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

int n,h,a[maxn],val,tag;
priority_queue<int> ql;
priority_queue<int,vector<int>,greater<int>> qr;
void work(){
	n=read();h=read();
	for(int i=1;i<=n;i++)a[i]=read();
	ql.push(a[1]),qr.push(a[1]);
	for(int i=2;i<=n;i++){
		tag+=h;
		int pl=ql.top()-tag,pr=qr.top()+tag;
		if(pl<=a[i]&&a[i]<=pr){
			ql.push(a[i]+tag),qr.push(a[i]-tag);
		}
		else if(a[i]<pl){
			val+=pl-a[i];
			ql.pop(),ql.push(a[i]+tag),ql.push(a[i]+tag),qr.push(pl-tag);
		}
		else{
			val+=a[i]-pr;
			qr.pop(),qr.push(a[i]-tag),qr.push(a[i]-tag),ql.push(pr+tag);
		}
	}
	printf("%lld\n",val);
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