#include<bits/stdc++.h>
#define int unsigned long long
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

int n,m,l,k,q,a[maxn],id[maxn];
mt19937 rnd(time(0));
void get(){
	int l=rnd()%(n+1),r=rnd()%(n-l+1);
	if(rnd()&1)swap(l,r);
	cout<<l<<" "<<r<<"\n";
}
void work(){
	n=rnd()%10+1;
	for(int i=1;i<=n;i++)a[i]=rnd()%n+1;
	sort(a+1,a+n+1);
	cout<<n<<"\n";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
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