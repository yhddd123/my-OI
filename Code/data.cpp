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
const int maxn=100010;
const int inf=1e9;
bool mbe;

mt19937 rnd(time(0));
int get(int l,int r){return l+rnd()%(r-l+1);}
void work(){
	int n=50000,m=2*n-3;
	cout<<n<<" "<<m<<"\n";
	for(int i=2;i<=n;i++)cout<<"1 "<<i<<"\n",m--;
	for(int i=3;i<=n;i++)cout<<"2 "<<i<<"\n",m--;
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	freopen("A.in","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	// cout<<T<<"\n";
	while(T--)work();
}