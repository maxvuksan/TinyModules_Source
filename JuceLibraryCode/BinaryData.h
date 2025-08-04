/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   RalewayItalicVariableFont_wght_ttf;
    const int            RalewayItalicVariableFont_wght_ttfSize = 303956;

    extern const char*   RalewayVariableFont_wght_ttf;
    const int            RalewayVariableFont_wght_ttfSize = 309720;

    extern const char*   RalewayLight_ttf;
    const int            RalewayLight_ttfSize = 164112;

    extern const char*   RalewayMedium_ttf;
    const int            RalewayMedium_ttfSize = 164128;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 4;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
