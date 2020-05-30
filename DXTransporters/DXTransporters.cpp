#include "pch.h"
#include "ModelInfo.h"
#include "SA2ModLoader.h"

extern "C"
{

    __declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
    {

        WriteCall((void*)0x0057E262, nullsub_1); //Removes Transporter Head

        NJS_OBJECT* DXBase = (NJS_OBJECT*)0x125A23C;
        *DXBase = *(new ModelInfo(std::string(path) + "\\Objects\\DXNMBase.sa2mdl"))->getmodel();

        NJS_OBJECT* DXDoor = (NJS_OBJECT*)0x1256994;
        *DXDoor = *(new ModelInfo(std::string(path) + "\\Objects\\DXNMDoor.sa2mdl"))->getmodel();

        //E56784 + 400000 = 1256784
        NJS_OBJECT* DXButn = (NJS_OBJECT*)0x1256784;
        *DXButn = *(new ModelInfo(std::string(path) + "\\Objects\\DXNMButn.sa2mdl"))->getmodel();

    }
    __declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}