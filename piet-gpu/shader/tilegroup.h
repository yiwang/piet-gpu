// Code auto-generated by piet-gpu-derive

struct InstanceRef {
    uint offset;
};

struct TileGroupRef {
    uint offset;
};

struct Instance {
    uint item_ref;
    vec2 offset;
};

#define Instance_size 12

InstanceRef Instance_index(InstanceRef ref, uint index) {
    return InstanceRef(ref.offset + index * Instance_size);
}

#define TileGroup_Instance 0
#define TileGroup_End 1
#define TileGroup_size 16

TileGroupRef TileGroup_index(TileGroupRef ref, uint index) {
    return TileGroupRef(ref.offset + index * TileGroup_size);
}

Instance Instance_read(InstanceRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = tilegroup[ix + 0];
    uint raw1 = tilegroup[ix + 1];
    uint raw2 = tilegroup[ix + 2];
    Instance s;
    s.item_ref = raw0;
    s.offset = vec2(uintBitsToFloat(raw1), uintBitsToFloat(raw2));
    return s;
}

void Instance_write(InstanceRef ref, Instance s) {
    uint ix = ref.offset >> 2;
    tilegroup[ix + 0] = s.item_ref;
    tilegroup[ix + 1] = floatBitsToUint(s.offset.x);
    tilegroup[ix + 2] = floatBitsToUint(s.offset.y);
}

uint TileGroup_tag(TileGroupRef ref) {
    return tilegroup[ref.offset >> 2];
}

Instance TileGroup_Instance_read(TileGroupRef ref) {
    return Instance_read(InstanceRef(ref.offset + 4));
}

void TileGroup_Instance_write(TileGroupRef ref, Instance s) {
    tilegroup[ref.offset >> 2] = TileGroup_Instance;
    Instance_write(InstanceRef(ref.offset + 4), s);
}

void TileGroup_End_write(TileGroupRef ref) {
    tilegroup[ref.offset >> 2] = TileGroup_End;
}

