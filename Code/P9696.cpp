// Problem: P9696 [GDCPC 2023] Swapping Operation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9696
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-14 21:05:59
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int st[17][maxn];
int que(int l,int r){
	if(l>r)return (1<<30)-1;
	int k=__lg(r-l+1);
	return st[k][l]&st[k][r-(1<<k)+1];
}
int val[maxn];
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	vector<int> p,q;
	for(int i=1,v=(1<<30)-1;i<=n;i++){
		if((v&a[i])<v)p.pb(i);
		v&=a[i];
	}
	for(int i=n,v=(1<<30)-1;i;i--){
		if((v&a[i])<v)q.pb(i);
		v&=a[i];
	}
	for(int i=1;i<=n;i++)st[0][i]=a[i];
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=st[j-1][i]&st[j-1][i+(1<<j-1)];
	}
	for(int i=1;i<n;i++)ans=max(ans,que(1,i)+que(i+1,n));
	for(int i:p){
		for(int j:q){
			for(int k=i;k<j;k++)ans=max(ans,(que(1,i-1)&que(i+1,k)&a[j])+(que(k+1,j-1)&que(j+1,n)&a[i]));
		}
	}
	map<int,vector<pii>> mp;
	for(int i:p){
		for(int k=i;k<n;k++)mp[que(1,i-1)&que(i+1,k)].pb({k,que(k+1,n)&a[i]});
	}
	for(auto[v,vec]:mp){
		val[n+1]=0;for(int j=n;j;j--)val[j]=max(val[j+1],v&a[j]);
		for(auto[k,vv]:vec)ans=max(ans,val[k+1]+vv);
	}
	mp.clear();
	for(int j:q){
		for(int k=1;k<j;k++)mp[que(k+1,j-1)&que(j+1,n)].pb({k,que(1,k)&a[j]});
	}
	for(auto[v,vec]:mp){
		val[0]=0;for(int i=1;i<=n;i++)val[i]=max(val[i-1],v&a[i]);
		for(auto[k,vv]:vec)ans=max(ans,val[k]+vv);
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}