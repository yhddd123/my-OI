#include<bits/stdc++.h>
#define int long long
#define mod 100001
using namespace std;
const int maxn=500010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn];
int pre[maxn<<2],suf[maxn<<2];
int pw[maxn];
void build(int nd,int l,int r){
	pre[nd]=suf[nd]=0;
	if(l==r)return ;
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int p){
	if(l==r){
		pre[nd]=suf[nd]=1;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	pre[nd]=(pre[ls]+pre[rs]*pw[mid-l+1]%mod)%mod;
	suf[nd]=(suf[ls]*pw[r-mid]%mod+suf[rs])%mod;
}
int cnt,res;
void query1(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		res+=pre[nd]*pw[cnt]%mod;res%=mod;
		cnt+=r-l+1;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)query1(ls,l,mid,ql,qr);
	if(qr>mid)query1(rs,mid+1,r,ql,qr);
}
void query2(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		res+=suf[nd]*pw[cnt]%mod;res%=mod;
		cnt+=r-l+1;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr>mid)query2(rs,mid+1,r,ql,qr);
	if(ql<=mid)query2(ls,l,mid,ql,qr);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();bool fl=0;
		for(int i=1;i<=n;i++)a[i]=read();
		pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*n%mod;
		build(1,1,n);
		for(int i=1;i<=n;i++){
			int val=0;
			if(2*a[i]-1<=n){
				res=cnt=0;query1(1,1,n,1,a[i]);val=res;
				res=cnt=0;query2(1,1,n,a[i],2*a[i]-1);
				if(val!=res){
					printf("Y\n");fl=1;
					break;
				}
			}
			else{
				res=cnt=0;query1(1,1,n,2*a[i]-n,a[i]);val=res;
				res=cnt=0;query2(1,1,n,a[i],n);
				if(val!=res){
					printf("Y\n");fl=1;
					break;
				}
			}
			updata(1,1,n,a[i]);
		}
		if(!fl)printf("N\n");
	}
}
