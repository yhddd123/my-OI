// Problem: P8376 [APIO2022] 排列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8376
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int mx=100000;
vector<int> res,lsh;
int a[110],b[110];
std::vector<int> construct_permutation(long long k){
	int tp=0;while((1ll<<(tp+1))<=k)tp++;
	k-=(1ll<<tp);
	for(int i=0;i<tp;i++)b[i]=(k>>i)&1ll;
	res.clear();
	int p1=-1,p2=-1;
	memset(a,-1,sizeof(a));
	for(int i=tp-1;~i;i--)if(b[i]){
		if(i&&b[i-1]&&(~p1)&&(~p2)){
			a[p1]--,a[i-1]=a[p2],a[p2]--,i--;
		}
		else if(~p1){
			a[i]=a[p1]-1;
			p2=p1,p1=i;
		}
		else{
			a[i]=mx-1;
			p1=i;
		}
	}
	for(int i=tp-1;~i;i--){
		res.push_back(2*mx-i);
		if(~a[i])res.push_back(a[i]);
	}
	lsh=res;sort(lsh.begin(),lsh.end());
	for(int &i:res)i=lower_bound(lsh.begin(),lsh.end(),i)-lsh.begin();
	return res;
}
signed main(){
	int T=read();
	while(T--){
		int x=read();construct_permutation(x);
		printf("%lld\n",(int)res.size());
		for(int i:res)printf("%lld ",i);printf("\n");
		// printf("%lld %lld\n",check(res),x);
	}
}