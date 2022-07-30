cmake_minimum_required(VERSION 3.13)  # CMake version check
project(paya-programming-competition) # Create project "paya-programming-competition"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Set source variables for each question
set(QUESTION_1 question-1/main.cpp)
set(QUESTION_7 question-7/main.cpp)

# Add executable targets for each question's solution
add_executable(question-1 ${QUESTION_1})
add_executable(question-7 ${QUESTION_7})
