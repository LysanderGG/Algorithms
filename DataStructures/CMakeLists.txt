include_directories(
	../Common/include/
	include/
)

set (HEADER_FILES
	../Common/include/gg.h
	include/Array.h
	include/BST.h
	include/HashTable.h
	include/List.h
)

set (SOURCE_FILES
	src/Array.c
	src/BST.c
	src/HashTable.c
	src/List.c
)

add_library(DataStructures 
	${HEADER_FILES}
	${SOURCE_FILES})