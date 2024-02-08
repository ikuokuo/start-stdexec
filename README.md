# Start stdexec

std::execution is the Senders model of asynchronous and parallel programming, proposed by [P2300](https://wg21.link/P2300).

The reference implementations:

- [NVIDIA/stdexec](https://github.com/NVIDIA/stdexec)
- [Meta/libunifex](https://github.com/facebookexperimental/libunifex)

## Build

Prepare,

- [CMake >= 3.14](https://cmake.org/download/)

Then,

```bash
# If on Ubuntu/Debian
sudo apt install -y build-essential cmake git

git clone --depth 1 https://github.com/ikuokuo/start-stdexec.git

cd start-stdexec/

# If want to avoid CPM re-downloading dependencies
export CPM_SOURCE_CACHE=$HOME/.cache/CPM

make
# make build TYPE=Debug
# make install
# make clean

./_build/stdexec_start
```

## Samples

- [stdexec_start.cc](samples/stdexec_start.cc): start your first stdexec program
- [taskflow_start.cc](samples/taskflow_start.cc): start your first taskflow program

## See also

Asynchronous Programming:

- [asio](https://think-async.com/Asio/index.html)

Parallel Task Programming:

- [taskflow](https://github.com/taskflow/taskflow): [documentation](https://taskflow.github.io/taskflow/index.html)
  - [Handbook](https://taskflow.github.io/taskflow/pages.html): [Cookbook](https://taskflow.github.io/taskflow/Cookbook.html), [Examples](https://taskflow.github.io/taskflow/Examples.html)
