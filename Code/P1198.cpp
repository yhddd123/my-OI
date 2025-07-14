#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;

int m,d;
int tree[maxn<<2];
int cnt,lst;
void updata(int nd,int l,int r,int pos,int w){
	if(l==r){
		tree[nd]=w;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(pos<=mid)updata(ls,l,mid,pos,w);
	else updata(rs,mid+1,r,pos,w);
	tree[nd]=max(tree[ls],tree[rs]);
}
void query(int nd,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		lst=max(tree[nd],lst);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(x<=mid)query(ls,l,mid,x,y);
	if(y>mid)query(rs,mid+1,r,x,y);
}
signed main(){
	cin>>m>>d;
	memset(tree,-0x3f,sizeof(tree));
	for(int i=1;i<=m;i++){
		int u;char ch;
		cin>>ch>>u;
		if(ch=='A')updata(1,1,m,++cnt,(u+lst)%d);
		else{
			lst=-1e18;
			query(1,1,m,cnt-u+1,cnt);
			printf("%lld\n",lst);
		}
	}
}

