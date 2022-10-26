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
vector<long double> actual_value;
vector<vector<vector<long double> > > error_weight;
vector<vector<long double> > error_neuron;
// long double a;
// long double b;
long double alpha;
long double alpha_rate;

void print_n_value()
{
    for (int i = 0; i < n; i++)
    {
        printf("the value in the %d layer\n", i + 1);
        for (int j = 0; j < neuron[i].size(); j++)
        {
            cout << neuron[i][j] << endl;
        }
    }
    return;
}

void neuron_(const vector<int> &net)
{
    neuron.resize(net.size());
    for (int i = 0; i < net.size(); i++)
    {
        neuron[i].resize(net[i], 0);
        printf("the neuron in the layer %d are made\n", i + 1);
    }
    print_n_value();
    return;
}

void topo(void)
{
    // cout << "how many layer you want(inlcuding the input layer)\n";

    n = 5;
    // cout << "enter the no of neuron in each layer\n";
    vector<int> net(n, 0);
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> net[i];
    // }
    net[0] = 1;
    net[1] = 2;
    net[2] = 3;
    net[3] = 2;
    net[4] = 1;
    cout << "the network is 1-2-3-2-1" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << net[i] << endl;
    }
    neuron_(net);
    return;
}

void input_layer(long double a)
{
    cout << "input the input layer vector" << endl;
    for (int i = 0; i < neuron[0].size(); i++)
    {
        neuron[0][i] = a;
    }
    print_n_value();
    return;
}

void resize_error_weight(vector<vector<vector<long double> > > &error_weight)
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
            printf("the value of the weights for the neurons in the %d layer and for the %d neuron are\n", i + 1, j + 1);
            for (int k = 0; k < weight[i][j].size(); k++)
            {
                cout << weight[i][j][k] << endl;
            }
        }
    }
    return;
}

void weights()
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

    print_w_values();

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

void baised()
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
    print_baise_weight();
    return;
}

void print_actual()
{
    printf("the actual value vector is \n");
    for (int i = 0; i < actual_value.size(); i++)
    {
        cout << actual_value[i] << endl;
    }
    return;
}

void test_input(long double a)
{
    actual_value.resize(neuron[n - 1].size());
    printf("input the actual value vector of size %ld\n", neuron[n - 1].size());
    for (int i = 0; i < actual_value.size(); i++)
    {
        actual_value[i] = sin(a);
    }

    print_actual();
    return;
}

long double activation_fn(long double demo)
{
    // here the activation fn is sigmoid
    // return ((1.0) / (1 + exp((-1) * demo)));
    return tanh(demo);
}

void feed_forward()
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
    print_n_value();
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

long double error_nn()
{
    long double demo;
    // printf("the error is calculated by mse");
    // cin>>demo;
    for (int i = 0; i < neuron[n - 1].size(); i++)
    {
        demo = pow((neuron[n - 1][i] - actual_value[i]), 2);
        demo /= 2.0;
        error_neuron[n - 1][i] = demo;
    }
    demo = *max_element(error_neuron[n - 1].begin(), error_neuron[n - 1].end());
    return demo;
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

void cal_new_weight(long double alpha)
{
    long double demo = 0;
    // int alpha ;
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 0; j < neuron[i].size(); j++)
        {
            for (int k = 0; k < neuron[i - 1].size(); k++)
            {
                demo = error_neuron[i][j] * (neuron[i - 1][k] * dif_activation_fn(neuron[i][j]));
                // error_weight[i-1][j][k]=demo;
                // if ()
                weight[i - 1][j][k] -= (alpha * error_weight[i - 1][j][k]);
            }
        }
    }
    return;
}

void cal_new_baise_weight(long double alpha)
{
    long double demo;
    for (int i = 0; i < n - 1; i++)
    {
        demo = 0;
        for (int j = 0; j < neuron[i + 1].size(); j++)
        {
            demo = dif_activation_fn(neuron[i + 1][j]);
            demo = (error_neuron[i + 1][j]) * (demo);
            weight_b[i][j] -= alpha * demo;
        }
    }
    return;
}

