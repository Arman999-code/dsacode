class hashtable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_func(self, key):
        return key % self.size

    def insert(self, key):
        index = self.hash_func(key)
        self.table[index].append(key)

    def search(self, key):
        index = self.hash_func(key)
        if key in self.table[index]:
            return True
        return False

    def delete(self, key):
        index = self.hash_func(key)
        if key in self.table[index]:
            self.table[index].remove(key)
            return True
        return False

    def display(self):
        for index, chain in enumerate(self.table):
            print(f"Index {index}: {chain}")

# Main block (outside class)
if __name__ == "__main__":
    ht = hashtable(10)
    ht.insert(15)
    ht.insert(25)
    ht.insert(35)
    ht.insert(64)
    print("Hash Table:")
    ht.display()

    key = 25
    print(f"\nSearch for {key}: {'Found' if ht.search(key) else 'Not Found'}")

    key = 35
    print(f"Delete {key}: {'Success' if ht.delete(key) else 'Failure'}")

    print("\nHash Table after deletion:")
    ht.display()
