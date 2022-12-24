<div align="center">
  <center><h1>ft_containers</h1></center>

## Goal of the project

Implementation of [Standard Template Library containers](https://cplusplus.com/reference/stl/) in C++98
</div>

## Containers
The following containers and their iterators are implemented:
* [Vector](https://en.cppreference.com/w/cpp/container/vector)
* [Map](https://en.cppreference.com/w/cpp/container/map)
* [Stack](https://en.cppreference.com/w/cpp/container/stack)

## Usage
```bash
$> make && ./ft_containers_tester
```

It will print the usage of the tester:

```bash
42Paris ft_containers
Usage: ./ft_container_tester [-vv | --verbose] [-t | --time] [-l | --logfile] [-d | --diff] [-vg | --valgrind] [-p | --pair] [-m | --map] [-s | --stack] [-v | --vector] [-a | --all]
GENERAL:
  -vv, --verbose: Print tests on stdout
  -t, --time: Print execution time
  -l, --logfile: Print tests into logs files
  -d, --diff: Print diff between ft::<container> tests and std::<container> tests
  -vg, --valgrind: Test memory leaks
AVAILABLE TESTS:
  -p, --pair: Pair tests
  -s, --stack: Stack tests
  -v, --vector: Vector tests
  -m, --map: Map tests
  -a, --all: All tests
EXAMPLES:
  ./ft_container_tester -vv -d -m
  ./ft_container_tester -vv -s
  ./ft_container_tester -vv -a -t -d -vg
```

We can as well use the subject's main, it will print ft_containers performance compared to std_containers:
```bash
$> time ./subject_ft 50; time ./subject_std 50
```