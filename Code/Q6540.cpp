#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=300010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],t[maxn],ans;
priority_queue<int> q;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	int c=0;
	for(int i=1,j=1;i<=n;){
		while(j<n&&a[j+1]==a[i])j++;
		for(int k=i;k<=j;k++)a[i]=c;
		if(j==n)break;
		t[++c]=j-i+1;
		i=j+1;
	}
	ans=n-c;
	// cout<<ans<<"\n";
	for(int i=c,s=0;i;i--){
		s++;s-=t[i]+1;ans++;
		q.push(t[i]+1);
		// cout<<i<<" "<<t[i]<<" "<<s<<" "<<ans<<"\n";
		while(s<0)s+=q.top(),q.pop(),ans--;
	}
	while(!q.empty())q.pop();
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
