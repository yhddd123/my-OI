#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
const int maxm=10000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
struct ask{
	int x,y;
	int id;
}q[maxn<<2];
bool cmp(ask u,ask v){
	if(u.x!=v.x)return u.x<v.x;
	return u.y<v.y;
}
int ans[maxn<<2];
pair<int,int> a[maxn];
int tree[maxm];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=maxm-10){
		tree[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i].first=read();a[i].second=read();
		a[i].first++;a[i].second++;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++){
		int u,v,uu,vv;
		u=read();v=read();uu=read();vv=read();
		u++;v++;uu++;vv++;
		q[i*4-3]={uu,vv,i*4-3};q[i*4-2]={u-1,v-1,i*4-2};
		q[i*4-1]={uu,v-1,i*4-1};q[i*4]={u-1,vv,i*4};
	}
	sort(q+1,q+4*m+1,cmp);
	for(int i=1,j=1;i<=4*m;i++){
//		cout<<i<<" "<<j<<"\n";
		while(j<=n&&a[j].first<=q[i].x){
			updata(a[j].second,1);j++;
		}
		if(!q[i].y)ans[q[i].id]=0;
		else ans[q[i].id]=query(q[i].y);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i*4-3]+ans[i*4-2]-ans[i*4-1]-ans[i*4]);
}
