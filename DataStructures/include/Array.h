#pragma once

typedef struct {
	void* pArray;
	int allocatedSize;
	int nbElements;
} ggArray;

ggArray* ggArrayCreate(int size);
void ggArrayDestroy(ggArray*);

