// Problem: P10684 [COTS 2024] 分割 Segregacija
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10684
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-05-27 19:25:21
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,q;
char s[maxn];
int a[2][maxn],sum[maxn],val[maxn],f[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2],tag[maxn<<2];
#define pl max(0ll,sum[n]-n)
#define pr sum[n]/2
#define all 1,pl,pr
void upd(int nd,int w){tree[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=min(tree[ls],tree[rs]);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	if(tag[nd])down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
void work(){
	n=read();q=read();
	for(int j=0;j<2;j++){
		scanf("%s",s+1);
		for(int i=1;i<=n;i++)a[j][i]=s[i]=='P';
	}
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[0][i]+a[1][i];
	int num=0;for(int i=1;i<=n;i++)num+=a[1][i];
	int s=0;for(int i=1;i<=n;i++)s+=a[0][i]*i+a[1][i]*i;
	for(int i=pl;i<=pr;i++)updata(all,i,i,abs(i-num)+s-i*(i+1)/2-(sum[n]-i)*(sum[n]-i+1)/2);
	for(int i=1;i<=n;i++)val[i]=sum[i]-i;
	for(int i=1;i<n;i++){
		int l=pl,r=min(val[i]-1,pr);
		if(l>r)continue;
		f[l]++,f[r+1]--;
		updata(all,l,r,2*val[i]);
	}
	// cout<<num<<"\n";
	// for(int i=1;i<=n;i++)cout<<val[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)f[i]+=f[i-1];
	for(int i=pl;i<=pr;i++)updata(all,i,i,-2*f[i]*i);
	// for(int i=pl;i<=pr;i++)cout<<query(all,i)<<" ";cout<<"\n";
	printf("%lld\n",tree[1]);
	while(q--){
		int op=read();
		if(op==1){
			int j=read()-1,i=read();
			int w=val[i];
			val[i]-=a[0][i]+a[1][i];
			swap(a[j][i],a[j][i+1]);
			val[i]+=a[0][i]+a[1][i];
			w=val[i]-w;
			// cout<<i<<" "<<val[i]<<" "<<w<<"\n";
			int l=pl,r=min(val[i]-w-(w<0),pr);
			if(l<=r)updata(all,l,r,2*w);
			w=a[j][i]*i+a[j][i+1]*(i+1)-a[j][i]*(i+1)-a[j][i+1]*i;
			upd(1,w);
		}
		else{
			int j=read()-1,i=read();
			int w=num;
			num-=a[1][i];
			swap(a[j][i],a[j+1][i]);
			num+=a[1][i];
			w=num-w;
			if(w==1){
				updata(all,pl,num-1,1),updata(all,num,pr,-1);
			}
			if(w==-1){
				updata(all,pl,num,-1),updata(all,num+1,pr,1);
			}
		}
		// for(int i=1;i<=n;i++)cout<<a[0][i];cout<<"\n";
		// for(int i=1;i<=n;i++)cout<<a[1][i];cout<<"\n";
		// for(int i=pl;i<=pr;i++)cout<<query(all,i)<<" ";cout<<"\n";
		printf("%lld\n",tree[1]);
	}
}

bool med;
int T;
signed main(){
	// freopen("matrix.in","r",stdin);
	// freopen("matrix.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}