/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on Feb 23rd, 2022, 8:36 PM
 * Purpose:  Dynamic Object Arrays
 */

//User Libraries
#include <iostream>
using namespace std;

//User Libraries
class RowAray{
    private:
        int size;
        int *rowData;
        int mrkRand(int);
    public:
        RowAray(int);
        ~RowAray();
        int getSize(){return size;}
        int getData(int i){return rowData[i];}
};

int RowAray::mrkRand(int seed){
    unsigned int a=31051;
    unsigned int c=997;
    unsigned int shrt=1<<15-1;
    unsigned int m=1<<31-1;
    static int Xn=30937;
    static int cnt=0;
    if(cnt==0&&seed<=shrt)Xn=seed;
    cnt++;
    Xn=(a*Xn+c)%m;
    return Xn;
}

RowAray::RowAray(int n){
    size=n;
    rowData=new int[size];
    for(int i=0;i<size;i++){
        rowData[i]=mrkRand(size)%90+10;
    }
}

RowAray::~RowAray(){
    delete[] rowData;
}

class Table{
    private:
        int szRow;
        int szCol;
        RowAray **records;
    public:
        Table(int,int);
        ~Table();
        int getSzRow(){return szRow;}
        int getSzCol(){return szCol;}
        int getData(int,int);
};

Table::Table(int rows,int cols){
    szRow = rows;
    szCol = cols;
    records = new RowAray*[szRow];
    for (int i = 0; i < szRow; i++) {
        records[i] = new RowAray(szCol);
    }
}

Table::~Table(){
    for (int i = 0; i < szRow; i++) {
        delete records[i];
    }
    delete[] records;
}

int Table::getData(int row,int col){
    return records[row]->getData(col);
}

class Triangle{
    private:
        int szRow;
        RowAray **records;
    public:
        Triangle(int);
        ~Triangle();
        int getSzRow(){return szRow;}
        int getData(int,int);
};

Triangle::Triangle(int rows){
    szRow = rows;
    records = new RowAray*[szRow];
    for (int i = 0; i < szRow; i++) {
        records[i] = new RowAray(i + 1);
    }
}

Triangle::~Triangle(){
    for (int i = 0; i < szRow; i++) {
        delete records[i];
    }
    delete[] records;
}

int Triangle::getData(int row,int col){
    return records[row]->getData(col);
}

//Function Prototypes
void prntRow(RowAray *,int);
void prntTab(Table *);
void prntTri(Triangle *);

//Execution Begins Here!
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    int rows,cols,perLine;
    
    cout<<"Input Rows and Cols"<<endl;
    cin>>rows>>cols;
    perLine=cols/2;
    
    RowAray row(cols);
    
    cout<<"The Row Array size = "<<row.getSize()
        <<" printed "<<perLine<<" per Line";
    prntRow(&row,perLine);
    
    Table tab(rows,cols);
    
    cout<<"The table size is [row,col] = ["<<rows<<","<<cols<<"]";
    prntTab(&tab);
    
    Triangle tri(rows);
    
    cout<<"The triangular table size is [row,row] = ["<<rows<<","<<rows<<"]";
    prntTri(&tri);

    return 0;
}

void prntRow(RowAray *a,int perLine){
    cout<<endl;
    for(int i=0;i<a->getSize();i++){
        cout<<a->getData(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

void prntTab(Table *a){
    cout<<endl;
    for(int row=0;row<a->getSzRow();row++){
        for(int col=0;col<a->getSzCol();col++){
            cout<<a->getData(row,col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void prntTri(Triangle *a){
    cout<<endl;
    for(int row=0;row<a->getSzRow();row++){
        for(int col=0;col<=row;col++){
            cout<<a->getData(row,col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
