cmake_minimum_required(VERSION 3.13)  # CMake version check
project(paya-programming-competition) # Create project "paya-programming-competition"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Set source variables for each question
set(QUESTION_1 question-1/main.cpp)
set(QUESTION_1_SIMPLE question-1/simple-version.cpp)
set(QUESTION_7 question-7/main.cpp)
set(QUESTION_2 question-2/main.cpp)
set(QUESTION_5 question-5/main.cpp)
set(QUESTION_10 question-10/main.cpp)
set(QUESTION_8 question-8/main.cpp)
set(QUESTION_3 question-3/main.cpp)
set(QUESTION_4 question-4/main.cpp)
set(QUESTION_11 question-11/main.cpp)
set(QUESTION_6 question-6/main.cpp)

# Add executable targets for each question's solution
add_executable(question-1 ${QUESTION_1})
add_executable(question-1-simple ${QUESTION_1_SIMPLE})
add_executable(question-2 ${QUESTION_2})
add_executable(question-7 ${QUESTION_7})
add_executable(question-5 ${QUESTION_5})
add_executable(question-10 ${QUESTION_10})
add_executable(question-8 ${QUESTION_8})
add_executable(question-3 ${QUESTION_3})
add_executable(question-4 ${QUESTION_4})
add_executable(question-11 ${QUESTION_11})
add_executable(question-6 ${QUESTION_11})

# Find packages
find_package(Threads REQUIRED)

# Link libraries
target_link_libraries(question-1 Threads::Threads)
target_link_libraries(question-1-simple Threads::Threads)
target_link_libraries(question-5 Threads::Threads)
