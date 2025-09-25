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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
bitset<maxn> f,g,h,hh;
void work(){
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='1')g.set(i);
		if(s[i]=='?')h.set(i);
	}
	for(int i=1;i<=n;i++){
		f=g;hh=h;
		int k=__lg(n/i+1);
		// cout<<i<<" "<<k<<"\n";
		for(int j=0;j<=k;j++){
			f|=hh&(f<<(i*(1<<j)));
			if(j<k)hh&=hh<<(i*(1<<j));
		}
		// for(int j=1;j<=n;j++)cout<<f[j];cout<<"\n";
		// for(int j=1;j<=n;j++)cout<<hh[j];cout<<"\n";
		printf("%d\n",f.count());
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