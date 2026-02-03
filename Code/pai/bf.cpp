#include<bits/stdc++.h>
using namespace std;bool Mbe;
const int IN=6e6;
char _i[IN],*_I=_i;
inline int rd(){
	for(;*_I<0x30;_I++);int x=0;
	for(;*_I>0x2f;_I++)x=(x<<1)+(x<<3)+(*_I^0x30);return x;
}
namespace MAOJUN{

typedef long long ll;
const int N=1e5+5;
int n,m,l,eu[N],ev[N],ew[N],a[N],b[N];
bool s[N],ky[N];

int fa[N],ee[N];
inline int fd(int x){for(;x^fa[x];x=fa[x]=fa[fa[x]]);return x;}
inline void main(){
	n=rd();m=rd();
	for(int i=1;i<=m;i++){eu[i]=rd()+1;ev[i]=rd()+1;ew[i]=rd();}
	l=rd();
	for(int i=1;i<=l;i++){a[i]=rd();b[i]=rd();}
	for(int r=rd();r--;)s[rd()+1]=1;
	iota(fa+1,fa+n+1,1);
	for(int i=1,p=0;i<=n;i++)if(s[i]){if(p)fa[i]=p;else p=i;}
	iota(ee+1,ee+m+1,1);
	sort(ee+1,ee+m+1,[&](int i,int j){return ew[i]<ew[j];});
	ll S=0;int C=0;
	for(int o=1;o<=m;o++){
		int i=ee[o],u=fd(eu[i]),v=fd(ev[i]);
		if(u^v){ky[i]=1;C++;S+=ew[i];fa[u]=v;}
	}
	typedef tuple<int,int,ll> ti;
	vector<ti>A;
	iota(fa+1,fa+n+1,1);ll as=0,sm=0;
	for(int o=1;o<=m;o++){
		int i=ee[o],u=fd(eu[i]),v=fd(ev[i]);
		if(u^v){
			sm+=ew[i];A.emplace_back(ew[i],C,S);
			if(!ky[i]){C++;S+=ew[i];}fa[u]=v;
		}
	}
	as=sm*l+(n-1)*accumulate(b+1,b+l+1,0ll);
	iota(fa+1,fa+l+1,1);iota(ee+1,ee+l+1,1);
	sort(ee+1,ee+l+1,[&](int i,int j){return a[i]<a[j];});
	for(int o=1;o<l;o++){
		int i=ee[o],u=fd(i),v=fd(i%l+1);
		if(b[u]>b[v])swap(u,v);
		int p=lower_bound(A.begin(),A.end(),ti(a[i]-b[v],0,0))-A.begin();
		if(p==n-1)as+=a[i];
		else{auto[w,C,S]=A[p];as+=(ll)a[i]*(n-C)-b[v]*(n-1ll-C)-(sm-S);}
		fa[v]=u;
	}
	printf("%lld\n",as);
}

}bool Med;int main(){
	fread(_i,1,IN,stdin);
	MAOJUN::main();
	return 0;
}