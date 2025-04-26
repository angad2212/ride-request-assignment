//main
#include<iostream>
using namespace std;

int sum(int a, int b){
    int result = 0;
    for(int i = a; i <= b; i++){
        result += i;
    }
    return result;
}

int main(){
    int x = 1;
    int y = 4;
    int ans = sum(x,y);
    cout << ans;
}