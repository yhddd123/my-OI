#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;

int n,m;
double a[maxn],k;
double ans,ans1;
int opt,x,y;
double sum[maxn<<2],mul[maxn<<2],laz[maxn<<2];

void build(int nd,int l,int r){
	if(l==r){
		mul[nd]=a[l]*a[l];
		sum[nd]=a[l];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	mul[nd]=mul[ls]+mul[rs];
	sum[nd]=sum[ls]+sum[rs];
}

void push(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	mul[ls]+=2.0*laz[nd]*sum[ls]+1.0*(mid-l+1)*laz[nd]*laz[nd]; 
	sum[ls]+=1.0*(mid-l+1)*laz[nd];
	laz[ls]+=laz[nd];
	mul[rs]+=2.0*laz[nd]*sum[rs]+1.0*(r-mid)*laz[nd]*laz[nd]; 
	sum[rs]+=1.0*(r-mid)*laz[nd];
	laz[rs]+=laz[nd];
	laz[nd]=0;
}

void updata(int nd,int l,int r){
	if(x<=l && y>=r){
		mul[nd]+=2.0*k*sum[nd]+1.0*(r-l+1)*k*k;
		sum[nd]+=1.0*(r-l+1)*k;
		laz[nd]+=k;
		return ;
	}
	if(laz[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(x<=mid)updata(ls,l,mid);
	if(y>mid)updata(rs,mid+1,r);
	mul[nd]=mul[ls]+mul[rs];
	sum[nd]=sum[ls]+sum[rs];
}

double query1(int nd,int l,int r){
	if(x<=l && y>=r){
		return sum[nd];
	}
	if(laz[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(y<=mid)return query1(ls,l,mid);
	if(x>mid)return query1(rs,mid+1,r);
	return query1(ls,l,mid)+query1(rs,mid+1,r);
}
double query2(int nd,int l,int r){
	if(x<=l && y>=r){
		return mul[nd];
	}
	if(laz[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(y<=mid)return query2(ls,l,mid);
	if(x>mid)return query2(rs,mid+1,r);
	return query2(ls,l,mid)+query2(rs,mid+1,r);
}

void sovle(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lf",&a[i]);
	build(1,1,n);
	while(m--){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1){
			scanf("%lf",&k);
			updata(1,1,n);
		}
		else if(opt==2){
			ans=query1(1,1,n);
			printf("%.4lf\n",(double)(1.0*ans/(y-x+1)));
		}
		else{
			ans=query1(1,1,n);
			ans1=query2(1,1,n);
//			cout<<ans<<" "<<ans1<<endl;
			ans=1.0*ans/(y-x+1);ans1=1.0*ans1/(y-x+1);
			printf("%.4lf\n",ans1-ans*ans);
		}
	}
}

int t;
signed main(){
//	cin.tie(0);cout.tie(0);
//	ios::sync_with_stdio(false);
	t=1;
	while(t--)sovle();
}

