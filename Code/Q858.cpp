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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,t[1<<20],ans;
int a[maxn];
void work(){
	n=read();ans=0;
	for(int s=0;s<(1<<20);s++)t[s]=0;
	for(int i=1;i<=n;i++)t[read()]++;
	for(int g=1;g<(1<<20);g++){
		for(int v1=g;v1<(1<<20);v1+=g)if(t[v1]){
			int v2=v1^g;
			if(v1<v2&&__gcd(v1,v2)==g)ans+=t[v1]*t[v2];
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}