// Problem: P4839 P 哥的桶
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4839
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-04-19 16:46:41
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=50001;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")

int n,m;
struct bas{
	int p[31],pos[31],cnt;
	void insert(int x,int id=0,int fl=2){
		// cout<<x<<" "<<id<<" "<<fl<<"\n";
		if(!x)return ;
		int ii=31-__builtin_clz(x);
		if(!p[ii]){p[ii]=x,pos[ii]=id;++cnt;return ;}
		if(fl==2&&cnt==31)return ;
		for(int i=30;~i;i--)if(x&(1<<i)){
			if(!p[i]){p[i]=x;pos[i]=id;++cnt;return ;}
			if(fl==0){
				if(id>pos[i])swap(id,pos[i]),swap(x,p[i]);
			}
			if(fl==1){
				if(id<pos[i])swap(id,pos[i]),swap(x,p[i]);
			}
			x^=p[i];
		}
	}
	int que(){
		int res=0;
		for(int i=30;~i;i--)if(p[i])res=max(res,res^p[i]);
		return res;
	}
}tree[maxn<<2];
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
void updata(int p,int w){
	int nd=1,l=1,r=n;
	while(l<=r){
		tree[nd].insert(w,p,nd&1);
		if(l==r)return ;
		if(p<=mid)nd=ls,r=mid;
		else nd=rs,l=mid+1;
	}
}
int query(int ql,int qr){
	int nd=1,l=1,r=n;
	while(l<=r){
		if(l==ql&&r==qr)return tree[nd].que();
		if(ql<=mid&&qr>mid){
			bas res;mems(res.p,0);res.cnt=0;
			for(int i=30;~i;i--)if(tree[ls].p[i]&&tree[ls].pos[i]>=ql){
				res.insert(tree[ls].p[i]);
				// cout<<tree[ls].p[i]<<" "<<tree[ls].pos[i]<<"\n";
			}
			for(int i=30;~i;i--)if(tree[rs].p[i]&&tree[rs].pos[i]<=qr){
				res.insert(tree[rs].p[i]);
				// cout<<tree[rs].p[i]<<" "<<tree[rs].pos[i]<<"\n";
			}
			// cout<<res.cnt<<"\n";
			return res.que();
		}
		if(qr<=mid)nd=ls,r=mid;
		else nd=rs,l=mid+1;
	}
}

signed main(){
	m=read();n=read();
	while(m--){
		int op=read();
		if(op==1){
			int p=read(),x=read();
			updata(p,x);
		}
		if(op==2){
			int l=read(),r=read();
			write(query(l,r));endl;
		}
	}
}