#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline ll read(){
	ll x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int maxn=325;
const int maxm=12;
const int inf=1e9;
bool mbe;

const int p=317;
ll n;int m,q;
int a[maxm][maxm],b[maxm][maxm];
int val[10],k;
ll f[10][1<<maxm-1];
map<pii,int> mp;int idx;
int g[18000][maxn];ll g1[maxn];
int h[maxm][1<<maxm-1][maxn],h1[maxn][maxn],h2[maxn][maxn];
int coef[1<<maxm][1<<maxm-1],c1[1<<maxm];
int C[maxn][maxn];
vector<pii> to[1<<maxm-1];
inline void inc(int &u,int v){((u+=v)>=p)&&(u-=p);}
void work(){
	m=read();
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)a[i][j]=read()%p;a[i][i]=1;
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)b[i][j]=read()%p;b[i][i]=1;
	}
	for(int i=0;i<p;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)inc(C[i][j]=C[i-1][j],C[i-1][j-1]);
	}
	for(int s=1;s<(1<<m);s++){
		int val=1;
		for(int i=0;i<m;i++)if(s&(1<<i)){
			for(int j=0;j<m;j++)if(s&(1<<j))val=val*b[i][j]%p;
		}
		coef[s][0]=val;
	}
	for(int s=1;s<(1<<m);s++){
		int ss=(1<<m)-s-1;
		for(int t=ss;t;t=(t-1)&ss){
			int &val=c1[t]=1;
			for(int i=0;i<m;i++)if(t&(1<<i)){
				for(int j=0;j<m;j++)if(s&(1<<j))val=val*a[i][j]%p;
				for(int j=0;j<m;j++)if(t&(1<<j))val=val*b[i][j]%p;
			}
		}
		int sz=__builtin_popcount(s)-1;
		for(int s1=0;s1<(1<<sz);s1++)if(coef[s][s1]){
			coef[s][s1]%=p;
			for(int t=ss;t;t=(t-1)&ss){
				coef[s|t][s1|(1<<sz)]+=coef[s][s1]*c1[t];
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int s=0;s<(1<<i);s++){
			for(int k=0;k<p;k++){
				for(int l=0;l<p;l++)h1[k][l]=0;
				if(k*(i+1)<p)h1[k][k]=1;
			}
			for(int j=0;j<i;j++){
				if(s&(1<<j)){
					for(int k=0;k<p-1;k++){
						for(int s=k;s+(k+1)*(i-j)<p;s++)h2[k+1][s]=h1[k][s];
					}
					for(int k=0;k<p;k++){
						for(int s=0;s+k*(i-j)<p;s++)h1[k][s]=h2[k][s],h2[k][s]=0;
					}
					for(int k=0;k<p-1;k++){
						for(int s=0;s+(k+1)*(i-j)<p;s++)h1[k+1][s]+=h1[k][s];
					}
				}
				for(int k=0;k<p;k++){
					for(int s=0;s+k*(i-j)<p;s++)if(h1[k][s])h2[k][s+k]=h1[k][s]*C[s+k][s]%p,h1[k][s]=0;
				}
				for(int k=0;k<p;k++){
					for(int s=k;s+k*(i-j-1)<p;s++)h1[k][s]=h2[k][s],h2[k][s]=0;
				}
			}
			for(int k=0;k<p;k++){
				for(int ss=0;ss<p;ss++)inc(h[i][s][ss],h1[k][ss]);
			}
		}
	}
	for(int s=0;s<(1<<m-1);s++){
		int ss=(1<<m-1)-1-s;
		for(int t=ss;;t=(t-1)&ss){
			vector<pii> a;
			for(int i=0,p=0;i<m;i++)if(i==m-1||(s&(1<<i))){
				int v=0;for(int j=p;j<i;j++)v|=((t>>j)&1)<<j-p;
				a.pb({i-p,v});
				p=i+1;
			}
			sort(a.begin(),a.end());
			int s0=0,s1=0,tt=0;
			for(auto[l,v]:a){
				s1+=v<<tt;
				tt+=l;
				s0|=1<<tt;
				tt++;
			}
			s0-=1<<m-1;
			if(mp.find({s0,s1})==mp.end()){
				mp[{s,t}]=++idx;
				// cout<<s0<<" "<<s1<<" "<<idx<<"\n";
				int *gg=g[idx];
				gg[0]=1;
				for(auto[l,v]:a){
					int *hh=h[l][v];
					for(int i=0;i<p;i++){
						for(int j=0;i+j<p;j++)g1[i+j]+=gg[i]*hh[j]*C[i+j][i];
					}
					for(int i=0;i<p;i++)gg[i]=g1[i]%p,g1[i]=0;
					// for(int i=0;i<p;i++)cout<<gg[i]<<" ";cout<<"\n";
				}
			}
			to[s].pb({t,mp[{s0,s1}]});
			if(!t)break;
		}
	}
	q=read();
	while(q--){
		n=read();
		k=0;while(n)val[++k]=n%p,n/=p;
		reverse(val+1,val+k+1);
		f[0][0]=1;
		for(int i=1;i<=k;i++){
			for(int s=0;s<(1<<m-1);s++)f[i][s]=0;
			for(int s=0;s<(1<<m-1);s++)if(f[i-1][s]){
				// cout<<i-1<<" "<<s<<" "<<f[i-1][s]<<"\n";
				for(auto[t,id]:to[s])f[i][s|t]+=f[i-1][s]*g[id][val[i]];
			}
			for(int s=0;s<(1<<m-1);s++)if(f[i][s])f[i][s]%=p;
		}
		// for(int s=0;s<(1<<m-1);s++)cout<<s<<" "<<f[k][s]<<" "<<coef[(1<<m)-1][s]<<"\n";
		ll ans=0;for(int s=0;s<(1<<m-1);s++)ans+=f[k][s]*coef[(1<<m)-1][s];
		printf("%lld\n",ans%p);
	}
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