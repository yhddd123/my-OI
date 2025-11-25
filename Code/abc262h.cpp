// Problem: AT_abc262_h [ABC262Ex] Max Limited Sequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc262_h
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-24 18:25:40
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

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,k,q,ans=1;
int lim[maxn],lsh[maxn],len;
tuple<int,int,int> ask[maxn];
int st[18][maxn];
int quemx(int l,int r){
	int k=__lg(r-l+1);
	return max(st[k][l],st[k][r-(1<<k)+1]);
}
vector<pii> que[maxn];
vector<int> upd[maxn];
int f[maxn],sum,tag,pos;
void work(){
	n=read();k=read();q=read();
	for(int i=0;i<18;i++){
		for(int j=1;j<=n;j++)st[i][j]=k;
	}
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),x=read();lsh[++len]=x;ask[i]={l,r,x};
		int k=__lg(r-l+1);
		st[k][l]=min(st[k][l],x),st[k][r-(1<<k)+1]=min(st[k][r-(1<<k)+1],x);
	}
	for(int i=17;i;i--){
		for(int j=1;j+(1<<i)-1<=n;j++){
			st[i-1][j]=min(st[i-1][j],st[i][j]);
			st[i-1][j+(1<<i-1)]=min(st[i-1][j+(1<<i-1)],st[i][j]);
		}
	}
	for(int i=1;i<=n;i++)lim[i]=st[0][i];
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	lsh[++len]=k;sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=q;i++){
		auto[l,r,x]=ask[i];
		if(quemx(l,r)<x){puts("0");return ;}
		x=lower_bound(lsh+1,lsh+len+1,x)-lsh;
		que[x].pb({l,r});
	}
	for(int i=1;i<=len;i++)upd[i].pb(0);
	for(int i=1;i<=n;i++){
		int x=lower_bound(lsh+1,lsh+len+1,lim[i])-lsh;
		upd[x].pb(i);
	}
	for(int i=1;i<=len;i++){
		f[0]=sum=1,tag=1,pos=0;
		sort(que[i].begin(),que[i].end(),[&](pii u,pii v){return u.se<v.se;});
		for(int j=1,p=0;j<upd[i].size();j++){
			while(p<que[i].size()&&que[i][p].se<upd[i][j]){
				while(upd[i][pos]<que[i][p].fi)(sum+=mod-f[pos++]*tag%mod)%=mod;
				p++;
			}
			tag=tag*lsh[i]%mod;
			f[j]=sum*ksm(tag)%mod;
			sum=sum*(lsh[i]+1)%mod;
			if(j+1==upd[i].size()){
				while(p<que[i].size()){
					while(upd[i][pos]<que[i][p].fi)(sum+=mod-f[pos++]*tag%mod)%=mod;
					p++;
				}
			}
			// cout<<i<<" "<<j<<" "<<sum<<" "<<tag<<"\n";
		}
		// cout<<i<<" "<<lsh[i]<<" "<<sum<<"\n";
		ans=ans*sum%mod;
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