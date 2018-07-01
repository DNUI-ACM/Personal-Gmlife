#include <stdio.h>
const int defult_capacity = 4 ;
template <typename T >
class vector{
private:
    typedef T* Pointer;
    typedef size_t size_type;
public:
    Pointer   head;
    size_type len;
    size_type capcity;
    vector(){
        len=0;
        capcity=defult_capacity;
        head= new T[defult_capacity];
    }
    ~vector(){
        delete[] head;
    }
    const vector & operator= ( const vector & rhs ){
        if( this != &rhs ){
            delete [] head;
            len = rhs.len();
            capcity = rhs.capcity();
            head = new T[ capcity() ];
            for( int k = 0; k < len; k++ )
                head[k] = rhs.head[k];
        }
        return *this;
    }
    T & operator[] (int i){return head[i];}
    const T & operator[] (int i) const {return head[ i ];}
public:
    class iterator{
        private:
            Pointer p;
        public:
            iterator(Pointer _p){
                p=_p;
            }
            iterator(){
                p=NULL;
            }
            iterator operator ++(int){
                return p+1;
            }
            iterator operator ++(){
                Pointer p2=p;
                p++;
                return p2;
            }
            iterator operator --(int){
                return p-1;
            }
            iterator operator --(){
                Pointer p2=p;
                p=p--;
                return p2;
            }
            iterator operator [](int i){
                return p+i;
            }
            friend bool operator ==(const iterator lsh,const iterator rsh){
            return lsh.p==rsh.p;
            }
            friend bool operator != (const iterator & lsh,const iterator & rsh){
            return lsh.p != rsh.p;
            }
            T & operator *(){
                return *p;
            }
            T * operator ->(){
                return &p;
            }
    };
public:
    int size() const { return len; }
    int capacity() const { return capcity; }
    bool empty() const { return size() == 0; }
    const T & back() const { return head[ len-1 ]; }
    iterator begin() {return &head[0];}
    iterator end()   { return &head[len]; }
private:
void resize( int newlen ){
        if( newlen > capcity )
            ReAllocate( newlen*2 );
        len = newlen;
    }
void ReAllocate( int newCapacity ){
        if( newCapacity < len ) return;

        T *oldArray = head;
        head = new T[ newCapacity ];
        for( int k = 0; k < len; k++ )
            head[k] = oldArray[k];
        capcity = newCapacity;
        delete [] oldArray;
    }
public:
    void reserve(size_type new_cap)
    {
        head= new Pointer[new_cap];
    }
    void push_back(const T & x){
        if(len == capcity)
            ReAllocate(2*capcity+1);
        head[len++]=x;
    }
    void pop_back() {len--;}
    void clear()   {delete[] head;}
    void insert( int pos, const T& value ){
        if(len == capcity)
            ReAllocate(2*capcity + 1);
        else{
            for (int i = len+1; i > pos; --i)
            {
                int af=i-1;
                head[i]=head[af];
            }
            head[pos]=value;
        }
        len++;
    }
    void erase( int pos ){
        for (int i = pos; i <= len; ++i)
        {
            int af=i+1;
            head[i]=head[af];
        }
        len--;
    }
    void swap( vector& other ) {
        Pointer temp=other.head;
        size_type tlen=len;
        size_type tcapacity=capcity;
        other.head=head;
        head=temp;
        len=other.size();
        capcity=other.capacity();
        other.len=tlen;
        other.capcity=tcapacity;
    }
};