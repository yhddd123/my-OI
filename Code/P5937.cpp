#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;

int n,m,f[maxn];
struct nd{
	int l,r,f;
}a[maxn];
int b[maxn],cnt;
string s;

int fd(int x){
	if(f[x]==x)return f[x];
	return f[x]=fd(f[x]);
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i].l>>a[i].r>>s;a[i].l--;
		if(s[0]=='o')a[i].f=1;
		else a[i].f=2;
		b[i*2-1]=a[i].l;b[i*2]=a[i].r;
	}
	sort(b+1,b+2*m+1);
	cnt=unique(b+1,b+2*m+1)-b-1;
	for(int i=1;i<=cnt*2;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		a[i].l=lower_bound(b+1,b+cnt+1,a[i].l)-b;
		a[i].r=lower_bound(b+1,b+cnt+1,a[i].r)-b;
		if(a[i].f==2){
			if(fd(a[i].l)==fd(a[i].r+cnt)){
				printf("%d\n",i-1);
				return 0;
			}
			f[fd(a[i].l)]=fd(a[i].r);
			f[fd(a[i].l+cnt)]=fd(a[i].r+cnt);
		}
		else{
			if(fd(a[i].l)==fd(a[i].r)){
				printf("%d\n",i-1);
				return 0;
			}
			f[fd(a[i].l)]=fd(a[i].r+cnt);
			f[fd(a[i].l+cnt)]=fd(a[i].r);
		}
	}
	printf("%d\n",m);
}

