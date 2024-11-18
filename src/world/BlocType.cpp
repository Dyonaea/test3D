#include "BlocType.h"

BlocType::BlocType(){
    addBloc(AIR, false, true, CUBE, {-1, -1, -1, -1, -1, -1});
    addBloc(GRASS, true, false, CUBE, {1, 1, 0, 2, 1, 1});
}

void BlocType::addBloc(BLOC_ID blocID, bool isSolid, bool transparent, MODEL blocModel, std::array<int, 6> tex){
    vtRegistry[blocID] = {isSolid, transparent, blocModel, tex};
}