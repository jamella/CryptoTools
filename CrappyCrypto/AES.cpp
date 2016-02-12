#include "PreCompile.h"

namespace AES
{

const unsigned int Nb = 4;

static const uint8_t AES_SBox[] =
{
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static const uint8_t AES_Invert_SBox[] =
{
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

void AES_add_round_key(std::vector<uint8_t>& state, const std::vector<uint8_t>& key_schedule, unsigned int schedule_index)
{
    // TODO: std::transform ?
    for(auto ix = 0u; ix < Nb; ++ix)
    {
        state[ix] = state[ix] ^ key_schedule[schedule_index + ix];
    }
}

void AES_sub_bytes(std::vector<uint8_t>& state)
{
    // TODO: std::transform ?
    for(auto ix = 0u; ix < Nb * 4; ++ix)
    {
        state[ix] = AES_SBox[state[ix]];
    }
}

template <typename Iter>
void AES_sub_bytes2(Iter& start, Iter& end)
{
    // TODO: std::transform ?
    //std::transform(start, end, start, [](){});
    while(start != end)
    {
        *start = AES_SBox[*start];
        ++start;
    }
}

void AES_shift_rows(std::vector<uint8_t>& state)
{
    // Starting at zero would be a no-op.
    for(auto ix = 1u; ix < 4; ++ix)
    {
        // TODO: check usage.
        std::rotate(std::begin(state) + ix * 4,
                    std::begin(state) + ix * 4 + ix,
                    std::begin(state) + ix * 4 + 4);
    }
}

void AES_mix_columns(std::vector<uint8_t>& state)
{
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;

    for(auto ix = 0u; ix < 4; ++ix)
    {
        A = 2 * state[ix] ^ 3 * state[4 + ix] ^ state[8 + ix] ^ state[12 + ix];
        B = state[ix] ^ 2 * state[4 + ix] ^ 3 * state[8 + ix] ^ state[12 + ix];
        C = state[ix] ^ state[4 + ix] ^ 2 * state[8 + ix] ^ 3 * state[12 + ix];
        D = 3 * state[ix] ^ state[ix + 4] ^ state[ix + 8] ^ 2 * state[12 + ix];

        state[ix] = A;
        state[4 + ix] = B;
        state[8 + ix] = C;
        state[12 + ix] = D;
    }

    // Destroy intermediate state.
    // TODO: may need SecureZeroMemory.
    A = B = C = D = 0;
}

template<int AES_key_size>
std::vector<uint8_t> AES_cipher(const std::vector<uint8_t>& input, const std::vector<uint8_t>& key_schedule)
{
    assert(input.size() == 4 * Nb); // 4*Nb (4) == 16 == 128 bits.
    //assert(key_schedule.size() == ??);

    std::vector<uint8_t> state(input);
    AES_add_round_key(state, key_schedule, 0);

    for(auto round = 1u; round < AES_key_size / 32 + 6 - 1; ++round)
    {
        AES_sub_bytes(state);
        AES_shift_rows(state);
        AES_mix_columns(state);
        AES_add_round_key(state, key_schedule, round * Nb);
    }

    AES_sub_bytes(state);
    AES_shift_rows(state);
    AES_add_round_key(state, key_schedule, Nb * (AES_key_size / 32 + 6));

    return state;

#if 0
//Cipher(byte in[4*Nb], byte out[4*Nb], word w[Nb*(Nr+1)])
// begin
// byte state[4,Nb]
 
//state = in
 
//AddRoundKey(state, w[0, Nb-1]) // See Sec. 5.1.4
 
//for round = 1 step 1 to Nr�1
// SubBytes(state) // See Sec. 5.1.1
// ShiftRows(state) // See Sec. 5.1.2
// MixColumns(state) // See Sec. 5.1.3
// AddRoundKey(state, w[round*Nb, (round+1)*Nb-1])
// end for
 
//SubBytes(state)
// ShiftRows(state)
// AddRoundKey(state, w[Nr*Nb, (Nr+1)*Nb-1])
 
//out = state
// end
#endif
}

template<int AES_key_size>
std::vector<uint8_t> AES_key_expansion(const std::vector<uint8_t>& key)
{
    std::vector<uint8_t> key_expansion;
    key_expansion.reserve(Nb * (AES_key_size / 32 + 6 + 1));

    // TODO: Does std::copy realloc?
    std::copy(key.cbegin(), key.cend(), std::begin(key_expansion));
    assert(key_expansion.capacity() == Nb * (AES_key_size / 32 + 6 + 1));

    uint8_t temp[4];
    for(int ix = AES_key_size / 32; ix <= Nb * (AES_key_size / 32 + 6); ++ix)
    {
        temp[0] = key_expansion[(ix - 1) * 4 + 0];
        temp[1] = key_expansion[(ix - 1) * 4 + 1];
        temp[2] = key_expansion[(ix - 1) * 4 + 2];
        temp[3] = key_expansion[(ix - 1) * 4 + 3];

        if((ix % (AES_key_size / 32)) == 0)
        {
            //temp = SubWord(RotWord(temp)) xor Rcon[i/Nk]
            //auto rot = 
            std::rotate(std::begin(temp), std::end(temp), std::begin(temp) + 1);
            // Rcon
            AES_sub_bytes2(std::begin(temp), std::end(temp));
        }
        else if((AES_key_size / 32) > 6 && ((ix % (AES_key_size / 32)) == 4))
        {
            //temp = SubWord(temp)
            AES_sub_bytes2(std::begin(temp), std::end(temp));
        }

        key_expansion[ix * 4 + 0] = key_expansion[(ix * 4) - (AES_key_size / 32) + 0] ^ temp[0];
        key_expansion[ix * 4 + 1] = key_expansion[(ix * 4) - (AES_key_size / 32) + 1] ^ temp[1];
        key_expansion[ix * 4 + 2] = key_expansion[(ix * 4) - (AES_key_size / 32) + 2] ^ temp[2];
        key_expansion[ix * 4 + 3] = key_expansion[(ix * 4) - (AES_key_size / 32) + 3] ^ temp[3];
    }

    return key_expansion;
}

#if 0
//KeyExpansion(byte key[4*Nk], word w[Nb*(Nr+1)], Nk)
// begin
// word temp
 
//i = 0
 
//while (i < Nk)
// w[i] = word(key[4*i], key[4*i+1], key[4*i+2], key[4*i+3])
// i = i+1
// end while
 
//i = Nk
 
//while (i < Nb * (Nr+1)]
// temp = w[i-1]
// if (i mod Nk = 0)
 temp = SubWord(RotWord(temp)) xor Rcon[i/Nk]
// else if (Nk > 6 and i mod Nk = 4)
// temp = SubWord(temp)
// end if
// w[i] = w[i-Nk] xor temp
// i = i + 1
// end while
// end
#endif
}

