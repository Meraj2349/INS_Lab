import os
import time
import hashlib
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto.Random import get_random_bytes
from base64 import b64encode, b64decode


# AES ENCRYPTION / DECRYPTION

def aes_encrypt(file_name, key_size=128, mode='ECB'):
    key = get_random_bytes(key_size // 8)
    iv = get_random_bytes(16)
    with open(file_name, 'rb') as f:
        plaintext = f.read()

    start = time.time()

    if mode.upper() == 'ECB':
        cipher = AES.new(key, AES.MODE_ECB)
        # PKCS7 padding
        pad_len = 16 - len(plaintext) % 16
        plaintext += bytes([pad_len]) * pad_len
        ciphertext = cipher.encrypt(plaintext)
    elif mode.upper() == 'CFB':
        cipher = AES.new(key, AES.MODE_CFB, iv)
        ciphertext = cipher.encrypt(plaintext)
    else:
        print("Unsupported mode")
        return

    end = time.time()

    with open('aes_key.bin', 'wb') as f:
        f.write(key)
    with open('aes_iv.bin', 'wb') as f:
        f.write(iv)
    with open('aes_output.bin', 'wb') as f:
        f.write(ciphertext)

    print(f"\n[AES {mode}] Encryption done in {end - start:.6f} seconds")
    print(f"Ciphertext saved as aes_output.bin\n")


def aes_decrypt(cipher_file, key_file='aes_key.bin', iv_file='aes_iv.bin', mode='ECB'):
    with open(key_file, 'rb') as f:
        key = f.read()
    with open(cipher_file, 'rb') as f:
        ciphertext = f.read()
    if os.path.exists(iv_file):
        with open(iv_file, 'rb') as f:
            iv = f.read()
    else:
        iv = None

    start = time.time()

    if mode.upper() == 'ECB':
        cipher = AES.new(key, AES.MODE_ECB)
        plaintext = cipher.decrypt(ciphertext)
        pad_len = plaintext[-1]
        plaintext = plaintext[:-pad_len]
    elif mode.upper() == 'CFB':
        cipher = AES.new(key, AES.MODE_CFB, iv)
        plaintext = cipher.decrypt(ciphertext)
    else:
        print("Unsupported mode")
        return

    end = time.time()

    print(f"\n[AES {mode}] Decryption done in {end - start:.6f} seconds")
    print("Recovered plaintext:\n")
    print(plaintext.decode(errors='ignore'))



# RSA ENCRYPTION / DECRYPTION

def rsa_generate_keys():
    key = RSA.generate(2048)
    private_key = key.export_key()
    public_key = key.publickey().export_key()
    with open("rsa_priv.pem", "wb") as f:
        f.write(private_key)
    with open("rsa_pub.pem", "wb") as f:
        f.write(public_key)
    print("RSA keys generated successfully.\n")


def rsa_encrypt(file_name):
    with open("rsa_pub.pem", "rb") as f:
        pub_key = RSA.import_key(f.read())
    with open(file_name, "rb") as f:
        plaintext = f.read()

    cipher = PKCS1_OAEP.new(pub_key)

    start = time.time()
    ciphertext = cipher.encrypt(plaintext)
    end = time.time()

    with open("rsa_output.bin", "wb") as f:
        f.write(ciphertext)

    print(f"\nRSA Encryption done in {end - start:.6f} seconds.")
    print("Ciphertext saved as rsa_output.bin\n")


def rsa_decrypt(cipher_file="rsa_output.bin"):
    with open("rsa_priv.pem", "rb") as f:
        priv_key = RSA.import_key(f.read())
    with open(cipher_file, "rb") as f:
        ciphertext = f.read()

    cipher = PKCS1_OAEP.new(priv_key)

    start = time.time()
    plaintext = cipher.decrypt(ciphertext)
    end = time.time()

    print(f"\nRSA Decryption done in {end - start:.6f} seconds.")
    print("Recovered plaintext:\n")
    print(plaintext.decode(errors='ignore'))



# RSA SIGNATURE / VERIFICATION

def rsa_sign(file_name):
    with open("rsa_priv.pem", "rb") as f:
        key = RSA.import_key(f.read())
    with open(file_name, "rb") as f:
        data = f.read()

    h = SHA256.new(data)
    signature = pkcs1_15.new(key).sign(h)

    with open("rsa_signature.bin", "wb") as f:
        f.write(signature)

    print("Signature generated and saved as rsa_signature.bin\n")


def rsa_verify(file_name):
    with open("rsa_pub.pem", "rb") as f:
        pub_key = RSA.import_key(f.read())
    with open(file_name, "rb") as f:
        data = f.read()
    with open("rsa_signature.bin", "rb") as f:
        signature = f.read()

    h = SHA256.new(data)
    try:
        pkcs1_15.new(pub_key).verify(h, signature)
        print("Signature verification: SUCCESS ✅\n")
    except (ValueError, TypeError):
        print("Signature verification: FAILED ❌\n")



# SHA-256 HASHING

def sha256_hash(file_name):
    with open(file_name, "rb") as f:
        data = f.read()
    h = hashlib.sha256(data).hexdigest()
    print("\nSHA-256 Hash:")
    print(h + "\n")



# MAIN MENU

def main():
    while True:
        print("\n===== CRYPTO LAB MENU =====")
        print("1. AES Encrypt")
        print("2. AES Decrypt")
        print("3. RSA Key Generation")
        print("4. RSA Encrypt")
        print("5. RSA Decrypt")
        print("6. RSA Sign")
        print("7. RSA Verify")
        print("8. SHA-256 Hash")
        print("9. Exit")

        choice = input("\nEnter your choice: ")

        if choice == '1':
            f = input("Enter plaintext file: ")
            mode = input("Enter mode (ECB/CFB): ")
            key_size = int(input("Enter key size (128/256): "))
            aes_encrypt(f, key_size, mode)
        elif choice == '2':
            aes_decrypt("aes_output.bin")
        elif choice == '3':
            rsa_generate_keys()
        elif choice == '4':
            f = input("Enter plaintext file: ")
            rsa_encrypt(f)
        elif choice == '5':
            rsa_decrypt()
        elif choice == '6':
            f = input("Enter file to sign: ")
            rsa_sign(f)
        elif choice == '7':
            f = input("Enter file to verify: ")
            rsa_verify(f)
        elif choice == '8':
            f = input("Enter file to hash: ")
            sha256_hash(f)
        elif choice == '9':
            print("Exiting program.")
            break
        else:
            print("Invalid option.\n")

import argparse

def cli_mode():
    parser = argparse.ArgumentParser(description="Crypto Lab Command-Line Tool")
    parser.add_argument("--aes", action="store_true", help="Run AES encryption/decryption")
    parser.add_argument("--mode", choices=["ecb", "cfb"], help="AES mode")
    parser.add_argument("--keysize", type=int, help="AES key size (128 or 256)")
    parser.add_argument("--encrypt", help="Encrypt input file")
    parser.add_argument("--decrypt", help="Decrypt ciphertext file")
    parser.add_argument("--rsa", action="store_true", help="Run RSA encryption/decryption")
    parser.add_argument("--sign", help="Generate RSA signature for a file")
    parser.add_argument("--verify", help="Verify RSA signature for a file")
    parser.add_argument("--hash", help="Generate SHA-256 hash of a file")

    args = parser.parse_args()

    if args.aes:
        if args.encrypt:
            aes_encrypt(args.encrypt, args.keysize or 128, args.mode or 'ECB')
        elif args.decrypt:
            aes_decrypt(args.decrypt, mode=args.mode or 'ECB')

    elif args.rsa:
        if args.encrypt:
            rsa_encrypt(args.encrypt)
        elif args.decrypt:
            rsa_decrypt()

    elif args.sign:
        rsa_sign(args.sign)

    elif args.verify:
        rsa_verify(args.verify)

    elif args.hash:
        sha256_hash(args.hash)

    else:
        main()

if __name__ == "__main__":
    cli_mode()