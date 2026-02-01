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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,q;
char s[maxn];
char t[maxn<<1];int hd,ed;
int pl[maxn],pr[maxn];
int mx[19][maxn];
mt19937 rnd(0);
int h[maxn],val[26],bas,pw[maxn];
int calc(int l,int r){return (h[r]+mod-h[l-1]*pw[r-l+1]%mod)%mod;}
int find(int x){
	int l=x+1,r=n,res=x;
	while(l<=r){
		int mid=l+r>>1;
		if(calc(pl[mid],pr[mid]-x)==calc(pl[mid]+x,pr[mid]))res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2];
void build(int nd,int l,int r){
	mn[nd]=n+1;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,int w){
	mn[nd]=min(mn[nd],w);
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
vector<pii> upd[maxn];
vector<tuple<int,int,int>> que[maxn];
int ans[maxn];
void work(){
	n=read();scanf("%s",s+1);
	hd=n+1,ed=n;
	for(int i=1;i<=n;i++){
		if('A'<=s[i]&&s[i]<='Z'){
			t[++ed]=s[i]-'A'+'a';
		}
		else{
			t[--hd]=s[i];
		}
		pl[i]=hd,pr[i]=ed;
	}
	for(int i=1;i<=n;i++)pl[i]-=hd-1,pr[i]-=hd-1;
	for(int i=hd;i<=ed;i++)s[i-hd+1]=t[i];
	bas=rnd()%mod;for(int i=0;i<26;i++)val[i]=rnd()%mod;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)h[i]=(h[i-1]*bas+val[s[i]-'a'])%mod;
	// for(int i=1;i<=n;i++)cout<<i<<" "<<pl[i]<<" "<<pr[i]<<"\n";
	m=read();for(int i=1;i<=m;i++){
		int x=read(),p;
		upd[p=find(x)].pb({i,x});
		// cout<<x<<" "<<p<<"\n";
	}
	q=read();
	for(int i=1;i<=q;i++){
		int k=read(),l=read(),r=read();
		que[k].pb({l,r,i});
	}
	build(1,1,m);
	for(int i=n;i;i--){
		for(auto[p,w]:upd[i])modif(1,1,m,p,w);
		for(auto[l,r,id]:que[i]){
			ans[id]=query(1,1,m,l,r);
			if(ans[id]>i)ans[id]=-1;
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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