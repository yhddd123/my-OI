// Problem: AT_agc016_d [AGC016D] XOR Replace
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc016_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-29 09:02:07
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],ans;
int lsh[maxn],len,t[maxn];
int f[maxn],fl[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),lsh[++len]=a[i];
	for(int i=1;i<=n;i++)b[i]=read(),lsh[++len]=b[i];
	int x=0;for(int i=1;i<=n;i++)x^=a[i];lsh[++len]=x;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(int i=1;i<=n;i++)b[i]=lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
	x=lower_bound(lsh+1,lsh+len+1,x)-lsh;
	for(int i=1;i<=n;i++)t[a[i]]++;t[x]++;
	for(int i=1;i<=n;i++){
		if(!t[b[i]]){puts("-1");return ;}
		t[b[i]]--;
	}
	for(int i=1;i<=len;i++)f[i]=i;
	for(int i=1;i<=n;i++)if(a[i]!=b[i])++ans,f[fd(a[i])]=fd(b[i]),fl[fd(a[i])]=1;
	int num=0;for(int i=1;i<=n;i++)if(f[i]==i&&fl[i])++num;
	if(num){
		ans+=num;
		if(fl[fd(x)])ans--;
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