alias t := test
alias b := build

@test:
    just build && ./build/test

@build:
    python3 build.py

@clean:
    rm -rf build/*
