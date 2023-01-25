cmake_minimum_required(VERSION 3.24)
project(Neuronet)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

include(FindCurses)
include(FindLibArchive)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast  ")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(CURL REQUIRED)
find_package(Curses REQUIRED)
find_package(ZLIB REQUIRED)
find_package(BLAS REQUIRED)
find_package(spdlog REQUIRED)

# Dependencies
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)


# Assign the include directories
#include_directories(${Boost_INCLUDE_DIRS})


include_directories(${PROJECT_SOURCE_DIR} ${ZLIB_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS} ${LibArchive_INCLUDE_DIRS} ${BLAS_INCLUDE_DIR})
set(CURSES_LIBRARIES "/usr/lib/x86_64-linux-gnu/libncursesw.so;/usr/lib/x86_64-linux-gnu/libformw.so")

add_executable(Neuronet
        #        Neuronet
        profiling/time_profiling.h
        profiling/time_profiling.cpp
        mempool/counting_mem_allocator.h
        mempool/counting_mem_allocator.cpp
        global.cpp
        utils.cpp
        main.cpp
        #  mempool/DynamicMempool.cpp
        #  mempool/data/Chunk.cpp
        #  mempool/data/gzChunk.cpp
        #  mempool/data/Image.cpp
        #  threadpool/ThreadPool.cpp
        tools/FileDownloader.cpp
        tools/ArchiveDecompressor.cpp
        dataset_readers/MNISTReader.cpp
        utils/narray_util.cpp
        neural_network/Network.cpp
        narray/narray.cpp
        narray/narray_coord.cpp
        #  destinations/DummyDestintion.cpp
        #  destinations/ImageDestination.cpp
        #  pipes/Pipe.cpp
        #  pipes/FunctionalPipe.cpp
        #  pipes/FilePipe.cpp
        #  pipes/GzPipe.cpp
        #  sources/source.cpp
        #  sources/mnist/MNISTsource.cpp
        )
target_link_libraries(${PROJECT_NAME} spdlog::spdlog_header_only ${ZLIB_LIBRARIES} ${CURL_LIBRARIES} ${CURSES_LIBRARIES} ${LibArchive_LIBRARIES} ${BLAS_LIBRARIES})

#add_executable(test_exec test/main_test.cpp narray/narray.cpp)
# example library
add_library(narray profiling/time_profiling.h profiling/time_profiling.cpp
        mempool/counting_mem_allocator.h mempool/counting_mem_allocator.cpp utils/narray_util.cpp narray/narray_coord.cpp narray/narray.cpp
        )


