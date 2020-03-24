#include <iostream>
#include <algorithm>

using namespace std;

class multime
{
    int size;
    int array[1000];

public:

    multime(int v[], int n);
    multime();
    multime(const multime &ob1);

    int getArray();
    int getSize();

    void elimDubluri();

    ~multime();

    multime operator+ (const multime& ob2);
    multime operator* (const multime& ob2);
    multime operator- (const multime& ob2);

    friend istream & operator >> ( istream & in, multime & ob1);
    friend ostream & operator << ( ostream & out, const multime & ob1);

};

multime::multime(int v[],int n = 0)
{
    for (int i = 0; i < n; i ++ )
        array[i] = v[i];
    size = n;
}

multime::multime() {
    size = 0;
}

multime::multime(const multime &ob1)
{
    size = ob1.size;
    const int *a = ob1.array;
    for (int i = 0; i < size; i++)
        array[i] = a[i];
}

multime::~multime() {
    size = 0;
}

int multime::getArray(){
    return *array;
}

int multime::getSize(){
    return size;
}

//--------ELIMINAM DUBLURILE SI SORTAM VECTORUL

void multime::elimDubluri() {
    sort( array , array+size );
    for(int i = 0; i < size-1; i++)

        for(int j = i+1; j < size; j++)
        if(array[i] == array[j]){

            for(int k = j+1; k < size; k++)
                array[k-1] = array[k];
            i --;
            size = size-1;
        }
}


//------REUNIUNEA A 2 MULTIMI

multime multime::operator+(const multime& ob2) {

    int vect[1000] = {0};
    int vector[1000] = {0};
    int i, k = 0, max = 0;

    for(i = 0; i < size; i++) {

            vector[array[i]] ++;
            if (array[i] > max) max = array[i];
    }

    for(i = 0; i < ob2.size; i++) {

            vector[ob2.array[i]] ++;
            if (ob2.array[i] > max) max = ob2.array[i];
    }

    for(i = 0; i <= max; i++)
        if(vector[i] > 0) {
                vect[k] = i;
                k ++ ;
        }

    multime temp(vect, k);

    return  temp;
}

//------INTERSECTIA A 2 MULTIMI

multime multime::operator*(const multime& ob2)
{
    int i, j, k = 0;
    int vect[1000] = {0};

    for(i = 0; i < size; i++) {

            for(j = 0; j < ob2.size; j++)
                if(array[i] == ob2.array[j]) {

                    vect[k] = array[i];
                    k ++;
                }
    }

    multime temp(vect, k);

    return temp;
}

//-------DIFERENTA A 2 MULTIMI

multime multime::operator-(const multime& ob2) {

   int i, j, ok, k=0;
   int vect[1000]={0};

   for(i = 0; i < size; i++) {

        ok = 1;
        for(j = 0; j < ob2.size; j ++)
            if( array[i] == ob2.array[j] ) ok = 0;
            if(ok == 1) {

                vect[k] = array[i];
                k ++;
            }
    }

    multime temp(vect, k);

    return temp;
}


istream & operator>>(istream & in, multime & ob1) {
    in >> ob1.size;
    for (int j = 0; j < ob1.size; j ++){
        in >> ob1.array[j];
    }
    return in;
}

ostream &operator<<(ostream &out, const multime &ob1) {
    out << "{";
    int i;
    if (ob1.size >= 1) {
        for (i = 0; i < ob1.size - 1; i++)
            out << ob1.array[i] << "," << " ";
        out << ob1.array[i];
    }
    out << "}";
    out << "\n";
    return out;
}


int main()
{
    multime ob1, ob2;

    cout<<"Introduceti numarul de elemente si elementele multimii 1"<<endl;

    cin >> ob1;

    cout<<"Introduceti numarul de elemente si elementele multimii 2"<<endl;

    cin >> ob2;

    ob1.elimDubluri();
    ob2.elimDubluri();

    multime ob3 = ob1 + ob2;
    multime ob4 = ob1 * ob2;
    multime ob5 = ob1 - ob2;

    cout << "MULTIMEA 1 : " << ob1;
    cout << "MULTIMEA 2 : " << ob2;
    cout << "REUNIUNEA : " << ob3;
    cout << "INTERSECTIA : " << ob4;
    cout << "DIFERENTA : " << ob5;

    return 0;
}
