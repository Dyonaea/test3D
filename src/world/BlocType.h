#ifndef BLOCTYPE_H
#define BLOCTYPE_H

#include "../util/util.h"
enum MODEL{
CUBE,
PLANT
};

enum BLOC_ID{
    AIR,
    GRASS
};

struct voxelType{
    bool isSolid;
    bool transparent;
    MODEL blocModel;
    std::array<int, 6> textures;
};

class BlocType{
    public:
        std::unordered_map<BLOC_ID, voxelType> vtRegistry;
        BlocType();
    private: 
        void addBloc(BLOC_ID blocID, bool isSolid, bool transparent, MODEL blocModel, std::array<int, 6> tex);

};

#endif