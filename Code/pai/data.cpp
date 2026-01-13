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
const int inf=1e5;
bool mbe;

int n,m,q,a[maxn];
mt19937 rnd(time(0));
int get(int l,int r){return rnd()%(r-l+1)+l;}
void work(){
	cout<<"0"<<"\n";
	n=1000,m=1000,q=1000;
	cout<<n<<" "<<m<<" "<<q<<" "<<rnd()%inf+1<<"\n";
	for(int i=1;i<=n;i++)cout<<rnd()%inf+1<<" ";cout<<"\n";
	for(int i=1;i<=m;i++)cout<<rnd()%n+1<<" "<<rnd()%n+1<<" "<<rnd()%inf+1<<"\n";
	for(int i=1;i<=q;i++)cout<<rnd()%(n+1)<<" "<<rnd()%inf+1<<"\n";
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("1.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	// cout<<T<<"\n";
	while(T--)work();
}