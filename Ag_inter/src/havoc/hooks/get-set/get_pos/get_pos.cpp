#include "get_pos.h"
#include "havoc/hooks/get_trans/get_trans.h"

Vector3 __fastcall hget_position(void* __this, const void* method)
{
	return oget_position(__this, method);
}

Vector3 GetPosition(void* __this)
{
    if (!__this)
        return { 0.0f, 0.0f, 0.0f };

    uintptr_t transform = oget_transform(__this, nullptr);
    if (!transform)
        return { 0.0f, 0.0f, 0.0f };
    return oget_position((void*)transform, nullptr);
}
