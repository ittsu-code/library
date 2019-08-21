#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//BEGIN CUT HERE
// longest prefix suffix matching of [0, i)
vector<int> knuth_morris_pratt(const string &s){
  int n=s.size();
  vector<int> kmp(n+1,-1),mp(n+1,-1);
  for(int i=0,j=-1;i<n;i++){
    while(~j&&s[i]!=s[j]) j=kmp[j];
    kmp[i+1]=mp[i+1]=++j;
    if(i+1<n&&s[i+1]==s[j]) kmp[i+1]=kmp[j];
  }
  return mp;
}
//END CUT HERE

//INSERT ABOVE HERE
signed ABC135_D(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  string s,t;
  cin>>s>>t;

  int n=s.size(),m=t.size();

  string b;
  while(b.size()<t.size()) b+=s;
  auto mp=knuth_morris_pratt(t+'$'+b+b);

  vector<int> match(n);
  for(int i=m+1;i<=m+n;i++)
    match[i-(m+1)]=mp[i+m]==m;

  vector< vector<int> > G(n);
  for(int i=0;i<n;i++)
    if(match[i]) G[i].emplace_back((i+m)%n);

  vector<int> indeg(n,0);
  for(int i=0;i<n;i++)
    for(int j:G[i]) indeg[j]++;

  queue<int> que;
  for(int i=0;i<n;i++)
    if(indeg[i]==0) que.emplace(i);

  vector<int> dp(n,0);
  while(!que.empty()){
    int v=que.front();que.pop();
    for(int u:G[v]){
      chmax(dp[u],dp[v]+1);
      indeg[u]--;
      if(indeg[u]==0) que.emplace(u);
    }
  }

  for(int i=0;i<n;i++){
    if(indeg[i]!=0){
      cout<<-1<<endl;
      return 0;
    }
  }

  cout<<*max_element(dp.begin(),dp.end())<<endl;
  return 0;
}
/*
  verified on 2019/08/21
  https://atcoder.jp/contests/abc135/tasks/abc135_f
*/

signed main(){
  ABC135_D();
  return 0;
}
