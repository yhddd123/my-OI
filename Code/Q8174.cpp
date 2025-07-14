#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,m;
vector<int> ans;
vector<int> sovle(int n,int m){
	if(m==2)return {0,(1ll<<n)-1};
	if(n==5&&m==15)return {0,1,3,4,5,7,8,9,11,12,13,15,28,29,31};
	if(m&1){
		vector<int> res=sovle(n-1,m-1);
		res.push_back((1ll<<n)-1);
		return res;
	}
	else{
		vector<int> res=sovle(n-1,m>>1);
		for(int i=0;i<m/2;i++)res.push_back(res[i]+(1ll<<n-1));
		return res;
	}
}
bool check(vector<int> res){
	for(int i:res){
		for(int j:res){
			if(*lower_bound(res.begin(),res.end(),(i&j))!=(i&j))return 0;
			if(*lower_bound(res.begin(),res.end(),(i|j))!=(i|j))return 0;
		}
	}
	return 1;
}
void work(){
	n=read();m=read();
	ans=sovle(n,m);
	sort(ans.begin(),ans.end());
	// cout<<check(ans)<<"\n";
	for(int i:ans)printf("%lld ",i);printf("\n");
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
