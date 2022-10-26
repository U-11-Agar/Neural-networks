#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
using namespace std;

#define max_error 4.9406564584124654e-324 // #define a()

int n;
vector<vector<long double>> neuron;
vector<vector<vector<long double>>> weight;
vector<vector<long double>> weight_b;
vector<long double> actual_value;
vector<vector<long double>> error_neuron;
vector<vector<long double>> weight_rnn;
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

void weight_rnn_(void)
{
    int demo_4=neuron.size();

    weight_rnn.resize(demo_4-1);
    for(int i=1;i<neuron.size();i++)
{
    weight_rnn[i-1].resize(neuron[i].size(),0);

}
for (int i=0;i<weight_rnn.size();i++)
{
    for (int j=0;j<weight_rnn[i].size();j++)
    {
        if (j%2==0)
        {
            weight_rnn[i][j]=(long double)rand()/RAND_MAX;
        }
        else
        {
            weight_rnn[i][j]=((long double)(rand()%10)+1);
        }
    }
}
return ;
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
    cout << "how many layer you want(inlcuding the input layer)" << endl;
    cin >> n;
    vector<int> net(n, 0);
    printf("enter the no of neuron in the first layer\n");
    int temp;
    cin >> temp;
    net[0] = temp;
    printf("enter the no of neuron in the last layer\n");
    cin >> temp;
    net[n - 1] = temp;
    for (int i = 1; i < n - 1; i++)
    {
        net[i] = rand() % 10 + 1;
    }
    cout << "the structure of the neural network generated ramdomly is " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << net[i] << "-"; // << endl;
    }
    cout << endl;
    neuron_(net);
    return;
}

void input_layer(long double a)
{
    cout << "input the input layer vector are" << endl;
    for (int i = 0; i < neuron[0].size(); i++)
    {
        neuron[0][i] = sin(a);
        cout << neuron[0][i] << endl;
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
            for (int k = 0; k < weight[i][j].size(); k++)
            {
                printf("the value of the weights for the %d neurons in the layer %d to the %d neuron of the layer %d\n", k + 1, i + 1, j + 1, i + 2);
                cout << weight[i][j][k] << endl;
            }
        }
    }
    return;
}

void weights()
{
    resize_error_weight(weight);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < weight[i].size(); j++)
        {
            for (int k = 0; k < weight[i][j].size(); k++)
            {
                if (k % 2 == 0)
                {
                    weight[i][j][k] = (long double)(rand() % 10 + 1);
                }
                else
                {
                    weight[i][j][k] = ((long double)rand() / (RAND_MAX));
                }
            }
        }
    }
    print_w_values();
    return;
}

void print_baise_weight()
{
    for (int i = 0; i < n - 1; i++)
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
    weight_b.resize(n);
    for (int i = 0; i < n - 1; i++)
    {
        weight_b[i].resize(neuron[i + 1].size(), 0);
    }
    for (int i = 0; i < n - 1; i++)
    {

        for (int j = 0; j < weight_b[i].size(); j++)
        {
            if (j % 2 == 0)
            {
                weight_b[i][j] = ((long double)(rand() % 10 + 1));
            }
            else
            {
                weight_b[i][j] = ((long double)rand() / (RAND_MAX));
            }
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
        actual_value[i] = sin(a + 0.0001);
    }

    print_actual();
    return;
}

long double activation_fn(long double demo)
{
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
    return;
}
void forward()
{
    long double demo = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < neuron[i + 1].size(); j++)
        {
            for (int k = 0; k < neuron[i].size(); k++)
            {  
                demo=neuron[i + 1][j];
            demo += weight_b[i][j];
                demo += neuron[i][k] * weight[i][j][k];
            }
            demo = activation_fn(demo);
            neuron[i + 1][j] = demo;
        }
        demo = 0.0;
    }
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
    long double temp;
    for (int i = 0; i < neuron[n - 1].size(); i++)
    {
        demo = pow((neuron[n - 1][i] - actual_value[i]), 2);
        demo /= 2.0;
        temp = actual_value[i] - neuron[n - 1][i];
        error_neuron[n - 1][i] = temp;
    }
    // demo = *max_element(error_neuron[n - 1].begin(), error_neuron[n - 1].end());
    return demo;
}

long double dif_activation_fn(long double n_value)
{

    long double demo;
    demo = (1 - pow(n_value, 2));

    return demo;
}

