// Problem: P8078 [WC2022] 秃子酋长
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8078
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-05-30 09:17:39
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=500010;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(ll x){static char buf[20];static int len=-1;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define endl puts("")

int n,m,B,a[maxn];
struct ask{
	int l,r,id;
}que[maxn];ll ans[maxn];
int pre[maxn],nxt[maxn],pos[maxn],h,t;
int l,r;ll res;
inline int abss(int x){return x<0?-x:x;}
inline void del(int p){
	int pl=pre[a[p]],pr=nxt[a[p]];
	res-=pl?abss(pos[a[p]]-pos[pl]):0;
	res-=pr?abss(pos[a[p]]-pos[pr]):0;
	res+=(pl&&pr)?abss(pos[pl]-pos[pr]):0;
	nxt[pl]=pr,pre[pr]=pl;pos[a[p]]=0;
}
inline void add(int p){
	int pl=pre[a[p]],pr=nxt[a[p]];
	nxt[pl]=a[p],pre[pr]=a[p];pos[a[p]]=p;
}
int b[maxn];
bool cmp(ask u,ask v){
	if(b[u.l]==b[v.l])return u.r>v.r;
	return u.l<v.l;
}

signed main(){
	n=read();m=read();B=1145;
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=i/B;
	for(int i=1;i<=m;i++)que[i]={read(),read(),i};
	sort(que+1,que+m+1,cmp);
	for(int i=0,j=1;i<=n/B;i++){
		l=max(i*B,1),r=n,res=0;
		for(int k=l;k<=r;k++)pos[a[k]]=k;
		for(int k=1,lst=0;k<=n;k++)if(pos[k]){
			if(lst)res+=abss(pos[k]-pos[lst]);
			pre[k]=lst,nxt[lst]=k;lst=k;
		}
		while(j<=m&&b[que[j].l]==i){
			while(r>que[j].r)del(r--);
			ll nw=res;
			while(l<que[j].l)del(l++);
			ans[que[j].id]=res;res=nw;
			while(l>max(i*B,1))add(--l);
			j++;
		}
		mems(pre,0),mems(nxt,0),mems(pos,0);
	}
	for(int i=1;i<=m;i++)write(ans[i]),endl;
}