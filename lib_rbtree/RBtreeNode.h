//
//
//template <class T>
//class RBtreeNode {
//	RBtreeNode<T>* _left;
//	RBtreeNode<T>* _right;
//	RBtreeNode<T>* _parent;
//	T _value;
//	bool _color;
//public:
//	RBtreeNode(T value, RBtreeNode<T>* left = nullptr, RBtreeNode<T>* right = nullptr, RBtreeNode<T>* parent = nullptr, bool color = false);
//	RBtreeNode(const RBtreeNode<T>& node);
//	RBtreeNode<T>& operator = (const RBtreeNode <T>& node);
//	const T& value() const noexcept;
//	const bool& color() const noexcept;
//	RBtreeNode<T>* left();
//	RBtreeNode<T>* right();
//	RBtreeNode<T>* parent();
//	void left(RBtreeNode<T>* node);
//	void right(RBtreeNode<T>* node);
//	void parent(RBtreeNode<T>* node);
//	void color(bool& color);
//	void value(T& value);
//};
//
//template<class T>
//RBtreeNode<T>::RBtreeNode(T value, RBtreeNode<T>* left, RBtreeNode<T>* right, RBtreeNode<T>* parent, bool color) {
//	_value = value; _left = left; _right = right; _parent = parent; _color = color;
//}
//
//template<class T>
//RBtreeNode<T>::RBtreeNode(const RBtreeNode<T>& node) {
//	_value = node._value;
//	_right = node._right;
//	_left = node._left;
//	_parent = node._parent;
//	_color = node._color;
//}
//
//template<class T>
//RBtreeNode<T>& RBtreeNode<T>::operator = (const RBtreeNode <T>& node) {
//	if (&node != this) {
//		_value = node._value;
//		_right = node._right;
//		_left = node._left;
//		_parent = node._parent;
//		_color = node._color;
//	}
//	return *this;
//}
//
//template<class T>
//const T& RBtreeNode<T>::value() const noexcept {
//	return _value;
//}
//
//template<class T>
//const bool& RBtreeNode<T>::color() const noexcept {
//	return _color;
//}
//
//template<class T>
//RBtreeNode<T>* RBtreeNode<T>::left() {
//	return _left;
//}
//
//template<class T>
//RBtreeNode<T>* RBtreeNode<T>::right() {
//	return _right;
//}
//
//template<class T>
//RBtreeNode<T>* RBtreeNode<T>::parent() {
//	return _parent;
//}
//
//template<class T>
//void RBtreeNode<T>::left(RBtreeNode<T>* node) {
//	_left = node;
//}
//
//template<class T>
//void RBtreeNode<T>::right(RBtreeNode<T>* node) {
//	_right = node;
//}
//
//template<class T>
//void RBtreeNode<T>::parent(RBtreeNode<T>* node) {
//	_parent = node;
//}
//
//template<class T>
//void RBtreeNode<T>::color(bool& color) {
//	_color = color;
//}
//
//template<class T>
//void RBtreeNode<T>::value(T& value) {
//	_value = value;
//}