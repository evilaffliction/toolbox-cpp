// The Reactive C++ Toolbox.
// Copyright (C) 2022 Reactive Markets Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TOOLBOX_BM_CONTEXT
#define TOOLBOX_BM_CONTEXT

#include <toolbox/bm/Range.hpp>
#include <toolbox/util/Alarm.hpp>

namespace toolbox::bm {

class TOOLBOX_API Context {
  public:
    explicit Context(Histogram& hist)
    : hist_{hist}
    {
    }
    ~Context();

    // Copy.
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    // Move.
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;

    explicit operator bool() const noexcept { return !stop_; }
    BenchmarkRange range(int first, int last) const noexcept { return {hist_, first, last}; }
    BenchmarkRange range(int count) const noexcept { return {hist_, 0, count}; }

    void stop() noexcept { stop_ = true; }

  private:
    Histogram& hist_;
    std::atomic_bool stop_{false};
};

} // namespace toolbox::bm

#endif // TOOLBOX_BM_CONTEXT
