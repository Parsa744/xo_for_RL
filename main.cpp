#include <iostream>

using namespace std;

class rectange{
private:
    int a;
    int b;
    int c;
public:
    rectange(int A,int B,int C) {
        a = A;
        b = B;
        c = C;
    }
    int mohit(){
        return a + b + c;
    }
};

int main(){
    int x = 1;
    int y = 2;
    int z = 3;
    rectange rec(x,y,z);
    cout << rec.mohit();
}