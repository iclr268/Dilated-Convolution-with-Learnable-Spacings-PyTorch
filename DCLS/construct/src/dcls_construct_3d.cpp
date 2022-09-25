#include <torch/extension.h>

#include <iostream>

#include <vector>

// CUDA forward declarations

torch::Tensor dcls_construct_3d_cuda_forward(   
    torch::Tensor weight,
    torch::Tensor P1,
    torch::Tensor P2,
    torch::Tensor P3,    
    const int dilated_kernel_size_d, const int dilated_kernel_size_h, const int dilated_kernel_size_w,
    const float scaling
    ); 

std::vector<torch::Tensor> dcls_construct_3d_cuda_backward(   
    torch::Tensor weight,
    torch::Tensor P1,
    torch::Tensor P2,
    torch::Tensor P3,    
    torch::Tensor grad_output,      
    const int dilated_kernel_size_d, const int dilated_kernel_size_h, const int dilated_kernel_size_w,
    const float scaling
    ); 
    
// C++ interface

#define CHECK_CUDA(x) TORCH_CHECK(x.type().is_cuda(), #x " must be a CUDA tensor")
#define CHECK_CONTIGUOUS(x) TORCH_CHECK(x.is_contiguous(), #x " must be contiguous")
#define CHECK_INPUT(x) CHECK_CUDA(x); CHECK_CONTIGUOUS(x)

torch::Tensor dcls_construct_3d_forward(   
    torch::Tensor weight,
    torch::Tensor P1,
    torch::Tensor P2,
    torch::Tensor P3,
    const int dilated_kernel_size_d, const int dilated_kernel_size_h, const int dilated_kernel_size_w,
    const float scaling
    ) {
  
    CHECK_INPUT(weight);
    CHECK_INPUT(P1);
    CHECK_INPUT(P2);
    CHECK_INPUT(P3);    


    return dcls_construct_3d_cuda_forward(
                              weight, 
                              P1,
                              P2,
                              P3,                              
                              dilated_kernel_size_d,
                              dilated_kernel_size_h,
                              dilated_kernel_size_w,
                              scaling                              
                              ); 
}

std::vector<torch::Tensor> dcls_construct_3d_backward(   
    torch::Tensor weight,
    torch::Tensor P1,
    torch::Tensor P2,
    torch::Tensor P3,
    torch::Tensor grad_output,      
    const int dilated_kernel_size_d, const int dilated_kernel_size_h, const int dilated_kernel_size_w,
    const float scaling
    ) {
      
    CHECK_INPUT(weight);
    CHECK_INPUT(P1);
    CHECK_INPUT(P2);
    CHECK_INPUT(P3);
    CHECK_INPUT(grad_output);    

    return dcls_construct_3d_cuda_backward( 
                              weight, 
                              P1,
                              P2,
                              P3,
                              grad_output,
                              dilated_kernel_size_d,
                              dilated_kernel_size_h,
                              dilated_kernel_size_w,
                              scaling 
                              ); 
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("forward", &dcls_construct_3d_forward, "DCLS3d forward (CUDA)");
  m.def("backward", &dcls_construct_3d_backward, "DCLS3d backward (CUDA)");
}