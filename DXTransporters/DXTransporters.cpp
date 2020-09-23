#include "pch.h"
#include "ModelInfo.h"
#include "SA2ModLoader.h"

extern "C"
{
    // signed int __usercall@<eax>(unsigned __int16 a1@<ax>, char *a2@<ebx>, NJS_TEXLIST *texlist)
    static const void* const LoadChaoTexlistPtr = (void*)0x00530280;
    static inline signed int LoadChaoTexlist(unsigned __int16 a1, const char* a2, NJS_TEXLIST* texlist)
    {
        signed int result;
        __asm
        {
            push[texlist]
            mov ebx, [a2]
            mov ax, [a1]
            call LoadChaoTexlistPtr
            add esp, 4
            mov result, eax
        }
        return result;
    }

    NJS_TEXNAME NameMachineTexCount[8];
    NJS_TEXLIST nNameMachineTexList = { arrayptrandlength(NameMachineTexCount) };

    void chaoLoadTex()
    {
        PrintDebug("\nMemoryCard Init\n");
        PrintDebug("Loading Transporter PAK...");
        LoadChaoTexlist(0, "AL_TRANSPORTER", &nNameMachineTexList);
    }

    __declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
    {

        WriteCall((void*)0x0057E262, nullsub_1); //Removes Transporter Head

        WriteCall((void*)0x0052AE1F, chaoLoadTex);

        NJS_OBJECT* DXBase = (NJS_OBJECT*)0x125A23C;
        *DXBase = *(new ModelInfo(std::string(path) + "\\Objects\\DXNMBase.sa2mdl"))->getmodel();

        NJS_OBJECT* DXDoor = (NJS_OBJECT*)0x1256994;
        *DXDoor = *(new ModelInfo(std::string(path) + "\\Objects\\DXNMDoor.sa2mdl"))->getmodel();

        //E56784 + 400000 = 1256784
        NJS_OBJECT* DXButn = (NJS_OBJECT*)0x1256784;
        *DXButn = *(new ModelInfo(std::string(path) + "\\Objects\\DXNMButn.sa2mdl"))->getmodel();

        WriteData((NJS_TEXLIST**)0x0123F064, &nNameMachineTexList);

    }
    __declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}