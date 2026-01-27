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
const int maxn=50010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans,o;
void add(vector<int> &a,int v){
	while(a.size()>1&&a.back()>v){
		v-=a.back();a.pop_back();
		v+=a.back();a.pop_back();
	}
	if(!a.size())a.pb(v);
	else if(a[0]>v)ans+=o*(v-a[0]),a.clear();
	else a.pb(v);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),o^=(__lg(a[i])+1)&1;
	o=o?-1:1;
	vector<int> c;
	for(int i=1;i<=n;i++){
		int x=a[i],k=__lg(x);
		vector<int> b;
		for(int j=k;~j;j--)add(b,(x>>j)&1ll);
		for(int v:b)c.pb(v);
	}
	sort(c.begin(),c.end());
	// for(int i=1;i<=n;i++){
		// int x=a[i],k=__lg(x);
		// for(int j=0;j<=k;j++)cout<<((x>>j)&1);cout<<"\n";
	// }
	add(c,0),add(c,0);
	for(int i=c.size()-1,o=0;~i;i--,o^=1)ans+=(o?-1:1)*c[i];
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