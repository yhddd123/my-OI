#include<bits/stdc++.h>
#define ll long long
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=1048576;
const ll inf=1e18;
bool mbe;

inline void chkmn(int &u,int v){(u>v)&&(u=v);} 
inline void chkmx(int &u,int v){(u<v)&&(u=v);} 
inline void chkmnll(ll &u,ll v){(u>v)&&(u=v);} 
inline void chkmxll(ll &u,ll v){(u<v)&&(u=v);} 

int n,a[maxn],v[maxn];
ll dp[maxn];
int lsh[16][maxn],len;
int val[maxn],id[maxn];
int b[maxn],c[maxn];
ll mn[maxn];
int m;
void init(int n){
	for(m=1;m<=n+1;m<<=1);
	for(int i=1;i<m;i++)mn[i]=inf;
}
void updata(int j){
	int l=c[j],r=val[j];ll v=dp[j];
	for(l+=m-1,r+=m+1,l>>=1,r>>=1;l^r^1;l>>=1,r>>=1){
		if(~l&1)chkmnll(mn[l^1],v);
		if(r&1)chkmnll(mn[r^1],v);
	}
}
ll query(int p){
	ll ans=inf;
	p+=m,p>>=1;
	while(p){
		chkmnll(ans,mn[p]);
		p>>=1;
	}
	return ans;
}
int st[maxn],tp;
const int B=50;
int cnt[maxn],pos[maxn];
void init(int l,int r,int d=0){
	if(r-l<=B){
		for(int i=l;i<=r;i++)lsh[d][i]=a[i];
		sort(lsh[d]+l,lsh[d]+r+1);
		return ;
	}
	int mid=l+r>>1;
	init(l,mid,d+1),init(mid+1,r,d+1);
	int p=l,q=mid+1,pp=l;
	while(p<=mid&&q<=r){
		if(lsh[d+1][p]<lsh[d+1][q])lsh[d][pp++]=lsh[d+1][p++];
		else lsh[d][pp++]=lsh[d+1][q++];
	}
	while(p<=mid)lsh[d][pp++]=lsh[d+1][p++];
	while(q<=r)lsh[d][pp++]=lsh[d+1][q++];
}
void sovle(int l,int r,int d=0){
	if(r-l<=B){
		int mid=l+r>>1;
		for(int i=l;i<=r;i++){
			for(int j=i-1,mx=-1;j>=l;j--)if(a[j]<a[i]){
				if(a[j]>mx)dp[i]=min(dp[i],dp[j]+v[i]);
				mx=max(mx,a[j]);
			}
		}
		return ;
	}
	int mid=l+r>>1;
	sovle(l,mid,d+1);
	len=r-l+1;for(int i=l;i<=r;i++)c[b[lsh[d][i]]]=i-l+1;
	int pp=l;
	tp=0;for(int i=mid;i>=l;i--){
		int p=b[lsh[d+1][i]];
		while(tp&&st[tp]<p)tp--;
		if(tp)val[p]=c[st[tp]];
		else val[p]=len+1;
		st[++tp]=p;
		id[pp++]=p;
	}
	tp=0;for(int i=mid+1;i<=r;i++){
		int p=b[lsh[d+1][i]];
		while(tp&&st[tp]>p)tp--;
		if(tp)val[p]=c[st[tp]];
		else val[p]=-1;
		st[++tp]=p;
	}
	// cout<<l<<" "<<r<<" s\n";
	// for(int i=l;i<=r;i++)cout<<val[i]<<" ";cout<<"\n";
	init(len+1);
	for(int i=1;i<=len+1;i++)cnt[i]=0; 
	for(int i=mid+1;i<=r;i++)cnt[val[i]+1]++;
	pos[len+1]=mid+1;for(int i=len;~i;i--)pos[i]=pos[i+1]+cnt[i+1];
	for(int i=mid+1;i<=r;i++)id[pos[val[i]+1]++]=i;
	// for(int i=mid+1;i<=r;i++)cout<<id[i]<<" ";cout<<"\n";
	for(int i=mid+1,j=l;i<=r;i++){
		const int ii=id[i];
		while(j<=mid&&c[id[j]]>val[ii])updata(id[j++]);
		chkmnll(dp[ii],query(c[ii])+v[ii]);
	}
	sovle(mid+1,r,d+1);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<=n;i++)dp[i]=inf;
	init(0,n);
	sovle(0,n);
	// for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	ll ans=inf;
	for(int i=n,mx=0;i;i--){
		if(mx<a[i])chkmnll(ans,dp[i]);
		mx=max(mx,a[i]);
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