# testing binary
add_executable(narray_test_int test/main_test.cpp)
target_link_libraries(narray_test_int PRIVATE narray ${CURSES_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_int
        COMMAND $<TARGET_FILE:narray_test_int>
)

add_executable(narray_test_float test/narray_test_float.cpp)
target_link_libraries(narray_test_float PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_float
        COMMAND $<TARGET_FILE:narray_test_float>
)

add_executable(narray_test_transpose test/narray_test_transpose.cpp)
target_link_libraries(narray_test_transpose PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_transpose
        COMMAND $<TARGET_FILE:narray_test_transpose>
)

add_executable(char_to_double_conversion test/char_to_double_conversion.cpp)
target_link_libraries(char_to_double_conversion PRIVATE narray  spdlog::spdlog_header_only  ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME char_to_double_conversion
        COMMAND $<TARGET_FILE:char_to_double_conversion>
)

add_executable(narray_test_update_weight test/narray_test_update_weight.cpp)
target_link_libraries(narray_test_update_weight PRIVATE narray  spdlog::spdlog_header_only  ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_update_weight
        COMMAND $<TARGET_FILE:narray_test_update_weight>
)

add_executable(narray_test_iterator test/narray_test_iterator.cpp)
target_link_libraries(narray_test_iterator PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_iterator
        COMMAND $<TARGET_FILE:narray_test_iterator>
)


add_executable(narray_test_bracket_operator test/narray_test_bracket_operator.cpp)
target_link_libraries(narray_test_bracket_operator PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_bracket_operator
        COMMAND $<TARGET_FILE:narray_test_bracket_operator>
)

add_executable(narray_test_dot_product math/math.h test/narray_test_dot_product.cpp)
target_link_libraries(narray_test_dot_product PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product
        COMMAND $<TARGET_FILE:narray_test_dot_product>
)

add_executable(narray_test_fill_predefined_values test/narray_test_fill_predefined_values.cpp)
target_link_libraries(narray_test_fill_predefined_values PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_fill_predefined_values
        COMMAND $<TARGET_FILE:narray_test_fill_predefined_values>
)

add_executable(narray_test_minus_assign test/narray_test_minus_assign.cpp)
target_link_libraries(narray_test_minus_assign PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_minus_assign
        COMMAND $<TARGET_FILE:narray_test_minus_assign>
)

add_executable(narray_test_fill_predefined_values_1 test/narray_test_fill_predefined_values_1.cpp)
target_link_libraries(narray_test_fill_predefined_values_1 PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_fill_predefined_values_1
        COMMAND $<TARGET_FILE:narray_test_fill_predefined_values_1>
)

add_executable(narray_zip_test utils/zip_iterator.h utils/zipper.h test/narray_zip_test.cpp)
target_link_libraries(narray_zip_test PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_zip_test
        COMMAND $<TARGET_FILE:narray_zip_test>
)


add_executable(narray_transform_test math/math.h test/narray_transform_function.cpp)
target_link_libraries(narray_transform_test PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_transform_test
        COMMAND $<TARGET_FILE:narray_transform_test>
)


add_executable(char_sigmoid_test math/math.h test/char_sigmoid_test.cpp)
target_link_libraries(char_sigmoid_test PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME char_sigmoid_test
        COMMAND $<TARGET_FILE:char_sigmoid_test>
)

add_executable(float_sigmoid_test math/math.h test/float_sigmoid_test.cpp)
target_link_libraries(float_sigmoid_test PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME float_sigmoid_test
        COMMAND $<TARGET_FILE:char_sigmoid_test>
)


add_executable(narray_weight_test math/math.h test/narray_weight_test.cpp)
target_link_libraries(narray_weight_test PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_weight_test
        COMMAND $<TARGET_FILE:narray_weight_test>
)

add_executable(copy_constructor_test test/copy_constructor_test.cpp)
target_link_libraries(copy_constructor_test PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME copy_constructor_test
        COMMAND $<TARGET_FILE:copy_constructor_test>
)

add_executable(narray_test_dot_product_1 math/math.h test/narray_test_dot_product_1.cpp)
target_link_libraries(narray_test_dot_product_1 PRIVATE narray  ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product_1
        COMMAND $<TARGET_FILE:narray_test_dot_product_1>
)
add_executable(narray_test_dot_product_1_1 math/math.h test/narray_test_dot_product_1_1.cpp)
target_link_libraries(narray_test_dot_product_1_1 PRIVATE narray  ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product_1_1
        COMMAND $<TARGET_FILE:narray_test_dot_product_1_1>
)


add_executable(narray_test_blas math/math.h test/narray_test_blas.cpp)
target_link_libraries(narray_test_blas PRIVATE narray  ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_blas
        COMMAND $<TARGET_FILE:narray_test_blas>
)

add_executable(narray_test_dot_product_2 math/math.h test/narray_test_dot_product_2.cpp)
target_link_libraries(narray_test_dot_product_2 PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product_2
        COMMAND $<TARGET_FILE:narray_test_dot_product_2>
)

add_executable(narray_test_dot_product_3 math/math.h test/narray_test_dot_product_3.cpp)
target_link_libraries(narray_test_dot_product_3 PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product_3
        COMMAND $<TARGET_FILE:narray_test_dot_product_3>
)


add_executable(narray_test_dot_product_4 math/math.h test/narray_test_dot_product_4.cpp)
target_link_libraries(narray_test_dot_product_4 PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product_4
        COMMAND $<TARGET_FILE:narray_test_dot_product_4>
)

add_executable(neuronet_test_train global.cpp utils.cpp dataset_readers/MNISTReader.cpp neural_network/Network.cpp test/neuronet_test_train.cpp)
target_link_libraries(neuronet_test_train PRIVATE narray spdlog::spdlog_header_only ${CURSES_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME neuronet_test_train
        COMMAND $<TARGET_FILE:neuronet_test_train>
)

add_executable(neuronet_test_train_1 global.cpp utils.cpp dataset_readers/MNISTReader.cpp neural_network/Network.cpp test/neuronet_test_train_1.cpp)
target_link_libraries(neuronet_test_train_1 PRIVATE narray spdlog::spdlog_header_only ${CURSES_LIBRARIES} ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME neuronet_test_train_1
        COMMAND $<TARGET_FILE:neuronet_test_train_1>
)

add_executable(neuronet_test_train_2 global.cpp utils.cpp dataset_readers/MNISTReader.cpp neural_network/Network.cpp test/neuronet_test_train_2.cpp)
target_link_libraries(neuronet_test_train_2 PRIVATE narray spdlog::spdlog_header_only ${CURSES_LIBRARIES} ${BLAS_LIBRARIES})

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME neuronet_test_train_2
        COMMAND $<TARGET_FILE:neuronet_test_train_2>
)


add_executable(narray_test_zip_different_sizes utils/zip_iterator.h utils/zipper.h test/narray_test_zip_different_sizes.cpp)
target_link_libraries(narray_test_zip_different_sizes PRIVATE narray)
# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_zip_different_sizes
        COMMAND $<TARGET_FILE:narray_test_zip_different_sizes>
)


