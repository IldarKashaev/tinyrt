#ifndef TINYRT_UTIL_H_
#define TINYRT_UTIL_H_

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "nlohmann/json.hpp"
#include "tinyrt/common.h"

namespace tinyrt {

TINYRT_INLINE auto SafeLoad(const std::string& filename)
    -> std::unordered_map<std::string, std::vector<float>> {
  std::unordered_map<std::string, std::vector<float>> weights_map;

  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cout << "Unable to open file: " << filename << std::endl;
    return weights_map;
  }

  // Read JSON length
  int64_t json_len;
  file.read(reinterpret_cast<char*>(&json_len), sizeof(json_len));

  // Read JSON
  std::vector<char> json_buffer(json_len);
  file.read(json_buffer.data(), json_len);
  auto json = nlohmann::json::parse(json_buffer.begin(), json_buffer.end());

  for (auto& element : json.items()) {
    if (element.key() == "__metadata__") continue;
    // TODO: Unused
    auto dtype_str = element.value()["dtype"].get<std::string>();
    std::vector<int> data_offsets =
        element.value()["data_offsets"].get<std::vector<int>>();
    size_t sz = static_cast<size_t>((data_offsets[1] - data_offsets[0]) /
                                    sizeof(float));

    file.seekg(8 + json_len + data_offsets[0], std::ios::beg);
    std::vector<float> weight(sz);
    file.read(reinterpret_cast<char*>(weight.data()), sz * sizeof(float));

    weights_map[element.key()] = std::move(weight);
  }

  return weights_map;
}

}  // namespace tinyrt

#endif  // TINYRT_UTIL_H_
