template <typename T>
class TriArray {
  public:
	int length=0;
	int dim=0;
	T *items;
	TriArray(int i){
		dim = i;
		length = i*(i-1)/2;
		items = new T[length];
	}
	~TriArray(){
		delete items;
	}
	size_t index(size_t i, size_t j){
		if(i>j){
			size_t temp = i;
			i = j;
			j = temp;
		}
		return i*dim+j-(i+1)*(i+2)/2;
	}
	T& operator()(size_t i, size_t j){
		return items[index(i,j)];
	}
};