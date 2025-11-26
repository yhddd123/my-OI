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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,x,a[maxn],ans;
int id[maxn],ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int pos[maxn];
int to[maxn],siz[maxn],num[maxn],sum[maxn],s1[maxn],s2[maxn],s3[maxn],s4[maxn];
void work(){
	n=read();x=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return u+a[u]>v+a[v];});
	for(int i=1;i<=n;i++)ff[i]=i;ff[n+1]=n+1;
	for(int ii=1;ii<=n;ii++){
		int i=id[ii];
		for(int j=fd(max(1ll,i-a[i]));j<=min(n,i+a[i]);j=fd(j)){
			to[j]=min(n,i+a[i])+1;
			ff[j]=fd(j+1);
		}
	}
	to[n+1]=n+1;
	int val=0;
	for(int i=1;i<=n;i++)siz[i]=1;
	for(int i=1;i<=n;i++){
		val+=siz[i]*(n-i+1);
		siz[to[i]]+=siz[i];
		s1[i]=val;
	}
	val-=n*(n+1)/2;
	ans=val;
	for(int i=n;i;i--)num[i]=num[to[i]]+(n-i+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+num[i];
	for(int i=1;i<=n;i++){
		s2[i]=s2[i-1]+siz[i]*(n-to[i]+1);
		s3[i]=s3[i-1]+siz[i];
		s4[i]=s4[i-1]+siz[i]*num[to[to[i]]];
	}
	// for(int i=1;i<=n;i++)cout<<to[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<num[i]<<" ";cout<<"\n";
	// cout<<ans<<"\n";
	for(int i=1,j=0;i<=n+2;i++){
		while(j<=n+1&&to[j]<i)j++;
		pos[i]=j;
	}
	for(int i=1;i<=n;i++)if(x>a[i]){
		int nw=min(n,i+x)+1;
		int pl=max(1ll,i-x),pr=pos[nw]-1;
		if(pl<=pr){
			int res=0;
			res+=(pr-pl+1)*num[nw];
			res-=sum[pr];
			res+=s1[pl-1];
			// cout<<res<<"\n";
			int p1=pos[pl],p2=pos[pos[nw+1]]-1;
			if(p1<pl)res+=s2[pl-1]-s2[p1-1];
			res+=(s3[min(pl-1,p2)]-s3[p1-1])*num[nw];
			if(p2<pl)res+=s4[pl-1]-s4[p2];
			// cout<<p2+1<<" "<<pl-1<<"\n";
			res+=(n-pl+1+n-pr+1)*(pr-pl+1)/2;
			// cout<<i<<" "<<res<<" "<<sum[pr]<<" "<<s1[pl-1]<<"\n";
			ans=min(ans,val+res);
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