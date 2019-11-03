#include "pch.h"

#include <kinc/graphics4/graphics.h>
#include <kinc/graphics4/indexbuffer.h>

#include <Kore/SystemMicrosoft.h>

#include "Direct3D9.h"

struct kinc_g4_index_buffer *kinc_internal_current_index_buffer = NULL;

void kinc_g4_index_buffer_init(kinc_g4_index_buffer_t *buffer, int count) {
	buffer->impl.myCount = count;
	DWORD usage = 0;
#ifdef KORE_WINDOWS
	usage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
#endif
	kinc_microsoft_affirm(device->CreateIndexBuffer(sizeof(int) * count, usage, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &buffer->impl.ib, 0));
}

void kinc_g4_index_buffer_destroy(kinc_g4_index_buffer_t *buffer) {
	buffer->impl.ib->Release();
}

int *kinc_g4_index_buffer_lock(kinc_g4_index_buffer_t *buffer) {
	int *ints;
	DWORD lockflags = 0;
#ifdef KORE_WINDOWS
	lockflags = D3DLOCK_DISCARD;
#endif
	int count2 = kinc_g4_index_buffer_count(buffer);
	kinc_microsoft_affirm(buffer->impl.ib->Lock(0, count2 * 4, (void **)&ints, lockflags));
	return ints;
}

void kinc_g4_index_buffer_unlock(kinc_g4_index_buffer_t *buffer) {
	kinc_microsoft_affirm(buffer->impl.ib->Unlock());
}

void kinc_internal_g4_index_buffer_set(kinc_g4_index_buffer_t *buffer) {
	kinc_internal_current_index_buffer = buffer;
	kinc_microsoft_affirm(device->SetIndices(buffer->impl.ib));
}

int kinc_g4_index_buffer_count(kinc_g4_index_buffer_t *buffer) {
	return buffer->impl.myCount;
}
