#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
using namespace std;

#define max_error 1e-3 // #define a()

int n;
vector<vector<long double> > neuron;
vector<vector<vector<long double> > > weight;
vector<vector<long double> > weight_b;
// vector<long double> actual_value;
vector<vector<vector<long double> > > error_weight;
vector<vector<long double> > error_neuron;
// long double a;
// long double b;
long double alpha;
long double alpha_rate;

void print_n_value()
{
    for (int i = 0; i < neuron.size(); i++)
    {
        printf("the value in the %d layer\n", i + 1);
        for (int j = 0; j < neuron[i].size(); j++)
        {
            cout << neuron[i][j] << endl;
        }
    }
    return;
}

void making_neurons(vector<int> &num_neurons)
{
    neuron.resize(num_neurons.size());
    for (int i = 0; i < num_neurons.size(); i++)
    {
        neuron[i].resize(num_neurons[i], 0);
        printf("the neuron in the layer %d are made\n", i + 1);
    }
    // print_n_value();
    return;
}

void resize_error_neuron()
{
    error_neuron.resize(n);
    for (int i = 0; i < n; i++)
    {
        error_neuron[i].resize(neuron[i].size(), 0);
    }
    return;
}

void topo(void)
{
    int num_layers;
    cout << "Enter the number of layers (including the input and output layers): ";
    cin >> num_layers;
    n=num_layers;
    vector<int> num_neurons(num_layers, 0);
    cout << "Enter the number of neurons in each layer: ";
    for (int i = 0; i < num_layers; i++)
    {
        cin >> num_neurons[i];
    }
    // cout << "how many layer you want(inlcuding the and the output layer input layer)\n";
    // cin>>n;
    // // n = 5;
    // cout << "enter the no of neuron in each layer\n";
    // vector<int> net(n, 0);
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> net[i];
    // }
    // // net[0] = 1;
    // // net[1] = 2;
    // // net[2] = 3;
    // // net[3] = 2;
    // // net[4] = 1;
    // // cout << "the network is 1-2-3-2-1" << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << net[i] << endl;
    // }
    making_neurons(num_neurons);
    resize_error_neuron();
    return;
}

void input_layer(const vector<long double>&input)
{
    // cout << "input the input layer vector" << endl;
    for (int i = 0; i < neuron[0].size(); i++)
    {
        neuron[0][i] = input[i];
    }
    // print_n_value();
    return;
}

void resize_error_weight(vector<vector<vector<long double>>> &error_weight)
{
    error_weight.resize(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        error_weight[i].resize(neuron[i + 1].size());
        for (int j = 0; j < error_weight[i].size(); j++)
        {
            error_weight[i][j].resize(neuron[i].size(), 0);
        }
    }
    return;
}

void print_w_values()
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < weight[i].size(); j++)
        {
            // printf("the value of the weights for the neurons in the %d layer and for the %d neuron are\n", i + 1, j + 1);
            for (int k = 0; k < weight[i][j].size(); k++)
            {
                cout << weight[i][j][k] << endl;
            }
        }
    }
    return;
}

void initialize_weights()
{
    // weight.resize(neuron.size() - 1);
    // for (int i = 0; i < n - 1; i++)
    // {
    //     weight[i].resize(neuron[i + 1].size());
    //     for (int j = 0; j < weight[i].size(); j++)
    //     {
    //         weight[i][j].resize(neuron[i].size(), 0);
    //     }
    // }

    resize_error_weight(weight);

    // std::transform(weight.begin(),weight.end(),weight.begin(),rand_());
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < weight[i].size(); j++)
        {
            for (int k = 0; k < weight[i][j].size(); k++)
            {
                weight[i][j][k] = ((long double)rand() / (RAND_MAX));
                // weight[i][j][k]=(long double) (b);
            }
        }
    }

    // print_w_values();

    return;
}

void print_baise_weight()
{
    for (int i = 0; i < n; i++)
    {
        printf("the value of the baise terms for %d layer\n", i + 1);
        for (int j = 0; j < weight_b[i].size(); j++)
        {
            cout << weight_b[i][j] << endl;
        }
    }
    return;
}

void initialize_biases()
{
    // baise.resize(n, 1);
    weight_b.resize(n);
    for (int i = 0; i < n - 1; i++)
    {
        weight_b[i].resize(n * neuron[i + 1].size(), 0);
    }
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < weight_b[i].size(); j++)
        {
            weight_b[i][j] = ((long double)rand() / (RAND_MAX));
            // weight_b[i][j] = (long double)(b);
        }
    }
    // print_baise_weight();
    return;
}




