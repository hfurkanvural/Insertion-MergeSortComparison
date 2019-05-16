//
//  myExecutable.cpp
//  algo1_hw1
//
//  Created by Hasan Furkan Vural on 15.10.2018.
//  150140029
//  Copyright © 2018 H. Furkan Vural. All rights reserved.
//
/**********************************************************************************************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
While compiling please use "g++ myExecutable.cpp -algo m -feature p -size 100000 -std=c++11" as command!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class DataObj
{
public:
    string timestamp;
    string instrument_token;
    double last_price;
    string otherinfo;
    
    void getvalts(string x){timestamp=x;}
    void getvalit(string x){instrument_token=x;}
    void getvallp(string x){double fx = stod(x); last_price = fx;}
    void getvaloi(string x){otherinfo=x;}
    DataObj operator=( DataObj&) ;
    DataObj(){}
    
};
void merge(DataObj A[], int start, int end, string feature);
void merge_sort(DataObj A[], int start, int end, string feature);
void insertion_sort(DataObj A[], int size, string feature);
//DataObj objarr[maxsize];

int main(int argc, const char * argv[]) {
    
    ifstream dataFile("log_inf.csv");
    int size, i=0;
    string emptystr, algo, feature;
    
    algo = string(argv[2]);
    feature = string(argv[4]);
    size = atoi(argv[6]);
    
//    cout<<"Sort type:"<<endl<<"m for merge sort, i for insertion sort"<<endl;
//    cin>>algo;
//    cout<<"Sort variable:"<<endl<<"for timestamp ‘t’ or for last_price ‘p’"<<endl;
//    cin>>feature;
//    cout<<"Sorting size: ";
//    cin>>size;

    DataObj *objarr;
    objarr = new DataObj[size];

    if (dataFile.is_open())
    {

        getline(dataFile, emptystr, '\n');
        while (i!=size)
        {
            string ts, it, lp, oi;
            getline(dataFile, ts,',');
            getline(dataFile, it, ',');
            getline(dataFile, lp, ',');
            getline(dataFile, oi, '\n');

            objarr[i].getvalts(ts);
            objarr[i].getvalit(it);
            objarr[i].getvallp(lp);
            objarr[i].getvaloi(oi);
            i++;
        }
        
        dataFile.close();
    }
    else
        cout<<"cannot open";
    
    if (algo=="m")
    {
        clock_t begin = clock();
        merge_sort(objarr, 0, size-1, feature);
        clock_t end = clock();
        double total_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Time elapsed for merge sort:    " << total_time << endl;
    }
    else
    {
        clock_t begin = clock();
        insertion_sort(objarr, size, feature);
        clock_t end = clock();
        double total_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Time elapsed for insertion sort:    " << total_time << endl;
        
    }
 
    ofstream outp;
    outp.open("sorted.csv", ofstream::out);
    if(outp.is_open())
    {
    int j;
    outp<<emptystr<<"\n";
    for (j=0; j<size; j++)
    {
        outp<<objarr[j].timestamp<<","<<objarr[j].instrument_token<<","<<objarr[j].last_price<<","<<objarr[j].otherinfo<<"\n";
    }
    }
    outp.close();
    

    return 0;
}
DataObj DataObj::operator=( DataObj &x)
{
    timestamp = x.timestamp;
    instrument_token = x.instrument_token;
    last_price = x.last_price;
    otherinfo = x.otherinfo;
    return *this;
}
//DataObj Arr[maxsize] ;
void merge(DataObj A[ ] , int start, int end, string feature) {
 

    int mid = (end+start)/2, p = start ,q = mid+1, k=0;
    int arraysize=(end-start)+1;
    //arraysize = sizeof(A);
    
    DataObj *Arr;
    Arr = new DataObj[arraysize];
    string type;
    if (feature == "t")
    {
        for(int i = start; i <= end; i++) {
            if(p > mid)
            {
                Arr[k] = A[q];
                k++;
                q++;
            }
            
            else if ( q > end)
            {
                Arr[k] = A[p];
                k++;
                p++;
            }
            
            else if( A[p].timestamp < A[q].timestamp)
            {
                Arr[k] = A[p];
                k++;
                p++;
            }
            else
            {
                Arr[k] = A[q];
                k++;
                q++;
            }
        }
    }
    else
        for(int i = start; i <= end; i++) {
            if(p > mid)
            {
                Arr[k] = A[q];
                k++;
                q++;
            }
            
            else if ( q > end)
            {
                Arr[k] = A[p];
                k++;
                p++;
            }
            
            else if( A[p].last_price < A[q].last_price)
            {
                Arr[k] = A[p];
                k++;
                p++;
            }
            else
            {
                Arr[k] = A[q];
                k++;
                q++;
            }
        }

    for (int p=0 ; p< k ;p ++) {
        A[ start ] = Arr[p] ;
        start++;
    }
    }
    



void merge_sort (DataObj A[], int start, int end, string feature)
{

    if( start < end ) {
        int mid = (start + end) / 2  ;
        merge_sort (A, start, mid, feature);
        merge_sort (A, mid+1, end, feature);
        merge(A, start, end, feature );

    }

    
}
void insertion_sort(DataObj A[], int n, string feature)
{
    int i, j;
    DataObj obj;
    for (i = 1; i < n; i++)
    {
        obj = A[i];
        j = i-1;

        if(feature=="t")
        {
            while (j >= 0 && A[j].timestamp > obj.timestamp)
            {
                A[j+1] = A[j];
                j = j-1;
            }
            A[j+1] = obj;
        }
        else
        {
            while (j >= 0 && A[j].last_price > obj.last_price)
            {
                A[j+1] = A[j];
                j = j-1;
            }
            A[j+1] = obj;
        }

    }
}

