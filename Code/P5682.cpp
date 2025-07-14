#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;

int n,a[maxn];
void sovle(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;a[0]=0;
	if(n<=1)cout<<"-1\n";
	else cout<<max(a[n-2],a[n]%a[n-1]);
	
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

