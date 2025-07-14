#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q,a;
multiset<int> s;
char c[5];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		a=read();
		s.insert(a);
	}
	auto it=s.begin();
	for(int i=1;i<=(n-1)/2;i++)it++;
//	cout<<*it<<"\n";
	q=read();
	while(q--){
		scanf("%s",c+1);
		if(c[1]=='a'){
			a=read();
			s.insert(a);
			n++;
			if(n&1&&a>*it)it++;
			if(!(n&1)&&a<*it)it--;
		}
		else printf("%lld\n",*it);
	}
}
