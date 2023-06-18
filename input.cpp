#include <iostream>
#include <ctime>
#include "new.cpp"
#include <fstream>
// #include<stdlib.h>
#include <sstream>
#include<string>

using namespace std;

int main(void)
{
    srand(time(0));
    cout << "hey, babuwolf, this is the code for the prediction house prize using ANN(31-16-16-1)" << endl;
    topo();
      int pc,u,v,ir,k[100],i=0,flag;FILE *fp;char fl[10];
fp=fopen("House-Price-Prediction-clean.csv",);
   do {fscanf(fp, “%d”,&k[i]);  i++;} while(k[i-1]!=100);
    // ifstream csv;
    // ofstream csv;
    // csv.open("housing_price_new.csv");
    // string line;
    // char *demo;
    long double demo;
    // long double line;
    // char d;
    weights();
    baised();
    resize_error_neuron();
    resize_error_weight(error_weight);
    test_input();
    // stringstream demo;
    while (csv)
    {
        for (int i = 0; i <= 31; i++)
        {

            if (i < 31)
            {
                // fscanf(csv,);
                // getline(csv, line, ',');
                // demo=&line;
                // for(int i=0;i<line.length();i++)
                // {

                // }
                // printf(typeof(line))
                // demo<<line;
                // demo= stold(line);
                // neuron[0][i]=demo;
                // neuron[0][i]<< demo;
                // neuron[0][i] = stold(line);
            }
            else
            {
                getline(csv, line, '\n');
                demo= stold(line);
                actual_value[0]=demo;
                // actual_value[0] = std::stold(line);
            }
        }
        print_n_value();
        // get(d);
        // cin>>d;
        back_prop();

        printf("the best weight for  the max_error = 1e-2 is \n");
        cout << endl
             << endl;
    }
    csv.close();
    return 0;
}
