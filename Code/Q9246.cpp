#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=5010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,d[maxn];
char s[maxn][maxn];
int fd(vector<int> id){
	if(!id.size())return 0;
	for(int i:id)d[i]=0;
	for(int i:id){
		for(int j:id)if(s[i][j]=='1')++d[i];
	}
	pii mx={0,0};
	for(int i:id)mx=max(mx,{d[i],i});
	return mx.se;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	vector<int> id;
	for(int i=1;i<=n;i++)id.pb(i);
	int p=fd(id);
	if(d[p]==n-1){puts("NOT FOUND");return ;}
	id.clear();
	for(int i=1;i<=n;i++)if(s[i][p]=='1')id.pb(i);
	int pp=fd(id);
	if(d[pp]==id.size()-1){
		id.clear();
		for(int i=1;i<=n;i++)if(s[i][pp]=='1')id.pb(i);
		int ppp=fd(id);
		printf("%lld %lld %lld\n",p,pp,ppp);
	}
	else{
		id.clear();
		for(int i=1;i<=n;i++)if(s[i][p]=='1'&&s[i][pp]=='1')id.pb(i);
		int ppp=fd(id);
		printf("%lld %lld %lld\n",p,pp,ppp);
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
