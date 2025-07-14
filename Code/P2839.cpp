#include<bits/stdc++.h>
using namespace std;
const int maxn=20010;
static char buf[1000000],*p1=buf,*p2=buf,rev[15],out[55000000];
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
int Len=-1;
inline void write(int x){
	int len=-1;
	do{
		rev[++len]=(x%10)^0x30;
		x/=10;
	}while(x);
	while(~len)out[++Len]=rev[len--];
	out[++Len]=0xa;
}

int n,m;
struct nd{
	int num,id;
}a[maxn];
bool cmp(nd u,nd v){return u.num<v.num;}
int rt[maxn],cnt;
int sum[maxn*18],pre[maxn*18],suf[maxn*18];
int ls[maxn*18],rs[maxn*18];
void build(int &nd,int l,int r){
	if(!nd)nd=++cnt;
	if(l==r){
		sum[nd]=pre[nd]=suf[nd]=1;
		return ;
	}
	int mid=l+r>>1;
	build(ls[nd],l,mid);build(rs[nd],mid+1,r);
	sum[nd]=sum[ls[nd]]+sum[rs[nd]];
	pre[nd]=max(pre[ls[nd]],pre[rs[nd]]+sum[ls[nd]]);
	suf[nd]=max(suf[rs[nd]],suf[ls[nd]]+sum[rs[nd]]);
}
void updata(int &nd,int l,int r,int ql,int w,int nd1){
	nd=++cnt;sum[nd]=sum[nd1];pre[nd]=pre[nd1];suf[nd]=suf[nd1];
	ls[nd]=ls[nd1];rs[nd]=rs[nd1];
	if(l==r){
		sum[nd]=pre[nd]=suf[nd]=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ql,w,ls[nd1]);
	else updata(rs[nd],mid+1,r,ql,w,rs[nd1]);
	sum[nd]=sum[ls[nd]]+sum[rs[nd]];
	pre[nd]=max(pre[ls[nd]],pre[rs[nd]]+sum[ls[nd]]);
	suf[nd]=max(suf[rs[nd]],suf[ls[nd]]+sum[rs[nd]]);
}
int querysum(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	int mid=l+r>>1;
	if(qr<=mid)return querysum(ls[nd],l,mid,ql,qr);
	if(ql>mid)return querysum(rs[nd],mid+1,r,ql,qr);
	return querysum(ls[nd],l,mid,ql,qr)+querysum(rs[nd],mid+1,r,ql,qr);
}
int querypre(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return pre[nd];
	int mid=l+r>>1;
	if(qr<=mid)return querypre(ls[nd],l,mid,ql,qr);
	if(ql>mid)return querypre(rs[nd],mid+1,r,ql,qr);
	return max(querypre(ls[nd],l,mid,ql,qr),querypre(rs[nd],mid+1,r,ql,qr)+querysum(ls[nd],l,mid,ql,qr));
}
int querysuf(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return suf[nd];
	int mid=l+r>>1;
	if(qr<=mid)return querysuf(ls[nd],l,mid,ql,qr);
	if(ql>mid)return querysuf(rs[nd],mid+1,r,ql,qr);
	return max(querysuf(rs[nd],mid+1,r,ql,qr),querysuf(ls[nd],l,mid,ql,qr)+querysum(rs[nd],mid+1,r,ql,qr));
}
int p[4],ans;
bool check(int x){
	int sum=0;
	if(p[2]-1>=p[1]+1)sum+=querysum(rt[x],1,n,p[1]+1,p[2]-1);
	sum+=querysuf(rt[x],1,n,p[0],p[1]);
	sum+=querypre(rt[x],1,n,p[2],p[3]);
	return sum>=0;
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i].num=read(),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	build(rt[1],1,n);
	for(int i=2;i<=n;i++)updata(rt[i],1,n,a[i-1].id,-1,rt[i-1]);
	m=read();
	while(m--){
		for(int i=0;i<4;i++)p[i]=(read()+ans)%n+1;
		sort(p,p+4);
		int l=1,r=n,res=1,mid;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid)){
				l=mid+1;
				res=mid;
			}
			else r=mid-1;
		}
		write(a[res].num);
		ans=a[res].num;
	}
	fwrite(out,1,Len,stdout);
}
