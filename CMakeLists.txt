cmake_minimum_required(VERSION 3.14.0)
project(
    fortran-vector
    LANGUAGES Fortran
)

set(FVERSION "-std=gnu")

set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${FVERSION}")

enable_language(Fortran)

include(GNUInstallDirs)

set(SOURCES     ${SOURCE_DIR}/src/vector.f90
                ${SOURCE_DIR}/src/concurrent_vec.f90
                ${SOURCE_DIR}/src/fortran_vector_bindings.f90
                ${SOURCE_DIR}/src/fortran_vector.c
                ${SOURCE_DIR}/src/vector.f90
)

set(FIFO_SRC    ${SOURCE_DIR}/libs/for_fifo_queue/src/fifo_queue_bindings.f90
                ${SOURCE_DIR}/libs/for_fifo_queue/src/fifo_queue.c
                ${SOURCE_DIR}/libs/for_fifo_queue/src/fifo_queue.f90
)

set(THREAD_SRC  ${SOURCE_DIR}/libs/forthread/src/queues/thread_linked_fifo_queue.f90
                ${SOURCE_DIR}/libs/forthread/src/thread_bindings.f90
                ${SOURCE_DIR}/libs/forthread/src/thread_mutex.f90
                ${SOURCE_DIR}/libs/forthread/src/thread_types.f90
                ${SOURCE_DIR}/libs/forthread/src/thread.f90
                ${SOURCE_DIR}/libs/forthread/src/for_p_thread.c
                ${SOURCE_DIR}/libs/forthread/src/no_std_conv.f90

)


add_library(for_fifo_queue SHARED ${FIFO_SRC})

add_library(forthread SHARED ${THREAD_SRC})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    for_fifo_queue
    forthread
)