#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,w,h,ans;
struct nd{
	int x,y,v,op;
}a[maxn];
bool cmp(nd u,nd v){
	if(u.x!=v.x)return u.x<v.x;
	return u.y>v.y;
}
set<pii> s;
void work(){
	n=read();m=read();w=read();h=read();
	for(int i=1;i<=n;i++){
		int u=read(),v=read(),val=read();
		a[i]={u*h+v*w,u*h-v*w,val,1};ans+=a[i].v;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),val=read();
		a[i+n]={u*h+v*w,u*h-v*w,val,0};
	}
	sort(a+1,a+n+m+1,cmp);
//	cout<<ans<<"\n";
	for(int i=1;i<=n+m;i++){
//		cout<<a[i].x<<" "<<a[i].y<<" "<<a[i].op<<"\n";
		if(a[i].op)s.insert({a[i].y,a[i].v});
		else{
			auto it=s.lower_bound({a[i].y,0});
			while(a[i].v){
				if(it==s.end())break;
				pii p=*it;it=s.erase(it);
				int d=min(a[i].v,p.second);
				a[i].v-=d;p.second-=d;ans-=d;
				if(p.second)s.insert(p);
			}
		}
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
