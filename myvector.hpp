#include<cstdio>
#include<cstdlib>
#include<cstddef>
#include<initializer_list>
#ifndef MY_VECTOR_WC
#define MY_VECTOR_WC
const int defult_capacity = 4 ;
template <typename T >
class vector{
public:
    typedef T* iterator;
    typedef T* Pointer;
    typedef T value_type;
    typedef T& reference;
    typedef size_t size_type;
    typedef const T& const_reference;
    typedef const T* const_iterator;
    typedef const T* const_Pointer;
    typedef ptrdiff_t difference_type;
private:
    Pointer   head;
    size_type len;
    size_type capcity;
public:
    vector():len(0),capcity(defult_capacity),head(new value_type[capcity]){}
    vector(size_type n,size_type a){
        len=n;
        capcity=2*n;
        head= new value_type[capcity];
        for (int i = 0; i < n; ++i)
        head[i]=a;
    }
    explicit vector(size_type n){
        len=n;
        capcity=2*n;
        head= new value_type[capcity];
        for (int i = 0; i < n; ++i)
        head[i]=0;
    }
    vector(std::initializer_list<value_type> init){
        len=init.size();
        capcity=2*len;
        head= new value_type[capcity];
        int i=0;
        for(auto n:init)
            head[i++]=n;
    }
    ~vector(){delete[] head;}
    vector & operator= (const vector & ){return *this;}
    value_type & operator[] (value_type i){return head[i];}
    class reverse_iterator
    {
    private:
        Pointer p;
    public:
        reverse_iterator (Pointer _p=NULL):p(_p){}
        reverse_iterator operator ++(int){
            Pointer p2=p;
            --p;
            return p2;
        }
        reverse_iterator operator ++(){return --p;}
        reverse_iterator operator --(int){
            Pointer p2=p;
            ++p;
            return p2;
        }
        reverse_iterator operator --(){return ++p;}
        reverse_iterator operator [](int i){return p+i;}
        bool operator == (const reverse_iterator &it){return p==it.p;}
        bool operator != (const reverse_iterator &it){return p!=it.p;}
        value_type operator *(){return *p;}
    };
public:
    iterator begin() {return head;}
    const_iterator begin()const {return head;}
    const_iterator cbegin()const noexcept {return &head[len];}
    iterator end() { return &head[len];}
    const_iterator end()const {return &head[len]; }
    const_iterator cend()const noexcept {return head;}
    reverse_iterator rbegin() {return &head[len-1];}
    const reverse_iterator rbegin()const {return &head[len-1];}
    const reverse_iterator crbegin()const noexcept {return &head[len-1];}
    reverse_iterator rend() {return head-1;}
    const reverse_iterator rend()const {return head-1;}
    const reverse_iterator crend()const noexcept {return head-1;}
    reference at( size_type pos ){
        if(pos<0||pos>len)
            exit(1);
        return head[pos];
    };
    size_type size() const { return len; }
    size_type capacity() const { return capcity; }
    bool empty() const { return size() == 0; }
    reference back() const { return head[ len-1 ]; }
private:
void resize( size_type new_len ){
        if( new_len > capcity )
            reallocate( new_len*2 );
        len = new_len;
    }
void reallocate( size_type new_cap ){
        if( new_cap < len ) return;
        value_type *old = head;
        head = new value_type[ new_cap ];
        for( int k = 0; k < len; k++ )
            head[k] = old[k];
        capcity = new_cap;
        delete [] old;
    }
public:
    void reserve(size_type new_cap)
    {
        if(len==0)
        head= new Pointer[new_cap];
        else
        {
            Pointer old=head;
            size_type oldcap=capcity;
            capcity=new_cap;
            head= new Pointer[new_cap];
            for (int i = 0; i < oldcap; ++i)
            head[i]=old[i];
            delete[] old;
        }
    }
    void push_back(const value_type x){
        if(len == capcity)
            reallocate(2*capcity+1);
        head[len++]=x;
    }
    void push_back(const iterator x){
        if(len == capcity)
            reallocate(2*capcity+1);
        head[len++]=*x;
    }
    void pop_back() {
        if(len==0)
            exit(1);
        len--;
    }
    void clear(){
       while(len)
        pop_back();
    }
    iterator insert( iterator it, const_reference value ){
        if(len == capcity)
            reallocate(2*capcity + 1);
        for (auto i = end()-1; i != it; --i)
                *i=*(i-1);
                *it=value;
        len++;
        return it;
    }
    iterator insert( size_type pos, const_reference value ){
        if(len == capcity)
            reallocate(2*capcity + 1);
        for (auto i = end()-1; i > pos; --i)
                head[i]=head[i-1];
                head[pos]=value;
        len++;
        return &head[pos];
    }
    iterator erase(size_type pos)
    {
        if(len==0)
            exit(1);
        for(int i=pos;i<len;i++)
            head[i]=head[i+1];
        len--;
        return begin()+pos;
    }
    iterator erase( iterator it ){
        if(len==0)
            exit(1);
        for (auto i = it; i != end(); ++i)
            *i=*(i+1);
        len--;
        if(len)
        return it;
        else
        return end();
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
     Pointer data()
    {
        return head;
    }
     void shrink_to_fit()
    {
        capcity=len+1;
        Pointer old=head;
        Pointer head=new value_type[capcity];
        for(int i=0;i<len;i++)
            head[i]=old[i];
            head=old;
        delete[] old;
    }
     void assign(size_type n,const_reference value )
    {
           len=0;
           for (int i = 0; i < n; ++i)
                push_back(value);
    }
};
#endif
//增加了初始化列表
