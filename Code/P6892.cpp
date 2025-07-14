#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,fl=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}
int n;
void out(int u,int v){
	printf("%d to %d\n",u,v);
}
void sovle(int l,int r){
	if(l>r)return ;
	if(r-l+1==6){
		out(l+1,l-2);
		out(r-1,l+1);
		out(l+2,l-4);
		return ;
	}
	if(r-l+1==10){
		out(r-2,l-2);
		out(l+2,r-2);
		out(l+5,l+2);
		out(l-1,r-4);
		out(r-1,l-1);
		return ;
	}
	if(r-l+1==12){
		out(r-2,l-2);
		out(r-5,r-2);
		out(l+1,r-5);
		out(l+5,l+1);
		out(l-1,l+5);
		out(r-1,l-1);
		return ;
	}
	if(r-l+1==14){
		out(r-6,l-2);
		out(l+4,r-6);
		out(r-2,l+4);
		out(l+2,r-2);
		out(r-5,l+2);
		out(l-1,r-5);
		out(r-1,l-1);
		return;
	}
	out(r-2,l-2);
	out(l+2,r-2);
	sovle(l+4,r-4);
	out(l-1,r-5);
	out(r-1,l-1);
}
signed main(){
	n=read();
	sovle(1,n*2);
}
