#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],h,t;
double ans[maxn],e[maxn];
double calc(int i,int j){
	return a[j]+e[i-j];
}
void s(int l,int r,int x,int y){
	if(l>r)return ;
	int mid=l+r>>1,p=0;
	double mx=0;
	for(int i=x;i<=min(mid,y);i++){
		if(calc(mid,i)>mx)mx=calc(mid,i),p=i;
	}
	ans[mid]=max(ans[mid],mx);
	s(l,mid-1,x,p);
	s(mid+1,r,p,y);
}


int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		e[i]=sqrt(i);
	}
	s(1,n,1,n);
	h=1;t=n;
	while(h<t){
		swap(a[h],a[t]);swap(ans[h],ans[t]);
		h++;t--;
	}
	s(1,n,1,n);
	for(int i=n;i>=1;i--)printf("%lld\n",max(0ll,(int)ceil(ans[i])-a[i]));
}

//#include<bits/stdc++.h>
//#define int long long
//#define mod 1000000007
//using namespace std;
//const int maxn=500010;
//const int inf=1e9;
//inline int read(){
//	int x=0,f=1;
//	char ch=getchar();
//	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
//	return x*f;
//}
//
//int n,a[maxn];
//int h,t,q[maxn],k[maxn];
//int l,r,mid,res;
//double ans[maxn],e[maxn];
//double calc(int i,int j){
//	return a[j]+e[i-j];
//}
//
//
//int T;
//signed main(){
//	//	freopen(".in","r",stdin);
//	//	freopen(".out","w",stdout);
//	
//	n=read();
//	for(int i=1;i<=n;i++){
//		a[i]=read();
//		e[i]=sqrt(i);
//	}
//	h=1;t=0;
//	for(int i=1;i<=n;i++){
//		while(h<t&&calc(k[t-1],q[t])<calc(k[t-1],i))--t;
//		l=i,r=n;res=r+1;
//		while(l<=r){
//			mid=l+r>>1;
//			if(calc(mid,q[t])<=calc(mid,i)){
//				res=mid;
//				r=mid-1;
//			}
//			else l=mid+1;
//		}
//		k[t]=res;q[++t]=i;
//		while(h<t&&k[h]<=i)++h;
//		ans[i]=max(ans[i],calc(i,q[h]));
//	}
//	l=1;r=n;
//	while(l<r){
//		swap(a[l],a[r]);swap(ans[l],ans[r]);
//		l++;r--;
//	}
//	h=1;t=0;
//	for(int i=1;i<=n;i++){
//		while(h<t&&calc(k[t-1],q[t])<calc(k[t-1],i))--t;
//		l=i,r=n;res=r+1;
//		while(l<=r){
//			mid=l+r>>1;
//			if(calc(mid,q[t])<=calc(mid,i)){
//				res=mid;
//				r=mid-1;
//			}
//			else l=mid+1;
//		}
//		k[t]=res;q[++t]=i;
//		while(h<t&&k[h]<=i)++h;
//		ans[i]=max(ans[i],calc(i,q[h]));
//	}
//	for(int i=n;i>=1;i--)printf("%lld\n",max(0ll,(int)ceil(ans[i])-a[i]));
//}
