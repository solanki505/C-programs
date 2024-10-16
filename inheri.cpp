#include <iostream>
using namespace std;

class matrix{
protected:
    int arr[3][3];
public:
    void read(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>arr[i][j];
            }
    }}
    virtual void show(){
    cout<<"matrix\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<arr[i][j]<<' ';}
            cout<<endl;
            }
    }
};

class matrixA : public matrix{
public:
    void show()override{
    cout<<"matrixA\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<arr[i][j]<<' ';}
            cout<<endl;
            }
    }
};

class matrixB : public matrixA{
public:
    void show()override{
    cout<<"matrixB\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<arr[i][j]<<' ';}
            cout<<endl;
            }
    }
};

int main() {
    matrix m;
    matrixA m1;
    matrixB m2;
    m.read();
    m1.read();
    m2.read();
    m.show();
    m1.show();
    m2.show();

}