void cal_new_weight_rnn_(void)
{
    long double demo=0;
    for (int i=0; i<weight_rnn.size();i++)
    {
        for (int j=0;j<weight_rnn[i].size();j++)
        {
            demo
        }
    }
}

void cal_new_weight()
{
    long double demo = 0;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 0; j < neuron[i + 1].size(); j++)
        {
            for (int k = 0; k < neuron[i].size(); k++)
            {
                demo = error_neuron[i + 1][j] * (neuron[i][k] * dif_activation_fn(neuron[i + 1][j]));
                weight[i - 1][j][k] -= (alpha * demo);
            }
        }
    }
    return;
}

void cal_new_baise_weight()
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

void cal_error_neuron()
{

    long double demo = 0.0;
    for (int i = n - 1; i > 1; i--)
    {
        for (int j = 0; j < neuron[i - 1].size(); j++)
        {
            demo = 0;
            for (int k = 0; k < neuron[i].size(); k++)
            {
                demo += error_neuron[i][k] * (weight[i - 1][k][j] * dif_activation_fn(neuron[i][j]));
            }
            error_neuron[i - 1][j] = demo;
        }
    }
    cout << "error of the neurons r calculated" << endl;
    cal_new_weight();
    cal_new_baise_weight();
    return;
}

void back_prop()
{
    long double demo, demo1;
    demo = 0;
    demo1 = 0;
    long long int t = 0;
    long double demoi;
    demoi = alpha;
    while (1)
    {

        feed_forward();
        demo = error_nn();
        alpha_rate = ((long double)rand() / (RAND_MAX)) / 10000;
        if (demo == demo1)
        {
            alpha -= (alpha_rate * alpha);
            cout << endl
                 << "**********" << endl
                 << alpha << endl;
        }
        else if (demo > demo1)
        {
            printf("\n8\n*\n*\n*\n*\n*\n*\n");
            alpha += (alpha_rate * alpha);
            cout << "**********\n"
                 << alpha << endl;
        }
        demo1 = demo;
        cout << "demo_error" << demo << endl;
        t += 1;
        cout << t << endl;
        if (demo < max_error)
        {
            printf("this is the break\n");
            break;
        }
        cal_error_neuron();
    }
    alpha = demoi;
    return;
}

signed main(void)
{

    cout << "hey, babuwolf, this is c005 and this is your hard coded recursive neural (RNN) network" << endl;
    topo();
    srand(time(0));
    weights();
    baised();
    resize_error_neuron();
    printf("input the initial learning rate that you what to train your neuron and weights with\n");
    // cin >> alpha;
    // alpha = ((long double)rand() / (RAND_MAX));
    alpha = 0.637896000;
    cout << "the valus aplha is" << endl
         << alpha << endl;
    printf("the rate at which you want to decrease alpha is\n");
    // cin >> alpha_rate;
    alpha_rate = ((long double)rand() / (RAND_MAX)) / 10000;
    // alpha_rate = alpha / 10000;
    cout << "the valus aplha rate is" << endl
         << alpha_rate << endl;
    cout << "do you want to start (y/n)" << endl;
    char start;
    cin >> start;
    if (start == 'n' || start == 'N')
    {
        return 0;
    }
    else
    {
        for (long double i = 0; i <= acos(0.0); i += 0.001)
        {
            // a=(long double)(rand()%5);
            // b=(long double)rand() / (RAND_MAX);
            cout << i << endl;
            input_layer(i);
            test_input(i);
            // resize_error_weight(error_weight);
            back_prop();
            // for (int j = 0; j < 10; j++)
            // {
            for (int k = 0; k < 10; k++)
            {
                printf("*_*_");
                cout << endl;
            }
            // }
            // printf("the best weight for the max_error = 1e-4 is \n");
            // print_w_values();
            // print_baise_weight();
            // cout<<endl<<endl;
            // print_n_value();
        }
        long double test;
        cout << "input the value for which you want to test the NN" << endl;
        for (int i = 0; i < 1; i += 0.001)
        {
            // cout << "the " << i << " input" << endl;
            test_input((long double)acos(0.0) + i);
            input_layer((long double)acos(0.0) + i);
            feed_forward();
            cout << endl
                 << "the prdicted value is" << endl
                 << neuron[n - 1][0] << endl;
            cout << sin((long double)acos(0.0) + (2.0 * i)) << endl;
            back_prop();
            // cin >> test;
        }
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
