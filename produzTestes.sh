#!/bin/bash

python src/adjacencia.py 1000 2000 100 99.95 > benchmarks/bench1.in
python src/adjacencia.py 4000 99.99 > benchmarks/bench2.in
