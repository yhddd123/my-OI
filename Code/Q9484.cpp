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
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
vector<int> id1,id2;
vector<pii> ans1,ans2;
char op[3];
int que(int u,int v){
	printf("? %lld %lld\n",u,v);fflush(stdout);
	scanf("%s",op+1);
	return op[1]=='B';
}
void work(){
	n=read();
	for(int i=2;i<=n;i++){
		if(que(1,i))id1.pb(i),ans1.pb({1,i});
		else id2.pb(i),ans2.pb({1,i});
	}
	while(id1.size()&&id2.size()){
		int u=id1.back(),v=id2.back();
		if(que(u,v))id2.pop_back(),ans1.pb({u,v});
		else id1.pop_back(),ans2.pb({u,v});
	}
	printf("!\n");fflush(stdout);
	if(!id1.size())swap(ans1,ans2);
	for(auto[u,v]:ans1)printf("%lld %lld\n",u,v),fflush(stdout);
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
