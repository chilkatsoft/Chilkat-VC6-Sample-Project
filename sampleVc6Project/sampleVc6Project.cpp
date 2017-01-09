// sampleVc6Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "chilkat-9.5.0-x86-vc6/include/CkCrypt2.h"

int main(int argc, char* argv[])
{
    freopen("stdout.txt","w",stdout);

    CkCrypt2 crypt;

    bool success = crypt.UnlockComponent("Anything for 30-day trial");
    if (success != true) {
        printf("%s\n",crypt.lastErrorText());
        return 1;
    }

    //  Set the encryption algorithm to chacha20
    //  chacha20 is a stream cipher, and therefore no cipher mode applies.
    crypt.put_CryptAlgorithm("chacha20");

    //  The key length for chacha20 is always 256-bits.
    crypt.put_KeyLength(256);

    //  Note: "padding" only applies to block encryption algorithmns.
    //  Since chacha20 is a stream cipher, there is no padding and the output
    //  number of bytes is exactly equal to the input.

    //  EncodingMode specifies the encoding of the output for
    //  encryption, and the input for decryption.
    //  Valid modes are (case insensitive) "Base64", "modBase64", "Base32", "Base58", "UU",
    //  "QP" (for quoted-printable), "URL" (for url-encoding), "Hex",
    //  "Q", "B", "url_oauth", "url_rfc1738", "url_rfc2396", and "url_rfc3986".
    crypt.put_EncodingMode("hex");

    //  The inputs to ChaCha20 encryption, specified by RFC 7539, are:
    //  1) A 256-bit secret key.
    //  2) A 96-bit nonce.
    //  3) A 32-bit initial count.
    //  The IV property is used to specify the chacha20 nonce.
    //  For a 96-bit nonce, the IV should be 12 bytes in length.
    // 
    //  Note: Some implementations of chacha20, such as that used internally by SSH,
    //  use a 64-bit nonce and 64-bit count.  To do chacha20 encryption in this way,
    //  simply provide 8 bytes for the IV instead of 12 bytes.  Chilkat will then automatically
    //  use 8 bytes (64-bits) for the count.

    //  This example duplicates Test Vector #3 (for ChaCha20 encryption) from RFC 7539.
    const char *ivHex = "000000000000000000000002";
    crypt.SetEncodedIV(ivHex,"hex");

    crypt.put_InitialCount(42);

    const char *keyHex = "1c9240a5eb55d38af333888604f6b5f0473917c1402b80099dca5cbc207075c0";
    crypt.SetEncodedKey(keyHex,"hex");

    const char *plainText = "'Twas brillig, and the slithy toves\nDid gyre and gimble in the wabe:\nAll mimsy were the borogoves,\nAnd the mome raths outgrabe.";

    const char *encStr = crypt.encryptStringENC(plainText);
    printf("%s\r\n",encStr);

    //  Now decrypt:
    const char *decStr = crypt.decryptStringENC(encStr);
    printf("%s\r\n",decStr);

    return 0;
}

