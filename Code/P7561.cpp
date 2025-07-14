// Problem: P7561 [JOISC 2021 Day2] 道路の建設案 (Road Construction)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7561
// Memory Limit: 2 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
using namespace std;
const int maxn=250010;
const int inf=4e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k;
pii a[maxn];
int ans[maxn],tp;
set<pii> s;
bool check(int x){
	tp=0;s.clear();
	for(int i=1,l=1;i<=n;i++){
		while(a[i].first-a[l].first>x){
			s.erase(s.find({a[l].second,a[l].first}));
			l++;
		}
		auto it=s.lower_bound({a[i].second-x,-inf});
		if(it!=s.end()){
			// cout<<i<<" "<<(*it).first<<" i\n";
			while((*it).first<=a[i].second+x){
				ans[++tp]=max(abs((*it).second-a[i].first),abs((*it).first-a[i].second));
				if(tp>=k)return true;
				it++;
				if(it==s.end())break;
			}
		}
		s.insert({a[i].second,a[i].first});
	}
	return 0;
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		a[i]={u+v,u-v};
		// cout<<a[i].first<<" "<<a[i].second<<"\n";
	}
	sort(a+1,a+n+1);
	int l=1,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
		// cout<<mid<<" "<<tp<<"\n";
	}
	check(res-1);
	sort(ans+1,ans+tp+1);
	for(int i=1;i<=tp;i++)printf("%lld\n",ans[i]);
	for(int i=tp+1;i<=k;i++)printf("%lld\n",res);
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
