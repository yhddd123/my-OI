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
const int maxn=22;
const int inf=1.2e9;
bool mbe;

int n,m,lim;
pii a[maxn];
int sum[1<<maxn];
pii f[1<<maxn];
pii operator*(pii u,pii v){return {min(u.fi,v.fi),((u.fi<=v.fi)*u.se+(u.fi>=v.fi)*v.se)%mod};}
vector<int> sub1[1<<maxn/2],sub2[1<<maxn/2];
void work(){
	n=read();lim=read();m=(n+1)/2;
	for(int i=0;i<n;i++)a[i]={read(),read()};
	sort(a,a+n,[&](pii u,pii v){return u.se<v.se;});
	for(int s=1;s<(1<<n);s++){
		int k=__lg(s);
		sum[s]=sum[s^(1<<k)]+a[k].fi;
	}
	for(int s=0;s<(1<<m);s++){
		for(int t=s;;t=(t-1)&s){
			sub1[s].pb(t);
			if(!t)break;
		}
		sort(sub1[s].begin(),sub1[s].end(),[&](int u,int v){return sum[u]>sum[v];});
	}
	for(int s=1;s<(1<<n-m);s++){
		int k=__lg(s),ss=s^(1<<k);
		for(int t=ss;;t=(t-1)&ss){
			sub2[s].pb(t|(1<<k));
			if(!t)break;
		}
		sort(sub2[s].begin(),sub2[s].end(),[&](int u,int v){return sum[u<<m]<sum[v<<m];});
	}
	for(int s=0;s<(1<<n);s++)f[s]={inf,0};
	f[0]={0,1};
	for(int s=1;s<(1<<m);s++){
		int k=__lg(s),ss=s^(1<<k);
		for(int t=ss;;t=(t-1)&ss){
			if(sum[t|(1<<k)]<=lim)f[s]=f[s]*f[ss^t];
			if(!t)break;
		}
		f[s].fi+=a[k].se;
		// cout<<s<<" "<<f[s].fi<<" "<<f[s].se<<"\n";
	}
	for(int s1=0;s1<(1<<m);s1++){
		for(int s2=1;s2<(1<<n-m);s2++){
			int k=__lg(s2),ss=s2^(1<<k);
			int j=0;pii val={inf,0};
			for(int s3:sub1[(1<<m)-1-s1]){
				while(j<sub2[s2].size()&&sum[s3]+sum[sub2[s2][j]<<m]<=lim){
					val=val*f[s1|((s2^sub2[s2][j])<<m)];
					// cout<<(s1|((s2^sub2[s2][j])<<m))<<" "<<val.fi<<" "<<val.se<<"\n";
					j++;
				}
				// cout<<s1<<" "<<s2<<" "<<s3<<" "<<val.fi<<" "<<val.se<<" u\n";
				f[s1|s3|(s2<<m)]=f[s1|s3|(s2<<m)]*val;
			}
			// cout<<s1<<" "<<s2<<" "<<(s1|(s2<<m))<<" "<<f[s1|(s2<<m)].fi<<" "<<f[s1|(s2<<m)].se<<"\n";
			f[s1|(s2<<m)].fi+=a[k+m].se;
		}
	}
	printf("%lld %lld\n",f[(1<<n)-1].fi,f[(1<<n)-1].se);
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