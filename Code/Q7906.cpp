#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,ans=1;
int cross(pii u,pii v){return u.fi*v.se-v.fi*u.se;}
pii operator+(pii u,pii v){return {u.fi+v.fi,u.se+v.se};}
pii operator-(pii u,pii v){return {u.fi-v.fi,u.se-v.se};}
void work(){
	n=read();
	vector<pii> a(n),b,c;
	for(int i=0;i<n;i++)a[i]={read(),read()};
	sort(a.begin(),a.end());
	for(int i=0;i<n;i++){
		while(b.size()>1&&cross(b[b.size()-1]-b[b.size()-2],a[i]-b[b.size()-2])<=0)b.pop_back();
		b.pb(a[i]);
	}
	int lst=b.size();
	for(int i=n-2;i>=0;i--){
		while(b.size()>lst&&cross(b[b.size()-1]-b[b.size()-2],a[i]-b[b.size()-2])<=0)b.pop_back();
		b.pb(a[i]);
	}
	b.pop_back();
	map<pii,bool> vis;for(pii p:b)vis[p]=1;
	for(pii p:a)if(vis.find(p)==vis.end())c.pb(p);
	for(int i=0;i<b.size();i++){
		for(pii &p:c)p=p-b[i];
		sort(c.begin(),c.end(),[&](pii u,pii v){return cross(u,v)>0;});
		for(pii &p:c)p=p+b[i];
		if(c.size())++ans;
		for(int j=1,k=0;j<c.size();j++){
			if(cross(c[j]-b[(i+1)%b.size()],c[k]-b[(i+1)%b.size()])<0)++ans,k=j;
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