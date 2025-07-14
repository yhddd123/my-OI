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

int n,sum;
vector<pii> s,m,l;
void work(){
	n=read();sum=0;s.clear(),m.clear(),l.clear();
	for(int i=1;i<=n;i++){
		int x=read();
		if(sum>=600){
			printf("0\nIGNORE\n");fflush(stdout);
			continue;
		}
		if(sum+x>=600&&sum+x<=1000){
			printf("0\nTAKE\n");fflush(stdout);
			sum+=x;
			continue;
		}
		if(x>=600){
			printf("%lld\n",s.size()+m.size()+l.size());
			while(s.size())printf("%lld ",s.back().se),s.pop_back();
			while(m.size())printf("%lld ",m.back().se),m.pop_back();
			while(l.size())printf("%lld ",l.back().se),l.pop_back();
			printf("\nTAKE\n");fflush(stdout);
			sum=x;
			continue;
		}
		if(x>=400&&m.size()){
			printf("%lld\n",s.size()+m.size()+l.size()-1);
			while(s.size())printf("%lld ",s.back().se),s.pop_back();
			while(m.size()>1)printf("%lld ",m.back().se),m.pop_back();
			while(l.size())printf("%lld ",l.back().se),l.pop_back();
			printf("\nTAKE\n");fflush(stdout);
			sum=m.back().fi+x;
			continue;
		}
		if(x>=200&&x<400&&l.size()){
			printf("%lld\n",s.size()+m.size()+l.size()-1);
			while(s.size())printf("%lld ",s.back().se),s.pop_back();
			while(m.size())printf("%lld ",m.back().se),m.pop_back();
			while(l.size()>1)printf("%lld ",l.back().se),l.pop_back();
			printf("\nTAKE\n");fflush(stdout);
			sum=l.back().fi+x;
			continue;
		}
		if(x<200){
			s.pb({x,i});
			printf("0\nTAKE\n");fflush(stdout);
			sum+=x;
			continue;
		}
		if(x<400){
			m.pb({x,i});
			printf("0\nTAKE\n");fflush(stdout);
			sum+=x;
			continue;
		}
		if(l.size()){
			if(l[0].fi<=x&&l[0].fi+x>1000){
				printf("0\nIGNORE\n");fflush(stdout);
				continue;
			}
			if(l[0].fi+x<=1000){
				l.pb({x,i});sum+=x;
				vector<int> id;
				while(sum>1000){
					sum-=s.back().fi;
					id.pb(s.back().se),s.pop_back();
				}
				printf("%lld ",id.size());
				for(int j:id)printf("%lld ",j);
				printf("\nTAKE\n");fflush(stdout);
				continue;
			}
			if(l[0].fi>x){
				printf("1 %lld\nTAKE\n",l[0].se);fflush(stdout);
				sum+=x-l[0].fi;l.pop_back();l.pb({x,i});
			}
		}
		else{
			l.pb({x,i});sum+=x;
			vector<int> id;
			while(sum>1000){
				sum-=s.back().fi;
				id.pb(s.back().se),s.pop_back();
			}
			printf("%lld ",id.size());
			for(int j:id)printf("%lld ",j);
			printf("\nTAKE\n");fflush(stdout);
		}
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
	
	T=read();
	while(T--)work();
}