void cal_error_neuron(long double alpha)
{

    long double demo = 0.0;
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 0; j < neuron[i - 1].size(); j++)
        {
            demo = 0;
            for (int k = 0; k < neuron[i].size(); k++)
            {
                demo += error_neuron[i][k] * (weight[i - 1][k][j] * dif_activation_fn(neuron[i][j]));
            }
            error_neuron[i - 1][j] = demo;
            neuron[i - 1][j] -= (alpha * demo);
        }
    }
    cout << "error of the neurons r calculated" << endl;
    // error_neuron[0].resize(neuron[0].size(),0);
    // print_error_n();
    cal_new_weight(alpha);
    cal_new_baise_weight(alpha);
    return;
}

void back_prop()
{
    long double demo, demo1;
    // long double alpha;
    // long double alpha_rate;
    // printf("input the initial learning rate that you what to train your neuron and weights with\n");
    // cin >> alpha;
    // printf("the rate at which you want to decrease alpha is\n");
    // cin>>alpha_rate;
    demo = 0;
    demo1 = 0;
    long long int t = 0;
    long double demoi;
    demoi = alpha;
    while (1)
    {
        // printf("hey !!!!\n");
        feed_forward();
        demo = error_nn();
        // cost_fn();
        // printf("return to back_prop\n");
        if (demo == demo1)
        {
            alpha -= (alpha_rate * alpha);
            // pause(1);
            cout << "alpha" << alpha << endl
                 << endl
                 << endl;
        }
        // else if (demo>demo1)
        // {
        //     printf("\n8\n*\n*\n*\n*\n*\n*\n");
        // }
        // else if (demo > demo1)
        // {
        //     alpha += (alpha_rate * alpha);
        //     // }
        // }
            if (demo < max_error)
            {
                printf("this is the break\n");
                break;
            }
            // check the stoping condition here
            // for(int i=neuron.size()-1;i>=1;i--)
            // {
            //     // error_nn(neuron[i],,i);
            //     cal_error_neuron();
            // }
            cal_error_neuron(alpha);
            demo1 = demo;
            cout << "demo_error      " << demo << endl;
            t += 1;
            cout << t << endl;
        }
        alpha = demoi;
        return;
    }

    signed main(void)
    {

        cout << "hey, babuwolf, this is c005 and this is your hard coded neural network" << endl;
        topo();
        srand(time(0));
        weights();
        baised();
        printf("input the initial learning rate that you what to train your neuron and weights with\n");
        cin >> alpha;
        printf("the rate at which you want to decrease alpha is\n");
        cin >> alpha_rate;
        for (long double i = 0; i < 5; i += 0.0001)
        {
            // a=(long double)(rand()%5);
            // b=(long double)rand() / (RAND_MAX);
            input_layer(i);
            test_input(i);
            resize_error_neuron();
            resize_error_weight(error_weight);
            back_prop();
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    printf("*_*_");
                }
            }
            // printf("the best weight for the max_error = 1e-4 is \n");
            // print_w_values();
            // print_baise_weight();
            // cout<<endl<<endl;
            // print_n_value();
        }
        long double test;
        cout << "input the value for which you want to test the NN" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "the " << i << " input" << endl;
            cin >> test;
            input_layer(test);
            feed_forward();
            cout << neuron[n - 1][0];
            cout << sin(test);
        }
        // while(1)
        // {
        //     input_layer();
        //     printf("do u want to give test input enter 0");
        //     int c;
        //     cin>>c;
        //     if(c==0)
        //     {
        //     test_input();
        //     back_prop();
        //     }
        //     feed_forward();
        //     print_n_value();
        // }
        return 0;
    }

    // make a error vector for the weights for the backprop
    // i can have dynamic programming to store the value of the error or vactor
    // dynamic gradient step value alpha