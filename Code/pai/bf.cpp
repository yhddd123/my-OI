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
const int inf=1e9;
bool mbe;

int n,qq,k,a[maxn];
void work(){
	n=read();qq=read();k=read();
	priority_queue<int> q;
	for(int i=1;i<=n;i++)q.push(read());
	while(qq--){
		char ch=getchar();
		while(ch!='A'&&ch!='C')ch=getchar();
		if(ch=='A'){
			int t=read();
			for(int i=1;i<=n;i++)a[i]=q.top(),q.pop();
			cout<<a[t]<<"\n";
			for(int i=1;i<=n;i++)q.push(a[i]);
		}
		else{
			int t=read();
			while(t--){
				int v=q.top();q.pop();q.push(v-k);
			}
		}
		
	}
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}