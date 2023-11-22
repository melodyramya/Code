class SimplifiedDES:

    def __init__(self):
        self.key = [1, 0, 1, 0, 0, 0, 0, 0, 1, 0]
        self.P10 = [3, 5, 2, 7, 4, 10, 1, 9, 8, 6]
        self.P8 = [6, 3, 7, 4, 8, 5, 10, 9]
        self.key1 = [0] * 8
        self.key2 = [0] * 8
        self.IP = [2, 6, 3, 1, 4, 8, 5, 7]
        self.EP = [4, 1, 2, 3, 2, 3, 4, 1]
        self.P4 = [2, 4, 3, 1]
        self.IP_inv = [4, 1, 3, 5, 7, 2, 8, 6]
        self.S0 = [
            [1, 0, 3, 2],
            [3, 2, 1, 0],
            [0, 2, 1, 3],
            [3, 1, 3, 2]
        ]
        self.S1 = [
            [0, 1, 2, 3],
            [2, 0, 1, 3],
            [3, 0, 1, 0],
            [2, 1, 0, 3]
        ]

    def key_generation(self):
        key = [0] * 10

        for i in range(10):
            key[i] = self.key[self.P10[i] - 1]

        Ls = key[:5]
        Rs = key[5:]

        Ls_1 = self.shift(Ls, 1)
        Rs_1 = self.shift(Rs, 1)

        for i in range(5):
            key[i] = Ls_1[i]
            key[i + 5] = Rs_1[i]

        for i in range(8):
            self.key1[i] = key[self.P8[i] - 1]

        Ls_2 = self.shift(Ls, 2)
        Rs_2 = self.shift(Rs, 2)

        for i in range(5):
            key[i] = Ls_2[i]
            key[i + 5] = Rs_2[i]

        for i in range(8):
            self.key2[i] = key[self.P8[i] - 1]

        print("Your Key-1:")
        print(" ".join(map(str, self.key1)))
        print("Your Key-2:")
        print(" ".join(map(str, self.key2)))

    def shift(self, ar, n):
        for _ in range(n):
            temp = ar[0]
            for i in range(len(ar) - 1):
                ar[i] = ar[i + 1]
            ar[-1] = temp
        return ar

    def binary(self, val):
        if val == 0:
            return "00"
        elif val == 1:
            return "01"
        elif val == 2:
            return "10"
        else:
            return "11"

    def function(self, ar, key_):
        l = ar[:4]
        r = ar[4:]

        ep = [r[self.EP[i] - 1] for i in range(8)]

        for i in range(8):
            ar[i] = key_[i] ^ ep[i]

        l1 = ar[:4]
        r1 = ar[4:]

        row = int(str(l1[0]) + str(l1[3]), 2)
        col = int(str(l1[1]) + str(l1[2]), 2)
        val = self.S0[row][col]
        str_l = self.binary(val)

        row = int(str(r1[0]) + str(r1[3]), 2)
        col = int(str(r1[1]) + str(r1[2]), 2)
        val = self.S1[row][col]
        str_r = self.binary(val)

        r = [0] * 4
        for i in range(2):
            c1 = str_l[i]
            c2 = str_r[i]
            r[i] = int(c1)
            r[i + 2] = int(c2)

        r_p4 = [r[self.P4[i] - 1] for i in range(4)]

        for i in range(4):
            l[i] = l[i] ^ r_p4[i]

        output = l + r
        return output

    def swap(self, array, n):
        l = array[:n]
        r = array[n:]
        output = r + l
        return output

    def encryption(self, plaintext):
        arr = [0] * 8

        for i in range(8):
            arr[i] = plaintext[self.IP[i] - 1]

        arr1 = self.function(arr, self.key1)
        after_swap = self.swap(arr1, len(arr1) // 2)
        arr2 = self.function(after_swap, self.key2)
        ciphertext = [0] * 8

        for i in range(8):
            ciphertext[i] = arr2[self.IP_inv[i] - 1]

        return ciphertext

    def decryption(self, ar):
        arr = [0] * 8

        for i in range(8):
            arr[i] = ar[self.IP[i] - 1]

        arr1 = self.function(arr, self.key2)
        after_swap = self.swap(arr1, len(arr1) // 2)
        arr2 = self.function(after_swap, self.key1)
        decrypted = [0] * 8

        for i in range(8):
            decrypted[i] = arr2[self.IP_inv[i] - 1]

        return decrypted

if __name__ == "__main__":
    obj = SimplifiedDES()

    obj.key_generation()

    plaintext = [1, 0, 0, 1, 0, 1, 1, 1]
    print("\nYour plain Text is:")
    print(" ".join(map(str, plaintext)))

    ciphertext = obj.encryption(plaintext)
    print("\nYour cipher Text is:")
    print(" ".join(map(str, ciphertext)))

    decrypted = obj.decryption(ciphertext)
    print("\nYour decrypted Text is:")
    print(" ".join(map(str, decrypted)))