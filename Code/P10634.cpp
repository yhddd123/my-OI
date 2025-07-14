// Problem: P10634 BZOJ2372 music
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10634
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-26 14:27:15
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

int n,m;
int a[maxn],b[maxn];
int cnt[26],hsh[26],id[26];
int val[26],bas,pw[maxn],hshs,hsht;
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
mt19937 rnd(time(0));
void work(){
	n=read();m=read();read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	if(n<m){
		printf("0\n");
		return ;
	}
	bas=rnd()%mod+1;for(int i=0;i<26;i++)val[i]=rnd()%mod;
	// bas=100;for(int i=0;i<26;i++)val[i]=i+1;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=m;i++)cnt[b[i]]++;
	for(int j=0,num=0;j<26;j++){
		if(cnt[j])id[j]=num++,cnt[j]=0;
	}
	for(int i=1;i<=m;i++)(hsht=hsht*bas+val[id[b[i]]])%=mod;
	// cout<<hsht<<"\n";
	vector<int> ans;
	for(int i=1;i<=m;i++){
		cnt[a[i]]++;
		inc(hsh[a[i]],pw[m-i]);
	}
	for(int j=0,num=0;j<26;j++){
		if(cnt[j])id[j]=num++;
	}
	for(int j=0;j<26;j++)if(cnt[j])inc(hshs,hsh[j]*val[id[j]]%mod);
	// for(int j=0;j<26;j++)cout<<j<<" "<<hsh[j]<<"\n";
	// cout<<hshs<<"\n";	
	if(hshs==hsht)ans.pb(1);
	for(int i=2;i<=n-m+1;i++){
		inc(hsh[a[i-1]],mod-pw[m-1]);cnt[a[i-1]]--;
		for(int j=0;j<26;j++)hsh[j]=hsh[j]*bas%mod;
		inc(hsh[a[i+m-1]],1);cnt[a[i+m-1]]++;
		for(int j=0,num=0;j<26;j++){
			if(cnt[j])id[j]=num++;
		}
		hshs=0;for(int j=0;j<26;j++)if(cnt[j])inc(hshs,hsh[j]*val[id[j]]%mod);
		// cout<<i<<" "<<hshs<<"\n";
		if(hshs==hsht)ans.pb(i);
	}
	printf("%lld\n",ans.size());
	for(int i:ans)printf("%lld\n",i);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("youran.in","r",stdin);
	// freopen("youran.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