add_executable(narray_test_matmul math/math.h global.cpp utils/zip_iterator.h utils/zipper.h test/narray_test_matmul.cpp)
target_link_libraries(narray_test_matmul PRIVATE narray spdlog::spdlog_header_only ${BLAS_LIBRARIES})
# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_matmul
        COMMAND $<TARGET_FILE:narray_test_matmul>
)

add_executable(narray_test_matsum math/math.h global.cpp utils/zip_iterator.h utils/zipper.h test/narray_test_matsum.cpp)
target_link_libraries(narray_test_matsum PRIVATE narray spdlog::spdlog_header_only ${BLAS_LIBRARIES})
# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_matsum
        COMMAND $<TARGET_FILE:narray_test_matsum>
)

add_executable(narray_test_maxarg math/math.h global.cpp utils/zip_iterator.h utils/zipper.h test/narray_test_maxarg.cpp)
target_link_libraries(narray_test_maxarg PRIVATE narray spdlog::spdlog_header_only ${BLAS_LIBRARIES})
# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_maxarg
        COMMAND $<TARGET_FILE:narray_test_maxarg>
)

add_executable(narray_test_maxarg_1 math/math.h global.cpp utils/zip_iterator.h utils/zipper.h test/narray_test_maxarg_1.cpp)
target_link_libraries(narray_test_maxarg_1 PRIVATE narray spdlog::spdlog_header_only ${BLAS_LIBRARIES})
# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_maxarg_1
        COMMAND $<TARGET_FILE:narray_test_maxarg_1>
)

add_executable(narray_feedforward_test math/math.h global.cpp utils/zip_iterator.h utils/zipper.h test/narray_feedforward_test.cpp)
target_link_libraries(narray_feedforward_test PRIVATE narray spdlog::spdlog_header_only ${BLAS_LIBRARIES})
# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_feedforward_test
        COMMAND $<TARGET_FILE:narray_feedforward_test>
)




add_executable(narray_test_dot_product_5 math/math.h test/narray_test_dot_product_5.cpp)
target_link_libraries(narray_test_dot_product_5 PRIVATE narray)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_dot_product_5
        COMMAND $<TARGET_FILE:narray_test_dot_product_5>
)

add_executable(narray_test_mempool global.cpp test/narray_test_mempool.cpp)
target_link_libraries(narray_test_mempool PRIVATE narray spdlog::spdlog_header_only)

# enable testing functionality
enable_testing()

# define tests
add_test(
        NAME narray_test_mempool
        COMMAND $<TARGET_FILE:narray_test_mempool>
)
