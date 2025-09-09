#include<bits/stdc++.h>
// #define int long long
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
priority_queue<int,vector<int>,greater<int>> q,q1;int tag;
vector<int> add[maxn],del[maxn];
int v[maxn],val[maxn];
int sum[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(a[i]==-1);
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),k=read(),len=r-l+1;
		v[i]=(len-k)/2;
		if(sum[r]-sum[l-1]>v[i]){puts("Impossible");return ;}
		v[i]-=sum[r]-sum[l-1];
		add[l].pb(i),del[r+1].pb(i);
	}
	for(int i=1;i<=n;i++){
		for(int j:add[i])val[j]=v[j]+tag,q.push(val[j]);
		for(int j:del[i])q1.push(val[j]);
		while(q1.size()&&q.size()&&q1.top()==q.top())q1.pop(),q.pop();
		if(!a[i]){
			if(!q.size()||q.top()-tag>0){
				a[i]=-1;
				tag++;
			}
			else a[i]=1;
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}