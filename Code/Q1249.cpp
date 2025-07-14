#include<bits/stdc++.h>
#define int long long
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
using namespace std;
const int maxn=400010;
const int inf=2e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int b[maxn],len;
int opt[maxn],u[maxn],v[maxn];
int sum[maxn<<2],cnt[maxn<<2];
void up(int nd){
	sum[nd]=sum[ls]+sum[rs];
	cnt[nd]=cnt[ls]+cnt[rs];
}
void updata(int p,int w,int nd=1,int l=1,int r=len){
	if(l==r){
		sum[nd]+=w*b[p];cnt[nd]+=w;
		return ;
	}
	if(p<=mid)updata(p,w,ls,l,mid);
	else updata(p,w,rs,mid+1,r);
	up(nd);
}
int find(int ql,int nd=1,int l=1,int r=len){//[ql,len]
	if(!sum[nd])return 0;
	if(l>=ql){
		if(l==r)return l;
		int t=find(ql,ls,l,mid);
		if(t)return t;
		return find(ql,rs,mid+1,r);
	}
	if(ql<=mid){
		int t=find(ql,ls,l,mid);
		if(t)return t;
	}
	return find(ql,rs,mid+1,r);
}
bool vis[maxn<<2];
int st[maxn<<2][3],tp;
void modif(int qr,int &fod,int &res,int nd=1,int l=1,int r=len){//[1,qr]
	if(!sum[nd]||fod<=0)return ;
	if(!vis[nd])vis[nd]=1,st[++tp][0]=nd,st[tp][1]=sum[nd],st[tp][2]=cnt[nd];
	if(r<=qr){
		if(l==r){
			int x=min((fod-1)/b[l]+1,cnt[nd]);
			cnt[nd]-=x;sum[nd]-=x*b[l];
			res+=x;fod-=x*b[l];
		}
		else{
			if(sum[rs]<=fod){
				if(!vis[rs])vis[rs]=1,st[++tp][0]=rs,st[tp][1]=sum[rs],st[tp][2]=cnt[rs];
				fod-=sum[rs];res+=cnt[rs];
				sum[rs]=0;cnt[rs]=0;
				modif(qr,fod,res,ls,l,mid);
			}
			else modif(qr,fod,res,rs,mid+1,r);
			up(nd);
		}
		return ;
	}
	if(qr>mid)modif(qr,fod,res,rs,mid+1,r);
	modif(qr,fod,res,ls,l,mid);
	up(nd);
}
int calc(int u,int v){
	if(u>=v)return 0;
	if(u<=b[1])return -1;
	int ans=0;
	while(u<v){
		int p=lower_bound(b+1,b+len+1,u)-b;
		int nxt=find(p);
		int d=min(b[nxt]+1,v)-u;int num=d;
		modif(p-1,num,ans);
		if(num>0){
			ans=-1;
			break;
		}
		u+=d-num;
	}
	while(tp){
		sum[st[tp][0]]=st[tp][1];
		cnt[st[tp][0]]=st[tp][2];
		vis[st[tp][0]]=0;
		tp--;
	}
	return ans;
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[++len]=a[i];
	m=read();
	for(int i=1;i<=m;i++){
		opt[i]=read();
		if(opt[i]==1)u[i]=read(),v[i]=read();
		else u[i]=read(),b[++len]=u[i];
	}
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;b[++len]=inf;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=m;i++)if(opt[i]!=1)u[i]=lower_bound(b+1,b+len+1,u[i])-b;
	for(int i=1;i<=n;i++)updata(a[i],1);updata(len,1);
	for(int i=1;i<=m;i++){
		if(opt[i]==1)printf("%lld\n",calc(u[i],v[i]));
		if(opt[i]==2)updata(u[i],1);
		if(opt[i]==3)updata(u[i],-1);
	}
}