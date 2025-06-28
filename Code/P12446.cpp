// Problem: P12446 [COTS 2025] 答好位 / Vrsta
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12446
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-14 20:05:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>

using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=515;
#define pb push_back

// int A[maxn],Tim;
// int Ans[maxn][maxn];
int que(int l,int r){
	printf("? %d %d\n",l,r);fflush(stdout);
	return read();
	
	// ++Tim;assert(Tim<=2048);
	// return Ans[l][r];
}

int n,q;
int f[maxn][maxn];
int ls[maxn],rs[maxn],pl[maxn],pr[maxn];
int build(int l,int r,int op){
	if(l>r)return 0;
	if(l==r){pl[l]=pr[l]=l;return l;}
	int u=op?que(l,r+1):que(l-1,r);
	pl[u]=l,pr[u]=r;
	// cout<<l<<" "<<r<<" "<<u<<"\n";
	ls[u]=build(l,u-1,1),rs[u]=build(u+1,r,0);
	return u;
}
void sovle(int u,int l,int r){
	if(!u)return ;
	sovle(ls[u],l,u-1),sovle(rs[u],u+1,r);
	vector<int> idl,idr;
	int x=ls[u];
	while(x){
		idl.pb(x);
		for(int i=(pl[ls[x]]?pl[ls[x]]:x);i<=x;i++)f[i][u]=x;
		x=rs[x];
	}
	x=rs[u];
	while(x){
		idr.pb(x);
		for(int i=x;i<=(pr[rs[x]]?pr[rs[x]]:x);i++)f[u][i]=x;
		x=ls[x];
	}
	// cout<<u<<" "<<l<<" "<<r<<"\n";
	int p=0,q=0;
	while(p<idl.size()&&q<idr.size()){
		int se=que(idl[p],idr[q]);
		if(se==idl[p]){
			for(int i=(pl[ls[idl[p]]]?pl[ls[idl[p]]]:idl[p]);i<=idl[p];i++){
				for(int j=u+1;j<=(pr[rs[idr[q]]]?pr[rs[idr[q]]]:idr[q]);j++)f[i][j]=se;
			}
			p++;
		}
		else{			
			for(int i=(pl[ls[idl[p]]]?pl[ls[idl[p]]]:idl[p]);i<u;i++){
				for(int j=idr[q];j<=(pr[rs[idr[q]]]?pr[rs[idr[q]]]:idr[q]);j++)f[i][j]=se;
			}
			q++;
		}
	}
}
signed main(){
	n=read();
	// for(int i=1;i<=n;i++)A[i]=read();
	// for(int i=1;i<=n;i++){
		// for(int j=i+1;j<=n;j++){
			// int p=0;for(int k=i;k<=j;k++)if(A[k]>A[p])p=k;
			// int pp=0;for(int k=i;k<=j;k++)if(k!=p&&A[k]>A[pp])pp=k;
			// Ans[i][j]=pp;
		// }
	// }
	
	int se=que(1,n),mx=0;
	if(se>1&&que(1,se)==se){
		int l=1,r=se-1;
		while(l<=r){
			int mid=l+r>>1;
			if(que(mid,se)==se)mx=mid,l=mid+1;
			else r=mid-1;
		}
	}
	else{
		int l=se+1,r=n;
		while(l<=r){
			int mid=l+r>>1;
			if(que(se,mid)==se)mx=mid,r=mid-1;
			else l=mid+1;
		}
	}
	// cout<<mx<<" "<<se<<"\n";
	ls[mx]=build(1,mx-1,1),rs[mx]=build(mx+1,n,0);
	sovle(mx,1,n);
	
	// for(int i=1;i<=n;i++){
		// for(int j=i+1;j<=n;j++)cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<Ans[i][j]<<"\n";
	// }
	
	printf("!\n");fflush(stdout);
	q=read();
	while(q--){
		int l=read(),r=read();
		printf("%d\n",f[l][r]);fflush(stdout);
	}
}