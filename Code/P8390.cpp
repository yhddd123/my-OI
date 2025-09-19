#include<bits/stdc++.h>
// #define int long long
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

int n;
vector<vector<pii>> ask;
void work(){
	n=read();
	for(int k=1;k<=n;k<<=1){
		for(int j=0;j<k;j++){
			vector<pii> que;
			for(int i=1;i<=n;i+=2*k){
				if(i+k<=n)que.pb({i+j,i+k});
				for(int p=i+k+1;p+1<i+2*k;p+=2)if(p+1<=n)que.pb({p,p+1});
			}
			if(que.size())ask.pb(que);
			que.clear();
			for(int i=1;i<=n;i+=2*k){
				for(int p=i+k;p+1<i+2*k;p+=2)if(p+1<=n)que.pb({p,p+1});
			}
			if(que.size())ask.pb(que);
		}
		for(int j=0;j+1<k;j++){
			vector<pii> que;
			for(int i=1;i<=n;i+=2*k){
				for(int p=i+k+(j&1);p+1<i+2*k;p+=2)if(p+1<=n)que.pb({p,p+1});
			}
			if(que.size())ask.pb(que);
		}
		// cout<<l<<" "<<ask.size()<<"\n";
	}
	// cout<<n<<"\n";
	printf("%d\n",ask.size());
	for(auto a:ask){
		for(auto[u,v]:a)if(v<=n)printf("CMPSWP R%d R%d ",u,v);
		puts("");
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