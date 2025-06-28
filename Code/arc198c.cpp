// Problem: C - Error Swap
// Contest: AtCoder - AtCoder Regular Contest 198 (Div. 2)
// URL: https://atcoder.jp/contests/arc198/tasks/arc198_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-25 21:11:38
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
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn];
vector<pii> ans;
void mov(int i,int j){
	assert(i<j);
	ans.pb({i,j});
	a[i]++,a[j]--,swap(a[i],a[j]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	int sum=0;for(int i=1;i<=n;i++)sum+=a[i]-b[i];
	if(sum!=0){puts("No");return ;}
	if(n==2){
		if(a[1]==b[1])puts("Yes"),puts("0");
		else if(a[1]==b[2]-1)puts("Yes"),puts("1"),puts("1 2");
		else puts("No");
		return ;
	}
	for(int i=1;i<=n-2;i++){
		pii mn={inf,0};
		for(int j=i;j<=n;j++)mn=min(mn,{abs(b[i]-a[j]),j});
		if(i!=mn.se)mov(i,mn.se);
		while(a[i]<b[i])mov(i,i+1),mov(i+1,i+2),mov(i,i+2);
		while(a[i]>b[i])mov(i,i+2),mov(i+1,i+2),mov(i,i+1);
	}
	bool fl=0;
	if(a[n-1]<b[n-1]){
		fl=1;
		mov(n-1,n),b[n-1]++,b[n]--,swap(b[n-1],b[n]);
	}
	while(a[n-1]>b[n-1]){
		mov(n-2,n-1),mov(n-1,n),mov(n-2,n),mov(n-1,n);
		mov(n-2,n),mov(n-1,n),mov(n-2,n-1),mov(n-1,n);
	}
	if(fl){
		mov(n-1,n),b[n-1]++,b[n]--,swap(b[n-1],b[n]);
	}
	puts("Yes");
	printf("%lld\n",ans.size());
	for(auto[u,v]:ans)printf("%lld %lld\n",u,v);
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<b[i]<<" ";cout<<"\n";
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