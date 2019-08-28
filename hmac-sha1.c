#include <stdio.h>
#include <string.h>

#ifndef USE_OPENSSL
#include <openssl/evp.h>
#include <openssl/sha.h>
#endif

 /* SHA-1 Blocksize */
#ifndef SHA_BLOCKSIZE
#define SHA_BLOCKSIZE   (64)
#endif

#define IPAD 0x36
#define OPAD 0x5C

void hmac_sha1(const unsigned char *key, const unsigned char *msg){

    unsigned int temp_LENGTH = strlen(msg);
    unsigned char concatBuffer[SHA_BLOCKSIZE + temp_LENGTH];
    unsigned char valueBuffer[SHA_BLOCKSIZE + SHA_DIGEST_LENGTH];
    unsigned int i;


    /**Adadpto la clave **/
    unsigned char k0[SHA_BLOCKSIZE];
    unsigned int hash_key[SHA_DIGEST_LENGTH];

    memset(hash_key, 0, sizeof(hash_key));
    memset(k0, 0, sizeof(k0));
    strncpy(k0, key, strlen(key)); //K0=k
    
    /** Bloque de relleno **/ 
    unsigned char ipad[SHA_BLOCKSIZE];
    unsigned char opad[SHA_BLOCKSIZE];

    //relleno interior ipad
    memset(ipad, IPAD, sizeof(ipad));
    //relleno exterior opad
    memset(opad, OPAD, sizeof(opad));

    //k0 XOR ipad
    for (i=0; i < SHA_BLOCKSIZE; i++){
        ipad[i] ^= k0[i];
    }
    //k0 XOR opad
    for (i=0; i < SHA_BLOCKSIZE; i++){
        opad[i] ^= k0[i];
    }

    memset(concatBuffer, 0, sizeof(concatBuffer));
    /*Concatenacion: (k0 XOR ipad) || msg */
    strncpy(concatBuffer, ipad, SHA_BLOCKSIZE);
    strncpy(concatBuffer + SHA_BLOCKSIZE, msg, temp_LENGTH);

    /*Inicializo y preparo el contexto para aplicar Hash (Message Diggest)*/
    EVP_MD_CTX mdctx, md_ctx;
    const EVP_MD *mdgst;

    unsigned char hmac_value[EVP_MAX_MD_SIZE]; //valor HMAC de salida
    unsigned int mac_len; //largo salida

    OpenSSL_add_all_digests();

    //Tipo de funcion de hash (digest type)
    mdgst = EVP_get_digestbyname("SHA1");
    if (!mdgst) {
        printf("Message Digest desconocido\n");
    }

    //Inicializa el contexto 'mdctx'
    EVP_MD_CTX_init(&mdctx);
    
    /*Setea el contexto 'mdctx' que usara la funcion hash 'mdgst'
      de tipo SHA1 (implementacion por defecto)*/
    EVP_DigestInit_ex(&mdctx, mdgst, NULL);

    //Hashea 'SHA_BLOCKSIZE + temp_LENGTH' bytes de 'msgBuffer' en mdctx
    EVP_DigestUpdate(&mdctx, concatBuffer, (SHA_BLOCKSIZE + temp_LENGTH));
    
    //Coloca el valor del hash sobre 'mdctx' y lo inserta en 'hmac_value'
    EVP_DigestFinal_ex(&mdctx, hmac_value, &mac_len);

    unsigned char *parcial_value;
    parcial_value = malloc(mac_len);
    strncpy(parcial_value, hmac_value, mac_len);

    /**Concatenacion: (k0 XOR opad) || H((k0 XOR ipad) || msg)**/
    memset(valueBuffer, 0, sizeof(valueBuffer));
    strncpy(valueBuffer, opad, SHA_BLOCKSIZE);
    strncpy(valueBuffer + SHA_BLOCKSIZE, parcial_value, mac_len);

    /*Aplicacion ultimo hash: H((k0 XOR opad) || H((k0 XOR ipad) || msg))**/
    EVP_MD_CTX_init(&md_ctx);//Se inicializa nuevamente el contexto pues antes se aplico EVP_DigestFinal_ex
    EVP_DigestInit_ex(&md_ctx, mdgst, NULL);
    EVP_DigestUpdate(&md_ctx, valueBuffer, SHA_BLOCKSIZE + SHA_DIGEST_LENGTH);
    EVP_DigestFinal_ex(&md_ctx, hmac_value, &mac_len);

    printf("HMAC-SHA1: ");
    for(i=0; i < mac_len; i++){
        printf("%02x", hmac_value[i]);  
    } 
    printf("\n");

}


int main(void){
    //Ejemplo:
    char msg[] = "Criptografia";
    char key[] = "qwertyuiopasdfgh";

    printf("Largo mensaje: %ld", strlen(msg));printf(" bytes\n");
    printf("Largo clave: %ld", strlen(key));printf(" bytes\n");

    hmac_sha1(key, msg);
    printf("\n");
}