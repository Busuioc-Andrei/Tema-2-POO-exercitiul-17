#include <iostream>

using namespace std;

class Object{
public:
Object(){
};
virtual ~Object() {};
virtual void display() = 0;
};

class ObArray : public Object {
Object **p;
int size;
int grows;
int dimens;

public:

//ObArray(int size=0,int grows, int dimens);

ObArray(int grows=2,int dimens=4){
    this->grows=grows;
    this->dimens=dimens;
    size=0;
    p=new Object*[dimens];
}

virtual ~ObArray(){
    RemoveAll();
    delete[] p;
}

void RemoveAll();
int getSize();
int add(Object* x);
int insertAt(int i, Object *x);
int removeAt(int i);
Object* getAt(int i);
virtual void display();

void reserve(int newDimens);

};


void ObArray :: RemoveAll(){
    for(int i=0;i<size;i++)
        //cout<<"test"<<i<<endl;
        delete p[i];

    size=0;
}

int ObArray :: getSize(){
    return size;
}

int ObArray :: add(Object *x){
    if(size+1>dimens)
        reserve(dimens+grows);
    size++;
    p[size-1]=x;
}

int ObArray :: insertAt(int i, Object *x){
    if(size+1>dimens)
        reserve(dimens+grows);
    size++;
    for(int k=size-1;k>i;k--){
        p[k]=p[k-1];
    }
    p[i]=x;
}


int ObArray :: removeAt(int i){
    size--;
    delete p[i];
    for(int k=i;k<size;k++)
        p[k]=p[k+1];
}

Object* ObArray :: getAt(int i){
    return p[i];
}


void ObArray :: display(){
    if(size==0)
            cout<<"Empty array";
    for(int i=0;i<size;i++){
        cout<<"p["<<i<<"]="<<endl;
        p[i]->display();
        cout<<endl;
    }
    cout<<endl;
}

void ObArray :: reserve(int newDimens){
    Object **C;
    C=new Object*[newDimens];
    for(int i=0;i<size;i++)
        C[i]=p[i];
    delete[] p;
    p=C;
    dimens=newDimens;
}







class points : public Object {
    int x;
    int y;
public:
    points(int a=0,int b=0){
        x=a;
        y=b;
    }
    virtual void display(){
        cout<<"x="<<x<<" "<<"y="<<y<<endl;
    }

};

class Complex : public Object {
    int R;
    int I;
public:
    Complex(int a=0,int b=0){
        R=a;
        I=b;
    }
    virtual void display(){
        cout<<R<<"+"<<I<<"i"<<endl;
    }
};




int main()
{
    ObArray V;
    Object *A=new points(1,2);
    Object *B=new points(3,5);
    Object *C=new points(4,6);
    Object *D=new points(2,2);
    Object *E=new Complex(5,4);
    Object *F=new Complex(9,3);

    V.add(A);
    V.add(B);
    V.add(E);
    V.add(C);
    V.insertAt(1,D);
    V.add(F);
    V.display();
    V.removeAt(2);
    V.display();
    return 0;
}
