#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
using namespace std;
const int maxn=200010;
const int inf=1e9;

mt19937 rnd(time(0));
int get(int l,int r){return l+rnd()%(r-l+1);}

int n,m,q,a[maxn];
void work(){
	n=100,m=5;
	cout<<n<<" "<<m<<"\n";
	for(int i=1;i<=m;i++){
		int l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)swap(l,r);
		cout<<rnd()%n<<" "<<l<<" "<<r<<"\n";
	}
}

int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("A.in","w",stdout);
	
	T=10;
	cout<<T<<"\n";
	while(T--)work();
}