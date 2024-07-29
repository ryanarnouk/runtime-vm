#!/bin/bash

cd ./src/parse/
bison -d parser.y

cd ..
cd ./lexer
flex lexer.l
