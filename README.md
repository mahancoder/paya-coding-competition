# Paya Computer Science Competition
Answers for Paya League Comp Sci final round

## Usage
First, build the apps from source, and then run your desired executable in /build directory.

## Building from source
To build from source, run build.sh:
```
./build.sh
```

## File structure
Every question-x folder contains a full app with separate main functions, along with It's binary. **build.sh** compiles all apps into separate executables using CMake configurations in CMakeLists.txt and then copies all of them into their own directory (e.g. question 1's binary located in /build will be copied to ../question-1, or simply It's subdirectory's question-1 directory)