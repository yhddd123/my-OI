#include<bits/stdc++.h>
#define int long long
#define y1 _y1
#define mod 19260817
using namespace std;
const int maxn=1000010;
const int inf=2e9;

int l,r;
int cnt,ans;
bool v[maxn],vis[maxn];
int p[maxn];
void s(int n){
	for(int i=2;i<=n;i++){
		if(!v[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			v[i*p[j]]=true;
			if(i%p[j]==0)break;
		}
	}
}
void sovle(){
	cin>>l>>r;
	s((1<<16));
	for(int i=1;p[i]*p[i]<=r;i++){
		for(int j=max(2ll,(l-1)/p[i])*p[i];j<=r;j+=p[i]){
			vis[j-l+1]=1;
		}
	}
	for(int i=1;i<=r-l+1;i++)if(!vis[i])++ans;
	if(l==1)cout<<ans-1<<"\n";
	else cout<<ans<<"\n";
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}

