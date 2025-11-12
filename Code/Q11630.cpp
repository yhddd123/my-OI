#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=1000010;
const int maxm=4010;
const int inf=1e9;
bool mbe;

int n,m,k,ans;
vector<pii> a,b;
int cx[maxn],cy[maxn],pre[maxn],suf[maxn];
vector<int> e[maxm];
int dis[maxm],num[maxm];
bool ban[maxm];
int id(int i,int j){
	return i*b.size()+j+1;
}
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
queue<int> q;
pii pp[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++){
		int x=read()+1,y=read()+1;
		pp[i]={x,y};
		cx[x]++,cy[y]++;
	}
	for(int i=1;i<=n;i++)pre[i]=(pre[i-1]+m-cx[i])%mod;
	suf[n+1]=0;for(int i=n;i;i--)suf[i]=(suf[i+1]+m-cx[i])%mod;
	for(int i=1;i<n;i++)if(!cx[i]&&!cx[i+1])(ans+=pre[i]*suf[i+1])%=mod;
	for(int i=1;i<=m;i++)pre[i]=(pre[i-1]+n-cy[i])%mod;
	suf[m+1]=0;for(int i=m;i;i--)suf[i]=(suf[i+1]+n-cy[i])%mod;
	for(int i=1;i<m;i++)if(!cy[i]&&!cy[i+1])(ans+=pre[i]*suf[i+1])%=mod;
	// cout<<ans<<"\n";
	int lst=0;for(int i=1;i<=n;i++)if(cx[i]){
		if(lst+1<i)a.pb({lst+1,i-1});
		a.pb({i,i});lst=i;
	}
	if(lst<n)a.pb({lst+1,n});
	lst=0;for(int i=1;i<=m;i++)if(cy[i]){
		if(lst+1<i)b.pb({lst+1,i-1});
		b.pb({i,i});lst=i;
	}
	if(lst<m)b.pb({lst+1,m});
	// for(auto[l,r]:a)cout<<l<<" "<<r<<" a\n";
	// for(auto[l,r]:b)cout<<l<<" "<<r<<" b\n";
	for(int i=0;i<a.size();i++){
		for(int j=0;j<b.size();j++){
			num[id(i,j)]=(a[i].se-a[i].fi+1)*(b[j].se-b[j].fi+1);
			// cout<<i<<" "<<j<<" "<<num[id(i,j)]<<"\n";
			if(num[id(i,j)]==1){
				bool fl=0;for(int p=1;p<=k;p++)if(pp[p].fi==a[i].fi&&pp[p].se==b[j].fi)fl=1;
				// cout<<id(i,j)<<" "<<fl<<"\n";
				if(fl){ban[id(i,j)]=1;continue;}
			}
			num[id(i,j)]%=mod;
			for(int ii=0;ii<4;ii++){
				int ni=i+fx[ii][0],nj=j+fx[ii][1];
				if(ni<0||ni>=a.size()||nj<0||nj>=b.size())continue;
				e[id(i,j)].pb(id(ni,nj));
				// cout<<id(i,j)<<" "<<id(ni,nj)<<" e\n";
			}
		}
	}
	for(int s=1;s<=a.size()*b.size();s++)if(!ban[s]){
		for(int i=1;i<=a.size()*b.size();i++)dis[i]=0;
		dis[s]=1;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:e[u])if(!ban[v]&&!dis[v]){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
		for(int i=s+1;i<=a.size()*b.size();i++)if(!ban[i]){
			(ans+=num[s]*num[i]%mod*(dis[i]-1))%=mod;
			// cout<<s<<" "<<i<<" "<<dis[i]-1<<" "<<ans<<"\n";
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