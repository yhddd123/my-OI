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
const int maxn=200010;
const int inf=1e18;
bool mbe;

int n,t;
int a[maxn],b[maxn],id[maxn];
bool vis[maxn];
vector<int> ans;
int pre[maxn],suf[maxn];
bool check(int x,bool fl=0){
	priority_queue<pii> q1;
	int res=0;for(int i=1;i<x;i++)q1.push({a[id[i]],id[i]}),res+=a[id[i]];
	for(int i=x;i<=n;i++){
		pre[i]=res+a[id[i]];
		if(q1.size()&&q1.top().fi>a[id[i]]){
			pii p=q1.top();q1.pop();
			q1.push({a[id[i]],id[i]});
			res-=p.fi;res+=a[id[i]];
		}
	}
	while(!q1.empty())q1.pop();
	priority_queue<pii,vector<pii>,greater<pii>> q2;
	res=0;for(int i=n;i>=x;i--){
		int cnt=max(0ll,b[id[i]]-x);
		while(q1.size()<cnt&&q2.size()){
			pii p=q2.top();q2.pop();
			res+=p.fi;
			q1.push(p);
		}
		while(q1.size()>cnt){
			pii p=q1.top();q1.pop();
			res-=p.fi;
		}
		if(q1.size()!=cnt)suf[i]=inf;
		else suf[i]=res;
		if(q1.size()&&a[id[i]]<q1.top().fi){
			pii p=q1.top();q1.pop();q1.push({a[id[i]],id[i]});
			q2.push(p);
			res-=p.fi,res+=a[id[i]];
		}
		else q2.push({a[id[i]],id[i]});
	}
	// for(int p=x;p<=n;p++)cout<<p<<" "<<pre[p]<<" "<<suf[p]<<"\n";
	for(int p=x;p<=n;p++)if(pre[p]+suf[p]<=t){
		if(fl){
			sort(id+1,id+p,[&](int u,int v){return a[u]<a[v];});
			sort(id+p+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
			for(int i=1;i<x;i++)ans.pb(id[i]);
			ans.pb(id[p]);
			for(int i=p+1;i<=p+max(0ll,b[id[p]]-x);i++)ans.pb(id[i]);
		}
		return 1;
	}
	return 0;
}
void work(){
	n=read();t=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return b[u]<b[v]||(b[u]==b[v]&&a[u]<a[v]);});
	int l=1,r=n,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	printf("%lld\n",res);
	if(!res)puts("0");
	else{
		ans.clear();
		check(res,1);
		printf("%d\n",ans.size());
		sort(ans.begin(),ans.end());
		for(int u:ans)printf("%d ",u);puts("");
	}
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