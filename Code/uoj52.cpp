#include "kth.h"
#include <bits/stdc++.h>

// #define MaxN 100000
// #define INF 2147483647
// 
// static int a_n, b_n, c_n;
// static int a[MaxN];
// static int b[MaxN];
// static int c[MaxN];
// 
// static int tot_get;
// 
// int get_a(int p)
// {
	// tot_get++;
	// if (0 <= p && p < a_n)
		// return a[p];
	// return INF;
// }
// int get_b(int p)
// {
	// tot_get++;
	// if (0 <= p && p < b_n)
		// return b[p];
	// return INF;
// }
// int get_c(int p)
// {
	// tot_get++;
	// if (0 <= p && p < c_n)
		// return c[p];
	// return INF;
// }

using namespace std;
int query_kth(int n_a, int n_b, int n_c, int k){
	int na=0,nb=0,nc=0;
	while(k){
		int d=(k-1)/3;
		int va=get_a(na+d),vb=get_b(nb+d),vc=get_c(nc+d);
		int mn=min({va,vb,vc});
		// cout<<k<<" "<<d<<" "<<na<<" "<<nb<<" "<<nc<<" "<<va<<" "<<vb<<" "<<vc<<"\n";
		if(mn==va)na+=d+1;
		else if(mn==vb)nb+=d+1;
		else nc+=d+1;
		k-=d+1;
		if(!k)return mn;
	}
}

// int main()
// {
	// int i;
	// int res, k;
// 
	// assert(scanf("%d %d %d %d", &a_n, &b_n, &c_n, &k) == 4);
	// for (i = 0; i < a_n; i++)
		// assert(scanf("%d", &a[i]) == 1);
	// for (i = 0; i < b_n; i++)
		// assert(scanf("%d", &b[i]) == 1);
	// for (i = 0; i < c_n; i++)
		// assert(scanf("%d", &c[i]) == 1);
// 
	// tot_get = 0;
	// res = query_kth(a_n, b_n, c_n, k);
	// printf("%d %d\n", res, tot_get);
// 
	// return 0;
// }
// 