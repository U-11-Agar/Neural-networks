#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class nn
{
public:
private:
};

void main(void)
{
    int n; // this the no of free varable in the given equation
    vector<long double> x(n, 0);
    cout << "hey, babuwolf, this is c005 and this is your hard coded newral network" << endl;

    cout << "how many  free variable r there in your equation" << endl;

    cin >> n;
    cout << "n = " << n << endl;

    printf("enter the value of the free variable\n");
    for (int i = 0; i < n; i++)
    {
        cout << "input the x" << i << endl;
        cin >> x[i];
    }
    printf("how many hidden layer u want\n");
    int n_hidden;
    cin >> n_hidden;
    srand(time(NULL));
    hidden_layer_1(n, x);

    return;
}
// void baise()
// {
//  static int baise=1;
//  long double weight_baised;

// }

// can we run all neuron in diffrent core  of my computer??????????????????

// first layer
void hidden_layer_1(int n, vector<long double> &x)
{
    int nu;
    cout << "how many neuron u want in the 1st hidden layer" << endl;
    cin >> nu;
    vector<long double> x_hidden_1(nu, 0);
    vector<vector<long double>> weights(nu, vector<long double>(n, 0));

    generate(weights.begin(), weights.end(), rand);
    for (int i = 0; i < nu; i++)
    {
        neuron(i, x_hidden_1, weights[i], x);
    }
    hidden_layer_2(x_hidden_1);
    return;
}

// i have to store every weights in the somehow so that i can backprogate

void neuron(int z, vector<long double> &x_nu, vector<long double> &weight, vector<long double> &x_previous_layer)
{
    // vector <long double> weights(n);
    long double demo;
    for (int i = 0; i < weight.size(); i++)
    {
        // for (int j=0;j<x_previous_layer.size();j++){

        demo += weight[i] * x_previous_layer[i];
        // }
    }
    demo = activation_fn(demo);
    x_nu[z] = demo;

    return;
}

long double activation_fn(long double demo)
{
    long double value;
    // this function i am taking the activation function as sigmoid
    value = (1) / (1 + exp(-demo));
    return value;
}

void hidden_layer_2(vector<long double> &x_hidden_1)
{
    int nu;
    cout << "how many neuron u want in the 2st hidden layer" << endl;
    cin >> nu;
    vector<long double> x_hidden_2(nu, 0);
    vector<vector<long double>> weights(nu, vector<long double>(x_hidden_1.size(), 0));

    generate(weights.begin(), weights.end(), rand);
    for (int i = 0; i < nu; i++)
    {
        neuron(i, x_hidden_2, weights[i], x_hidden_1);
    }
    output_layer(x_hidden_2);
    return;
}

void output_layer(vector<long double> &x_hidden_2)
{
    cout << " there is only 1 neuron in the output layer\n";
    vector<long double> prediction(1, 0);
    vector<vector<long double>> weights(1, vector<long double>(x_hidden_2.size(), 0));
    generate(weights.begin(), weights.end(), rand);
    neuron(0, prediction, weights[0], x_hidden_2);
    B_prop();
    return;
}

void B_prop()
{
}

long double fn_diff(long double z)
{
    // we can use the transform fn for taking up the vector as a whole and pass every in this
    // the derivative of the activation function function. in this case this ia a sigmoid fuction

    long double demo = 0;
    demo = (1 - z) * z;
    return demo;
}