#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=600010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k,a[maxn],ans;
priority_queue<pair<int,int> > q;
int l[maxn],r[maxn];
bool vis[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();k=read();
	if(n<2*k){
		printf("Error!");
		return 0;
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		q.push({a[i],i});
		l[i]=i-1,r[i]=i+1;
		if(!l[i])l[i]=n;
		if(r[i]==n+1)r[i]=1;
	}
	for(int i=1;i<=k;i++){
		while(q.size()&&vis[q.top().second])q.pop();
		int p=q.top().second,val=q.top().first;q.pop();
		ans+=val;
		vis[p]=vis[l[p]]=vis[r[p]]=1;
		a[++n]=a[l[p]]+a[r[p]]-a[p];
		l[n]=l[l[p]],r[n]=r[r[p]];
		r[l[l[p]]]=n,l[r[r[p]]]=n;
		q.push({a[n],n});
	}
	printf("%lld\n",ans);
}
