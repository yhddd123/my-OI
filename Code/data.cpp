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
const int maxn=600010;
const int inf=1e9;
bool mbe;

mt19937 rnd(time(0));
int get(int l,int r){return l+rnd()%(r-l+1);}
int a[maxn];
void work(){
	int n=500000,m=500000;
	cout<<n<<" "<<m<<"\n";
	for(int i=1;i<=n;i++)a[i]=i*2;
	shuffle(a+1,a+n+1,rnd);
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	while(m--){
		int op=1,l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)swap(l,r);
		if(op)cout<<"1 "<<l<<" "<<r<<" "<<1<<"\n";
		else cout<<"2 "<<l<<" "<<r<<"\n";
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	freopen("1.in","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}