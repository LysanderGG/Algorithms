include_directories(
	../Common/include/
	include/
)

set (HEADER_FILES
	../Common/include/gg.h
	include/BinarySearch.h
)

set (SOURCE_FILES
	src/BinarySearch.c
)

add_library(Algorithms 
	${HEADER_FILES}
	${SOURCE_FILES})