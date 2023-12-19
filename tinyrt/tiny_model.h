#ifndef TINYRT_TINY_MODEL_H_
#define TINYRT_TINY_MODEL_H_

#include <string>
#include <vector>

#include "CL/opencl.hpp"
#include "nlohmann/json.hpp"

namespace tinyrt {

class TinyModel {
 public:
  TinyModel(const std::string& weights_file, const std::string& arch_file,
            cl::Context* context, cl::CommandQueue* command_queue);

  ~TinyModel() = default;

  void SetInputs(const std::vector<void*>& inputs);

  void Inference();

  void GetOutputs(std::vector<void*>& outputs);

  const std::string& backend() { return backend_; }

  const std::vector<nlohmann::json>& inputs() { return inputs_; }

  const std::size_t NumInputs() { return inputs_.size(); }

  const std::size_t NumOutputs() { return outputs_.size(); }

 private:
  std::vector<nlohmann::json> statements_;
  std::string backend_;
  std::vector<nlohmann::json> inputs_;
  std::vector<nlohmann::json> outputs_;
  cl::Device device_;
  std::shared_ptr<cl::Context> context_ = nullptr;
  std::shared_ptr<cl::CommandQueue> command_queue_ = nullptr;
  std::unique_ptr<cl::Program> program_ = nullptr;
  std::unordered_map<std::string, cl::Buffer> buffers_;
  std::vector<void*> output_buffers_;
};

}  // namespace tinyrt

#endif  // TINYRT_TINY_MODEL_H_
