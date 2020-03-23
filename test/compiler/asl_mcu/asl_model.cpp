#include "operators/Constant.h"
#include "operators/Reshape.h"
#include "operators/Gemm.h"
#include "operators/Relu.h"
#include "operators/LogSoftmax.h"


using namespace dnnc;


void usage(char** args) {
  std::cout << "\nUsage: " << args[0] <<
    " <datafile for input \"0\">" <<
    "\n\n";

  std::cout << "This model has " << 1 << " input(s):\n";
  std::cout << "\t 1. \"0\" (shape 714):\n";

  std::cout << "Output(s) will be written in file(s):\n";
  std::cout << "\t 1. \"11.out\" (shape 1, 2):\n";
}

int main(int argc, char** argv) {

#define BUNDLE_DIR std::string(argv[0]).substr(0,\
                      std::string(argv[0]).find_last_of("/")) + "/"

  if ( argc < 2 || std::string(argv[1]).substr(0,2) == "-h" ) {
    usage(argv);
    return 1;
  }

  tensor<float> dnnc_0({714});
  dnnc_0.read(argv[1]);
  tensor<float> dnnc_fc1_dot_weight({16, 714});
  dnnc_fc1_dot_weight.read(BUNDLE_DIR + "fc1.weight");
  tensor<float> dnnc_fc1_dot_bias({16});
  dnnc_fc1_dot_bias.read(BUNDLE_DIR + "fc1.bias");
  tensor<float> dnnc_fc2_dot_weight({2, 16});
  dnnc_fc2_dot_weight.read(BUNDLE_DIR + "fc2.weight");
  tensor<float> dnnc_fc2_dot_bias({2});
  dnnc_fc2_dot_bias.read(BUNDLE_DIR + "fc2.bias");

  Constant<int64_t> dnnc___1("dnnc___1");
  std::vector<int64_t> dnnc___1_value_vec = {-1,714};
  tensor<int64_t> dnnc___1_value({2}); dnnc___1_value.load(dnnc___1_value_vec);
  dnnc___1.setAttribute ( attr_value, dnnc___1_value );
  tensor<int64_t> dnnc_dnnc___1_5 = dnnc___1.compute ();


  Reshape<float, float, int64_t> dnnc___2("dnnc___2");
  tensor<float> dnnc_dnnc___2_6 = dnnc___2.compute ( dnnc_0, dnnc_dnnc___1_5);


  Gemm<float, float, float> dnnc___3("dnnc___3");
  float dnnc___3_alpha = 1.000000 ;
  dnnc___3.setAttribute ( attr_alpha, dnnc___3_alpha );
  float dnnc___3_beta = 1.000000 ;
  dnnc___3.setAttribute ( attr_beta, dnnc___3_beta );
  int32_t dnnc___3_transB = 1 ;
  dnnc___3.setAttribute ( attr_transB, dnnc___3_transB );
  tensor<float> dnnc_dnnc___3_7 = dnnc___3.compute ( dnnc_dnnc___2_6, dnnc_fc1_dot_weight, dnnc_fc1_dot_bias);


  Relu<float, float> dnnc___4("dnnc___4");
  tensor<float> dnnc_dnnc___4_8 = dnnc___4.compute ( dnnc_dnnc___3_7);


  Gemm<float, float, float> dnnc___5("dnnc___5");
  float dnnc___5_alpha = 1.000000 ;
  dnnc___5.setAttribute ( attr_alpha, dnnc___5_alpha );
  float dnnc___5_beta = 1.000000 ;
  dnnc___5.setAttribute ( attr_beta, dnnc___5_beta );
  int32_t dnnc___5_transB = 1 ;
  dnnc___5.setAttribute ( attr_transB, dnnc___5_transB );
  tensor<float> dnnc_dnnc___5_9 = dnnc___5.compute ( dnnc_dnnc___4_8, dnnc_fc2_dot_weight, dnnc_fc2_dot_bias);


  Relu<float, float> dnnc___6("dnnc___6");
  tensor<float> dnnc_dnnc___6_10 = dnnc___6.compute ( dnnc_dnnc___5_9);


  LogSoftmax<float, float> dnnc___7("dnnc___7");
  int32_t dnnc___7_axis = 1 ;
  dnnc___7.setAttribute ( attr_axis, dnnc___7_axis );
  tensor<float> dnnc_dnnc___7_11 = dnnc___7.compute ( dnnc_dnnc___6_10);

  // Write the output tensor in a file.
  dnnc_dnnc___7_11.write("11.out");


  return 0;
}

