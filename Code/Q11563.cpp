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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int f1,f2;
map<int,int> dp;
void ins(int b,int c){
	auto it=dp.upper_bound(2*a[b]-a[c]);
	while(it!=dp.end()&&b>=(*it).se)it=dp.erase(it);
	if(it==dp.begin())dp[2*a[b]-a[c]]=b;
	else{
		it--;
		if((*it).se>=b)return ;
		dp[2*a[b]-a[c]]=b;
	}
}
int que(int p){
	auto it=dp.upper_bound(p);
	if(it==dp.begin())return -1;
	else return (*--it).se;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);a[0]=a[1];
	f1=1,f2=-1;dp.clear();
	for(int i=2;i<n;i++){
		int g1=-1,g2=-1;
		g2=max(g2,que(a[i+1]));
		if(a[i+1]-a[i]<a[i]-a[i-1])dp.clear();
		if(~f1){
			if(a[i+1]-a[i]>=a[i]-a[i-2])ins(i-1,f1);
			if(a[i+1]-a[i-1]>=a[i-1]-a[f1])g1=max(g1,i-2);
		}
		if(~f2){
			if(a[i+1]-a[i]>=a[i]-a[f2])ins(i-1,i-2);
			// cout<<a[i+1]-a[i-1]<<" "<<a[i-1]-a[i-2]<<"\n";
			if(a[i+1]-a[i-1]>=a[i-1]-a[i-2])g1=max(g1,f2);
		}
		f1=g1;f2=g2;
		// cout<<f1<<" "<<f2<<"\n";
	}
	if((~f1)||(~f2)||!dp.empty())puts("YES");
	else puts("NO");
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