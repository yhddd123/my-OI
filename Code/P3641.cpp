// Problem: P3641 [APIO2016] 最大差分
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3641
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-08 22:10:47
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
// #include "gap.h"

extern "C" void MinMax(long long,long long,long long*,long long*);
extern "C" long long findGap(int,int);

// static void my_assert(int k){ if (!k) exit(1); }
// static int subtask_num, N;
// static long long A[100001];
// static long long call_count;
// void MinMax(long long s, long long t, long long *mn, long long *mx){
	// int lo = 1, hi = N, left = N+1, right = 0;
	// my_assert(s <= t && mn != NULL && mx != NULL);
	// while (lo <= hi){
		// int mid = (lo+hi)>>1;
		// if (A[mid] >= s) hi = mid - 1, left = mid;
		// else lo = mid + 1;
	// }
	// lo = 1, hi = N;
	// while (lo <= hi){
		// int mid = (lo+hi)>>1;
		// if (A[mid] <= t) lo = mid + 1, right = mid;
		// else hi = mid - 1;
	// }
	// if (left > right) *mn = *mx = -1;
	// else{
		// *mn = A[left];
		// *mx = A[right];
	// }
	// if (subtask_num == 1) call_count++;
	// else if (subtask_num == 2) call_count += right-left+2;
// }


using namespace std;
long long findGap(int T,int n){
	if(T==1){
		vector<long long> a(n);
		MinMax(1,1e18,&a[0],&a[n-1]);
		for(int i=1;i<=n-i-1;i++)MinMax(a[i-1]+1,a[n-i]-1,&a[i],&a[n-i-1]);
		long long ans=0;for(int i=1;i<n;i++)ans=max(ans,a[i]-a[i-1]);
		return ans;
	}
	else{
		long long a1=0,an=0;
		MinMax(1,1e18,&a1,&an);
		long long d=(an-a1+n-2)/(n-1),lst=a1,ans=d;
		for(long long i=a1+1;i<an;i+=d){
			long long mn=0,mx=0;MinMax(i,i+d-1,&mn,&mx);
			if(mn!=-1)ans=max(ans,mn-lst),lst=mx;
		}
		return ans;
	}
}

// int main(){
	// FILE *in = stdin, *out = stdout;
	// my_assert(2 == fscanf(in, "%d%d", &subtask_num, &N));
	// my_assert(1 <= subtask_num && subtask_num <= 2);
	// my_assert(2 <= N && N <= 100000);
	// for (int i=1;i<=N;i++) my_assert(1 == fscanf(in, "%lld", A+i));
	// for (int i=1;i<N;i++) my_assert(A[i] < A[i+1]);
	// fprintf(out, "%lld\n", findGap(subtask_num, N));
	// fprintf(out, "%lld\n", call_count);
// }