long double activation_fn(long double demo)
{
    // here the activation fn is sigmoid
    // return ((1.0) / (1 + exp((-1) * demo)));
    return tanh(demo);
}

void forward_propagation()
{
    long double demo = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < neuron[i + 1].size(); j++)
        {
            demo = weight_b[i][j];
            for (int k = 0; k < neuron[i].size(); k++)
            {
                demo += neuron[i][k] * weight[i][j][k];
            }
            demo = activation_fn(demo);
            neuron[i + 1][j] = demo;
        }
        demo = 0.0;
    }
    // print_n_value();
    return;
}



long double error_nn(const vector<long double> &target)
{
    long double error = 0.0;
    for (int i = 0; i < neuron[n - 1].size(); i++)
    {
        long double diff = neuron[n - 1][i] - target[i];
        error_neuron[n - 1][i] = 0.5 * diff * diff;
        error = max(error_neuron[n - 1][i],error);
    }
    // cout<<"the error calculated"<<endl;
    return error;
}

long double dif_activation_fn(long double n_value)
{
    // this function returns the value of the diffential activation
    long double demo;
    demo = (1 - pow(n_value, 2));
    // demo = (1 - n_value) * n_value;
    return demo;
    // return 1- pow(n_value,2);
}

void cal_new_weight() //this fuction calculate the new weights for in the back propagration step
{
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 0; j < neuron[i].size(); j++)
        {
            for (int k = 0; k < neuron[i - 1].size(); k++)
            {
                long double demo = error_neuron[i][j] * (neuron[i - 1][k] * dif_activation_fn(neuron[i][j]));
                weight[i - 1][j][k] -= (alpha * demo);
            }
        }
    }
    // std::cout << "new weights done" << std::endl;

    return;
}

void cal_new_baise_weight() // this calculates the new baise in the back propagation step
{
   for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < neuron[i + 1].size(); j++)
        {
            long double demo = dif_activation_fn(neuron[i + 1][j]);
            demo = (error_neuron[i + 1][j]) * (demo);
            weight_b[i][j] -= alpha * demo;
        }
    }
    return;
}

void cal_error_neuron() // this function calcutate the error in the neurons
{

    long double demo = 0.0;
    for (int i = n - 1; i >0; i--)
    {
        for (int j = 0; j < neuron[i - 1].size(); j++)
        {
            demo = 0;
            for (int k = 0; k < neuron[i].size(); k++)
            {
                demo += error_neuron[i][k] * (weight[i - 1][k][j] * dif_activation_fn(neuron[i][j]));
            }
            error_neuron[i - 1][j] = demo;
            // neuron[i - 1][j] -= (alpha * demo);
        }
    }
    // print_n_value();
    // cout << "error of the neurons r calculated" << endl;
    // error_neuron[0].resize(neuron[0].size(),0);
    // print_error_n();
    return;
}

void backpropagation()
{
    cal_error_neuron();
    cal_new_weight();
    cal_new_baise_weight();
    return;
}


// make a error vector for the weights for the backprop
// i can have dynamic programming to store the value of the error or vactor
// dynamic gradient step value alpha
void train_network(const vector<vector<long double> >& inputs, const vector<vector<long double> >& targets,int epochs) {
    // long double demo;
    for(int z=0;z<epochs;z++)
    {
        long double demo;
        cout<<endl<<endl << "Epoch: " << z+1 << endl;
        for (int i = 0; i < inputs.size(); i++) {
            input_layer(inputs[i]);
            forward_propagation();
            // print_n_value();
            demo = error_nn(targets[i]);
            // cout<<demo;
            backpropagation();
            // print_n_value();
        }
        cout<<"max error="<<demo<<endl;
        alpha =alpha-(alpha* alpha_rate);
        // epoch++;
    }
}




int main()
{
    srand(time(nullptr));
    
    topo();
    initialize_weights();
    initialize_biases();

    alpha = 0.1;
    alpha_rate = 0.001;

    vector<vector<long double> > inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<vector< long double> > targets = {{0}, {1}, {1}, {0}};
    cout<<"input the number of epochs"<<endl;
    int epochs;
    cin>>epochs;
    train_network(inputs, targets, epochs);

    return 0;
}
