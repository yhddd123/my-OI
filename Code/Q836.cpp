#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=300010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a,b;
int h[maxn],ta[maxn],tb[maxn];
priority_queue<int> q;
int ans,cnt=1;
void work(){
	n=read();a=read();b=read();
	for(int i=1;i<=n;i++){
		h[i]=read();
		ta[i]=((h[i]-1)%b+1+a-1)/a+1;
		tb[i]=(h[i]+b-1)/b;
		// cout<<ta[i]<<" "<<tb[i]<<"\n";
	}
	for(int i=1;i<=n;i++){
		cnt+=tb[i];
		if(cnt>=ta[i])cnt-=ta[i],q.push(ta[i]),ans++;
		else if(!q.empty()&&q.top()>ta[i])cnt+=q.top()-ta[i],q.pop(),q.push(ta[i]);
	}
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
	
	T=1;
	while(T--)work();
}
