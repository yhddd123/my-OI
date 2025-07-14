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

int n,ans;
string s;
void dfs(string s,int val){
	if(!s.size()){
		ans=max(ans,val);
		return ;
	}
	int n=s.size();
	for(int i=0;i<n;i++){
		int j=i;while(j+1<n&&s[j+1]==s[i])j++;
		string t;
		for(int k=0;k<i;k++)t=t+s[k];
		for(int k=j+1;k<n;k++)t=t+s[k];
		dfs(t,val+(j-i==2));
	}
}
void work(){
	cin>>s;ans=0;
	dfs(s,0);
	printf("%lld\n",ans);	
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
	
	T=read();
	while(T--)work();
}
