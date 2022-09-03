#include <iostream>
#include <fstream>

// #include <io.h>
// #include <fcntl.h>

typedef unsigned char ubyte_t;
ubyte_t coin[] = {
    0x42, 0x4D, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC9, 0xAE, 0xFF, 0xC9, 0xAE, 0xFF, 0x27, 0x7F, 0xFF, 0x27,
    0x7F, 0xFF, 0x27, 0x7F, 0xFF, 0x27, 0x7F, 0xFF, 0xC9, 0xAE, 0xFF, 0xC9, 0xAE, 0xFF, 0xC9, 0xAE,
    0xFF, 0x27, 0x7F, 0xFF, 0x0E, 0xC9, 0xFF, 0x0E, 0xC9, 0xFF, 0x0E, 0xC9, 0xFF, 0x0E, 0xC9, 0xFF,
    0x27, 0x7F, 0xFF, 0xC9, 0xAE, 0xFF, 0xC9, 0xAE, 0xFF, 0x27, 0x7F, 0xFF, 0x00, 0xF2, 0xFF, 0x00,
    0xF2, 0xFF, 0x0E, 0xC9, 0xFF, 0x0E, 0xC9, 0xFF, 0x27, 0x7F, 0xFF, 0xC9, 0xAE, 0xFF, 0x27, 0x7F,
    0xFF, 0x00, 0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x0E, 0xC9, 0xFF,
    0x0E, 0xC9, 0xFF, 0x27, 0x7F, 0xFF, 0x27, 0x7F, 0xFF, 0xB0, 0xE4, 0xEF, 0x00, 0xF2, 0xFF, 0x00,
    0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x0E, 0xC9, 0xFF, 0x0E, 0xC9, 0xFF, 0x27, 0x7F, 0xFF, 0xC9, 0xAE,
    0xFF, 0x27, 0x7F, 0xFF, 0xB0, 0xE4, 0xEF, 0x00, 0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x00, 0xF2, 0xFF,
    0x27, 0x7F, 0xFF, 0xC9, 0xAE, 0xFF, 0xC9, 0xAE, 0xFF, 0x27, 0x7F, 0xFF, 0xB0, 0xE4, 0xEF, 0x00,
    0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x00, 0xF2, 0xFF, 0x27, 0x7F, 0xFF, 0xC9, 0xAE, 0xFF, 0xC9, 0xAE,
    0xFF, 0xC9, 0xAE, 0xFF, 0x27, 0x7F, 0xFF, 0x27, 0x7F, 0xFF, 0x27, 0x7F, 0xFF, 0x27, 0x7F, 0xFF,
    0xC9, 0xAE, 0xFF, 0xC9, 0xAE, 0xFF
};

bool CreateBitmap(const std::string& fileName)
{
    std::ofstream fileHandler(fileName, std::ios::binary);
    if (fileHandler.is_open())
    {
        for (int i = 0; i < sizeof(coin); ++i) {
            fileHandler << coin[i];
        }

        return true;
    }

    return false;
}

int CreateNewCoinBitmap()
{
    return CreateBitmap("new_coin.bmp") ? 0 : 1;
}

int SendNewCoinToStdout()
{
    // don't work; HxD shows a wrong buffer when piping stdout to a file

    // _setmode(_fileno(stdout), _O_BINARY);
    
    // for (int i = 0; i < sizeof(coin); ++i) {
    //     char buf[] = {0x41};
    //     fwrite(buf, 1, 1, stdout);
    // }

    return 0;
}

int main()
{
    // return CreateNewCoinBitmap();
    return SendNewCoinToStdout();
}