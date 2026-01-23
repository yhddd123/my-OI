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

int n,q,id[maxn],fa[maxn];
mt19937 rnd(time(0));
void work(){
	n=100000,q=100000;
	cout<<n<<" "<<q<<"\n";
	for(int i=1;i<=n;i++)cout<<rnd()%inf+1<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)cout<<rnd()%n+1<<" ";cout<<"\n";
	for(int i=1;i<=q;i++){
		int o=rnd()%3+1,l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)swap(l,r);
		if(o==1)cout<<o<<" "<<l<<" "<<r<<" "<<rnd()%inf+1<<"\n";
		if(o==2)cout<<o<<" "<<l<<" "<<r<<" "<<rnd()%n+1<<"\n";
		if(o==3)cout<<o<<" "<<l<<" "<<r<<"\n";
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