#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[maxn],g[maxn];
int vl[maxn],vr[maxn],id[maxn];
#define lb(x) (x&(-x))
int tree[maxn<<1];
void upd(int x,int w){
	while(x<=n)inc(tree[x],w),x+=lb(x);
}
int que(int x){
	int res=0;
	while(x>0)inc(res,tree[x]),x-=lb(x);
	return res;
}
int que(int l,int r){
	if(l>r)return 0;
	return que(r)-que(l-1);
}
void sovle(int *f,int l,int r){
	if(l==r){
		if(a[l]==1)inc(f[l],f[l-1]);
		return ;
	}
	int mid=l+r>>1;
	sovle(f,l,mid);
	vl[mid]=a[mid];for(int i=mid-1;i>=l;i--)vl[i]=max(vl[i+1],a[i]);
	vr[mid+1]=a[mid+1];for(int i=mid+2;i<=r;i++)vr[i]=max(vr[i-1],a[i]);
	for(int i=l;i<=mid;i++)id[i]=i;
	sort(id+l,id+mid+1,[&](int u,int v){return u+vl[u]-1<v+vl[v]-1;});
	for(int j=mid+1,i=l;j<=r;j++){
		while(i<=mid&&j>=id[i]+vl[id[i]]-1){
			upd(id[i],f[id[i]-1]);
			i++;
		}
		inc(f[j],que(j-vr[j]+1));
		if(j==r){
			while(i>l){
				i--;
				upd(id[i],mod-f[id[i]-1]);
			}
		}
	}
	sovle(f,mid+1,r);
}
int ans[maxn];
void sovle(int l,int r){
	if(l==r){
		if(a[l]>1)(ans[l]+=f[l-1]*g[l+1])%=mod;
		return ;
	}
	int mid=l+r>>1;
	sovle(l,mid);
    sovle(mid+1,r);
	// cout<<l<<" "<<r<<endl;
	vl[mid+1]=0;for(int i=mid;i>=l;i--)vl[i]=max(vl[i+1],a[i]);
	vr[mid]=0;for(int i=mid+1;i<=r;i++)vr[i]=max(vr[i-1],a[i]);
	for(int i=mid+1;i<=r;i++)id[i]=i;
	sort(id+mid+1,id+r+1,[&](int u,int v){return u-vr[u]+1>v-vr[v]+1;});
	vector<pii> pos;
	for(int i=mid,lst=mid;i>=l;i--){
		if(vl[i]>vl[i+1]&&i<mid)pos.pb({i+1,lst}),lst=i;
		if(i==l)pos.pb({l,lst});
	}
	int j=mid+1;
	for(pii p:pos){
		int pl=p.fi,pr=p.se,mx=vl[pr+1];
		for(int i=pr;i>=pl;i--){
			mx=max(mx,i==pr?1:a[i]);
			while(j<=r&&id[j]-vr[id[j]]+1>=i){
				upd(id[j],g[id[j]+1]);
				j++;
			}
			(ans[pr]+=f[i-1]*(que(i+mx-1,n)-que(i+vl[i]-1,n)+mod))%=mod;
		}
	}
	for(int i=mid+1;i<j;i++)upd(id[i],mod-g[id[i]+1]);
	for(int i=l;i<=mid;i++)id[i]=i;
	sort(id+l,id+mid+1,[&](int u,int v){return u+vl[u]-1<v+vl[v]-1;});
	pos.clear();
	for(int i=mid+1,lst=mid+1;i<=r;i++){
		if(vr[i]>vr[i-1]&&i>mid+1)pos.pb({lst,i-1}),lst=i;
		if(i==r)pos.pb({lst,r});
	}
	// cout<<l<<" "<<r<<" "<<pos.size()<<" s"<<endl;
	j=l;
	for(pii p:pos){
		int pl=p.fi,pr=p.se,mx=vr[pl-1];
		for(int i=pl;i<=pr;i++){
			mx=max(mx,i==pl?1:a[i]);
			while(j<=mid&&id[j]+vl[id[j]]-1<=i){
				// cout<<l<<" "<<r<<" "<<pl<<" "<<pr<<" "<<i<<" "<<j<<endl;
				upd(id[j],f[id[j]-1]);
				j++;
			}
			// cout<<i<<" "<<j<<endl;
			(ans[pl]+=(que(i-mx+1)-que(i-vr[i]+1)+mod)*g[i+1])%=mod;
		}		
	}
	for(int i=l;i<j;i++)upd(id[i],mod-f[id[i]-1]);
	// cout<<l<<" "<<r<<" "<<ans[2]<<endl;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	f[0]=1;sovle(f,1,n);
	reverse(a+1,a+n+1);
	g[0]=1;sovle(g,1,n);
	reverse(a+1,a+n+1),reverse(g,g+n+2);
	// for(int i=0;i<=n+1;i++)cout<<f[i]<<" ";cout<<"\n";
	// for(int i=0;i<=n+1;i++)cout<<g[i]<<" ";cout<<"\n";
	sovle(1,n);
	for(int i=1;i<=n;i++)inc(ans[i],f[n]);
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
