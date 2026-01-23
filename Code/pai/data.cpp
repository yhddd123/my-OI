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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q;
mt19937 rnd(time(0));
void work(){
	n=rnd()%20+1;
	cout<<n<<"\n";
	for(int i=2;i<=n;i++){
		int u=rnd()%(i-1)+1,v=i,w=rnd()%10+1;
		cout<<u<<" "<<v<<" "<<w<<"\n";
	}
	vector<tuple<int,int,int>> ask;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int k=1;k<=j-i+1&&k<=5;k++)ask.pb({i,j,k});
		}
	}
	cout<<ask.size()<<"\n";
	for(auto[l,r,k]:ask)cout<<l<<" "<<r<<" "<<k<<"\n";
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