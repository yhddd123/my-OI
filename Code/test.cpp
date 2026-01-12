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
const int maxn=500010;
const int inf=1e18;
bool mbe;

int n,a[maxn],ans;
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
int id[maxn];
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]>a[v]||(a[u]==a[v]&&u<v);});
	for(int i=1;i<=n;i++)upd(i,1);
	for(int ii=1,jj=1;ii<=n;ii=jj+1){
		jj=ii;
		while(jj<n&&a[id[ii]]==a[id[jj+1]])jj++;
		int l=ii,r=jj,num=n-ii+1;
		while(l<=r){
			int p1=que(id[l]),p2=que(id[r]);
			if(p1-1<num-p2){
				ans+=p1-1;
				upd(id[l++],-1);
			}
			else{
				ans+=num-p2;
				upd(id[r--],-1);
			}
			num--;
		}
	}
	printf("%lld\n",ans);
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