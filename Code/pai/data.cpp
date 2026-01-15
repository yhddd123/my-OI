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
const int inf=20;
bool mbe;

int n,q;
mt19937 rnd(time(0));
void work(){
	n=10,q=100;
	cout<<n<<"\n";
	for(int i=2;i<=n;i++){
		cout<<"1"<<" "<<rnd()%inf+1<<"\n";
	}
	for(int i=1;i<n;i++)cout<<rnd()%inf+1<<" ";cout<<"\n";
	cout<<q<<"\n";
	for(int i=1;i<=q;i++){
		int u=rnd()%n+1,v=rnd()%n+1;
		while(u==v)v=rnd()%n+1;
		cout<<u<<" "<<v<<"\n";
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