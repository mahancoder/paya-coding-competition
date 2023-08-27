# Paya Computer Science Competition
Answers for Paya League Comp Sci final round (1400 - 1401)

## Usage
First, build the apps from source, and then run your desired executable in a question's directory.

## Building from source
To build from source, run build.sh:
```
./build.sh
```

## Answers
To view the presentation online, visit [this](https://mahancoder.github.io/paya-coding-competition/presentation/html/) page.

## File structure
You can find competition's questions PDF source in **exam-questions.pdf**

Every question-x folder contains a full answer with separate main functions, along with binaries to its question. **build.sh** compiles all apps (answers) into separate executables using CMake configurations in CMakeLists.txt and then copies all of them into their own directory (e.g. question 1's binary located in /build will be copied to ../question-1, or simply It's subdirectory's question-1 directory)

## Results
We got the #1 rank in the entire country :)
