#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,db>
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
const int inf=1e9;
bool mbe;

int n,m,c;
int a[maxn],b[maxn];
int dp[maxn];
struct node{
	int p,l,r;
}q[maxn];int h,t;
pii calc(int v){
	int p=upper_bound(b+1,b+m+1,v)-b-1;
	if(p==m)return {m,0};
	else return {p,1.0*(v-b[p])/(b[p+1]-b[p])};
}
pii get(int l,int r){
	pii res=calc(a[r]-a[l]);
	return {dp[l]+res.fi-c,res.se};
}
void work(){
	n=read();m=read();c=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=m;i++)b[i]=b[i-1]+read();
	dp[0]=0;q[h=t=1]={0,1,n};
	for(int i=1;i<=n;i++){
		while(q[h].r<i)h++;
		dp[i]=get(q[h].p,i).fi;
		++q[h].l;if(q[h].l>q[h].r)h++;
		while(h<=t&&get(q[t].p,q[t].l)<get(i,q[t].l))t--;
		if(h<=t){
			int ll=q[t].l+1,rr=q[t].r,res=rr+1;
			while(ll<=rr){
				int mm=ll+rr>>1;
				if(get(q[t].p,mm)<get(i,mm))res=mm,rr=mm-1;
				else ll=mm+1;
			}
			q[t].r=res-1;
			if(res<=n)q[++t]={i,res,n};
		}
		else q[++t]={i,i+1,n};
	}
	printf("%lld\n",dp[n]);
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