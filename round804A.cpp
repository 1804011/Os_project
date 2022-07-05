#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll i,n,tc,u,v;
    cin>>tc;
    while(tc--){
        cin>>n;
        if(n%2==1)
            cout<<-1<<endl;
        else {
                n/=2;
            cout<<3<<" "<<(n^3)<<" "<<(n^3)<<endl;

        }
    }
}
