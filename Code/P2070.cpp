#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100010;

int n,k;
struct nd{
	int id,flag;
}a[maxn<<2];
bool cmp(nd u,nd v){
	return u.id<v.id;
}
int x,pos,cnt,lst,ans,tot;
char ch; 
signed main(){
//	freopen("ex_data1.in","r",stdin);
	scanf("%d",&n);
	k=1;
	for(int i=1;i<=n;i++){
//		cout<<i<<endl;
		scanf("%lld",&x);cin>>ch;
		ans+=x;
		if(ch=='R'){
			a[++cnt].flag=1;a[cnt].id=pos;
			a[++cnt].flag=-1;a[cnt].id=pos+x;
			pos+=x;
		}
		else{
			a[++cnt].flag=1;a[cnt].id=pos-x;
			a[++cnt].flag=-1;a[cnt].id=pos;
			pos-=x;
		}
	}
	sort(a+1,a+cnt+1,cmp);
//	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++){
		if(a[i].flag==1){
			++tot;
			if(tot>=k)lst=a[i].id;
		}
		else{
			if(tot==k)ans-=a[i].id-lst;
			--tot;
		}
	}
	printf("%lld\n",ans);
}
