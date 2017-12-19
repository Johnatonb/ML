#include <cstdarg>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>

// std::mt19937 rng;

std::uniform_real_distribution<> d(-1,1);
std::mt19937 gen;


class node{
  public:
    double internal_value;
    std::vector<double> internal_weights;

    node(double proposed){
      internal_value = proposed;
    }

    operator double(){
      return internal_value;
    }

    double operator=(double rhs){
      internal_value = rhs;
    }

    double &operator[](int rhs){
      return internal_weights[rhs];
    };

    void size(int value){

      for(int i = 0; i < value; i++){
        internal_weights.push_back(d(gen));
        // std::cout<<d(gen)<<std::endl;
      }
    }

    int size(){
      return internal_weights.size();
    }
};

double softsign(double input){
  return input/(1+abs(input));
}



class layer{
  public:
    std::vector<node> node_layer;

    double size(){
      return node_layer.size();
    }

    layer(const int& count){
      for(int i = 0; i < count; i++){
        node_layer.push_back(node(0.0));
      }
    }

    node &operator[](const int& rhs){
      return node_layer[rhs];
    };
};

class netwerk{
  public:
    std::vector<layer> network;

    int size(){
      return network.size();
    }

    netwerk(const int& count,...){
      va_list args;
      va_start(args, count);
      for(int i = 0; i < count; i++){
        network.push_back(va_arg(args,layer));
      }
      for(int i = 0; i < network.size() - 1; ++i){
        for(int j = 0; j < network[i].size(); j++){
          // std::cout<<network[]<<std::endl;
          network[i][j].size(network[i+1].size());
        }
      }
    }

    layer &operator[](const int& rhs){
      return network[rhs];
    };

    void feed_forward(){
      double temp = 0;
      // std::cout<<network.size()<<std::endl;
      for(int i = 0; i < network.size() -1; i++){
        for(int j = 0; j < network[i+1].size(); j++){
          // std::cout<<i+1<<","<<network[i+1].size()<<std::endl;
          for(int k = 0; k < network[i].size(); k++){
            temp += network[i][k] * network[i][k][j];
            // std::cout<<"["<<i<<"]["<<k<<"] * ["<<i<<"]["<<k<<"]["<<j<<"]"<<std::endl;
            // std::cout<<network[i][k]<< " * " <<network[i][k][j]<<std::endl;
            // std::cout<<"temp :"<<temp<<std::endl;
          }
          network[i+1][j] = tanh(temp);
          // std::cout<<network[i+1][j]<<std::endl;
          temp = 0;
        }
        // node = temp
      }
    }
};

int main(){
  // layer outputs(5);
  netwerk baz(4,layer(786),layer(16),layer(16),layer(10));
  for(int i = 0; i < baz[0].size(); i++){
    baz[0][i] = 1;
    // std::cout<<baz[3][i]<<std::endl;
  }
  baz.feed_forward();
  // for(int i = 0; i < baz[3].size(); i++){
  //   // baz[0][i] = 1;
  //   std::cout<<baz[3][i]<<std::endl;
  // }
}
