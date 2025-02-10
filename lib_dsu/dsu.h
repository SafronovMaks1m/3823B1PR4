class DSU {
	int _size;
	int* _parent;
	int* _rank;
public:
	DSU(int size = 0);
	~DSU();
	void make_set(int elem);
	int find(int elem);
	void uni(int first, int second);
	void clear();
};