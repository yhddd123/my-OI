#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int s,x;
mt19937 rnd(time(0));
void work(){
	s=read(),x=read();
	if(__gcd(s,x)==1){
		printf("1\n%lld\n",s);
		return ;
	}
	if((s&1)&&!(x&1))printf("3\n1 "),s--;
	else printf("2\n");
	while(1){
		int u=rnd()%inf,v=s-u;
		if(__gcd(abs(u),x)==1&&__gcd(abs(v),x)==1){
			printf("%lld %lld\n",u,v);
			return ;
		}
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
