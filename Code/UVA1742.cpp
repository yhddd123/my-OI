#include<bits/stdc++.h>
#define double long double
using namespace std;
const int maxn=2010;

int n,sum,ans;

int tot,cnt,tp;
struct nd{
	int x,y,dep,val;
}a[maxn];
struct ndd{
	double lk,rk;
	int id;
}l[maxn],r[maxn];
bool cmpl(ndd u,ndd v){
	return u.lk<v.lk;
}
bool cmpr(ndd u,ndd v){
	return u.rk<v.rk;
}

double K(int x,int y,int x2,int y2){
	return (double) (x-x2)/(y-y2);
}

void clear(){
	tot=cnt=ans=sum=0;
	tp=1;
	memset(a,0,sizeof(a));
	memset(l,0,sizeof(l));
	memset(r,0,sizeof(r));
}
void sovle(){
	clear();
	for(int i=1;i<=n;i++){
		int x,y,d;
		scanf("%d%d%d",&x,&y,&d);
		if(x==y)	continue;
		if(x>y)	swap(x,y);
		a[++tot]=(nd){x,y,d,y-x};
	}
	for(int i=1;i<=tot;i++){
		cnt=0;
		for(int j=1;j<=tot;j++){
			if(a[i].dep!=a[j].dep){
				l[++cnt].id=j;
				l[cnt].lk=K(a[i].x,a[i].dep,a[j].x,a[j].dep);
				l[cnt].rk=K(a[i].x,a[i].dep,a[j].y,a[j].dep);
				if(l[cnt].lk>l[cnt].rk)	swap(l[cnt].lk,l[cnt].rk);
				r[cnt]=l[cnt];
			}
		}
		sort(l+1,l+cnt+1,cmpl);	sort(r+1,r+cnt+1,cmpr);
		sum=a[i].val;
		ans=max(ans,sum);
		tp=1;
		for(int j=1;j<=cnt;j++){
			sum+=a[l[j].id].val;
			while(r[tp].rk<l[j].lk)	sum-=a[r[tp].id].val,++tp;
			ans=max(ans,sum);
		}
	}
	printf("%d\n",ans);
}

signed main(){
	while(~scanf("%d",&n))	sovle();
}
