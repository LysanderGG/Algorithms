include_directories(
	../Common/include/
	../Algorithms/include/
	../DataStructures/include/
	../ext/googletest/include/
)

link_directories(${PROJECT_SOURCE_DIR}/ext/googletest/lib)

add_executable(UnitTests 
	src/ArrayTest.cpp
	src/BSTTest.cpp
	src/BinarySearchTest.cpp
	src/HashTableTest.cpp
	src/ListTest.cpp
	src/main.cpp
)

target_link_libraries(UnitTests Algorithms DataStructures gtestd)

