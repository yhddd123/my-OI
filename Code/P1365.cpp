#include<bits/stdc++.h>
using namespace std;
int n;
char c[300010];
double x1,x2;
signed main(){
	scanf("%d%s",&n,c+1);
	for(int i=1;i<=n;i++){
		if(c[i]=='?')x2+=(2*x1+1)*0.5,x1=(x1+1)*0.5;
		else if(c[i]=='o')x2+=2*x1+1,x1++;
		else if(c[i]=='x')x1=0;
	}
	printf("%.4lf",x2);
}
