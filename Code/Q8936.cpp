#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=65;
const int inf=1e12;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans=-inf,a[maxn];
vector<int> que[maxn];
int st[maxn],tp;
priority_queue<int,vector<int>,greater<int>> q;
void dfs(int sum,int lst,int w){
	if(sum>n)return ;
	if(sum==n){
		if(ans>w)return ;
		while(!q.empty())q.pop();
		bool fl=1;
		// for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<w<<"\n";
		for(int i=1,k=1;i<=lst;i++){
			for(int j:que[i])q.push(j);
			while(k<=tp&&i==st[k]){
				if(q.size()<st[k]||q.top()<st[k]){fl=0;break;}
				for(int l=1;l<=st[k];l++)q.pop();k++;
			}
		}
		if(fl)ans=w;
		return ;
	}
	for(int i=lst;sum+i<=n;i++){
		st[++tp]=i;
		dfs(sum+i,i,w+a[i]);
		tp--;
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		que[l].push_back(r);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(0,1,0);
	if(ans==-inf)puts("impossible");
	else printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	 // freopen("team.in","r",stdin);
	 // freopen("team.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}