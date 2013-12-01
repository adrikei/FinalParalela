#!/bin/bash


for i in {1..8}
do
	python src/adjacencia.py $(($i+$i))000 99.9999 > benchmarks/bench$i.in
done
