#include<cstdio>
#include<cstdlib>
#include<cstddef>
#include<initializer_list>
#include<iostream>
#ifndef MY_LIST_WC
#define MY_LIST_WC
template<typename T>
class list
{
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    class node
    {
    private:
        value_type data;
        node* nex;
        node* per;
    public:
        node():data(0),nex(nullptr),per(nullptr){}
        node(value_type a):data(a),nex(nullptr),per(nullptr){}
        ~node(){}
        node* & getper(){return per;}
        node* & getnex(){return nex;}
        reference getvalue(){return data;}
    };
private:
    node gh,gt;
    node* head;
    node* tail;
    size_type len;
public:
    list():head(&gh),tail(&gt),len(0){}
    explicit list( size_type count, const_reference value):head(&gh),tail(&gt),len(0){
        for (int i = 0; i < count; ++i)
            push_back(value);
    }
    list(std::initializer_list<value_type> init):head(&gh),tail(&gt),len(0){
        for(auto n:init)
        push_back(n);
    }
    ~list(){clear();}
    list & operator = (const list& other)
    {
        if(this!=&other)
       {
        iterator first1=begin();
        iterator last1=end();
        iterator first2=other.begin();
        iterator last2=other.end();
        while(first1!=last1&&first2!=last2)
            *(first1++) = *(first2++);
        if(first2==last2)
            erase(first1,last1);
        else
            insert(last1,first2,last2);
       }
    }
    void assign( size_type count,const_reference value ){
        clear();
        for (int i = 0; i < count; ++i)
        push_back(value);
    }
    class iterator
    {
    private:
        node* p;
    public:
        iterator(node* _p=nullptr):p(_p){}
        iterator operator ++(int){
            node* p2=p;
            p=p->getnex();
            return p2;
        }
        iterator operator ++(){return p=p->getnex();}
        iterator operator --(int){
            node* p2=p;
            p=p->getper();
            return p2;
        }
        iterator operator --(){return p=p->getper();}
        friend bool operator == (const iterator &lsh,const iterator &rsh){return lsh.p==rsh.p;}
        friend bool operator != (const iterator &lsh,const iterator &rsh){return lsh.p!=rsh.p;}
        reference operator *(){return p->getvalue();}
        node* operator ->(){return p;}
        node* operator &(){return p;}
    };
    class reverse_iterator
    {
    private:
        node* p;
    public:
        reverse_iterator(node* _p=nullptr):p(_p){};
        reverse_iterator operator ++(int){

            node* p2=p;
            p=p->getper();
            return p2;
        }
        reverse_iterator operator ++(){return p=p->getper();}
        reverse_iterator operator --(int){
            node* p2=p;
            p=p->getnex();
            return p2;
        }
        reverse_iterator operator --(){return p=p->getnex();}
        friend bool operator == (const reverse_iterator &lsh,const reverse_iterator &rsh){return lsh.p==rsh.p;}
        friend bool operator != (const reverse_iterator &lsh,const reverse_iterator &rsh){return lsh.p!=rsh.p;}
        reference operator *(){return p->getvalue();}
        node* operator ->(){return p;}
        node* operator &(){return p;}
    };
    typedef const iterator const_iterator;
    typedef const reverse_iterator const_reverse_iterator;
public:
    reference front(){return head->getvalue();}
    const_reference front() const {return head->getvalue();}
    reference back() {return tail->getvalue();}
    const_reference back() const {return tail->getvalue();}
    iterator begin() {return head;}
    const iterator begin()const {return head;}
    const iterator cbegin()const noexcept {return tail->getnex();}
    iterator end() { return tail->getnex();}
    const iterator end()const {return tail->getnex(); }
    const iterator cend()const noexcept {return head;}
    reverse_iterator rbegin() {return tail;}
    const reverse_iterator rbegin()const {return tail;}
    const reverse_iterator crbegin()const noexcept {return head->getper();}
    reverse_iterator rend() {return head->getper();}
    const reverse_iterator rend()const {return head->getper();}
    const reverse_iterator crend()const noexcept {return tail;}
    bool empty(){return len==0;}
    size_type size(){return len;}
public:
    void clear(){
        if(empty())
            return;
        while(!empty())
            pop_back();
    }
    void push_back(const_reference value ){
        node* _node=new node(value);
        if(len==0)
            {
                tail=head=_node;
                tail->getnex()=&gt;
                head->getper()=&gh;
                len++;
                return;
            }
        if(len==1)
            {
                head->getnex()=_node;
                _node->getper()=head;
                _node->getnex()=&gt;
                tail=_node;
                len++;
                return;
            }
        tail->getnex()=_node;
        _node->getper()=tail;
        _node->getnex()=&gt;
        tail=_node;
        len++;
    }
    void push_front(const_reference value ){
        node* _node=new node(value);
        if(len==0)
            {
                tail=head=_node;
                tail->getnex()=&gt;
                head->getper()=&gh;
                len++;
                return;
            }
        if(len==1)
            {
                tail->getper()=_node;
                _node->getnex()=tail;
                _node->getper()=&gh;
                head=_node;
                len++;
                return;
            }
        head->getper()=_node;
        _node->getnex()=head;
        _node->getper()=&gh;
        head=_node;
        len++;
    }
    void pop_back(){
        if(len==0)
            return;
        if(len==1)
            {
                node* del=tail;
                tail=&gt;
                head=&gh;
                len=0;
                delete del;
                return;
            }
        node* del=tail;
        tail=tail->getper();
        tail->getnex()=&gt;
        len--;
        delete del;
    }
    void pop_front(){
        if(len==0)
            return;
        if(len==1)
            {
                node* del=head;
                tail=&gt;
                head=&gh;
                len=0;
                delete del;
                return;
            }
        node* del=head;
        head=head->getnex();
        head->getper()=&gt;
        len--;
        delete del;
    }
    iterator insert( iterator pos, const_reference value ){
        node* _node=new node(value);
        if(len==0)
        {
            push_back(value);
            return head;
        }
        if(pos==begin())
        {
            push_front(value);
            return head;
        }
        _node->getper()=pos->getper();
        _node->getnex()=&pos;
        pos->getper()->getnex()=_node;
        pos->getper()=_node;
        len++;
        return _node;
    }
    iterator insert( iterator pos, const_iterator first , const_iterator last){
        while(first!=last)
            insert(pos,*first++);
        return last;
    }
    iterator erase( iterator pos ){
        if(pos==begin())
        {
            pop_front();
            return begin();
        }
        pos->getper()->getnex()=pos->getnex();
        pos->getnex()->getper()=pos->getper();
        node* temp=pos->getnex();
        len--;
        node* del=&pos;
        delete del;
        if(len==0)
        return end();
        else
        return temp;
    }
    iterator erase(iterator first,iterator last)
    {
        while(first!=last)
            erase(first++);
        return last;
    }
    void swap( list& other ){
        std::swap(head,other.head);
        std::swap(tail,other.tail);
        std::swap(len,other.len);
    }
    void resize( size_type count ){
        if(count==len)
            return;
        if(count<len)
            {
                while(len!=count)
                    pop_back();
                return;
            }
        if(count>len)
            {
                while(len!=count)
                    push_back(0);
            }
    }
    void resize( size_type count, const_reference value ){
        if(count==len)
            return;
        if(count<len)
            {
                while(len!=count)
                    pop_back();
                return;
            }
        if(count>len)
            {
                while(len!=count)
                    push_back(value);
            }
    }
    void merge( list & other ){
        if(size()==0)
            {
                swap(other);
                return;
            }
        else if(other.size()==0)
            return;
        iterator itl=begin();
        iterator itr=other.begin();
        while(itl!=end()&&itr!=other.end()){
            if((*itl) < (*itr))
                {
                    itl++;
                }
            else{
                    insert(itl,*itr);
                    itr++;
                }
        }
        while(itr!=other.end()){
            push_back(*itr);
            itr++;
        }
        other.clear();
    }
    template <class Compare>
    void merge( list & other, Compare comp ){
        if(size()==0)
            {
                swap(other);
                return;
            }
        else if(other.size()==0)
            return;
        iterator itl=begin();
        iterator itr=other.begin();
        while(itl!=end()&&itr!=other.end()){
            if(comp(*itl,*itr)==true){
                    itl++;
                    continue;
                }
            else{
                    insert(itl,*itr);
                    itr++;
                }
        }
        while(itr!=other.end()){
            push_back(*itr);
             itr++;
        }
        other.clear();
    }
    void splice( const_iterator pos, list& other ){
        for (iterator it=other.begin(); it !=other.end() ; ++it)
            insert(pos,*it);
        other.clear();
    }
    void splice( const_iterator pos, list& other, iterator it ){
            insert(pos,*it);
            other.erase(it);
    }
    void splice( const_iterator pos, list& other, const_iterator first, const_iterator last ){
        for (iterator it=first; it !=last ; ++it)
        {
            insert(pos,*it);
            other.erase(it);
        }
    }

    void remove(const_reference value){
        for (iterator it=begin(); it !=end();)
            if(*it==value)
                it=erase(it);
            else
                it++;
    }
    template <class UnaryPredicate>
    void remove_if(UnaryPredicate p){
        for (iterator it=begin(); it !=end();)
            if(p(*it)==true)
                it=erase(it);
            else
                it++;
    }
    void reverse(){
        for (iterator it=begin(); it !=end() ;it--)
        {
            node* temp;
            temp=(&it)->getper();
            (&it)->getper()=(&it)->getnex();
            (&it)->getnex()=temp;
        }
        node* temp;
        temp=head;
        head=tail;
        tail=temp;
        head->getper()=&gh;
        tail->getnex()=&gt;
    }
    void sort(){
        list carry;
        list count[64];
        int fill=1;
        while(!empty())
        {
            carry.splice(carry.begin(),*this,begin());
            int i=0;
            iterator it;
            while(i<fill&&!count[i].empty())
            {
                count[i].merge(carry);
                carry.swap(count[i++]);
            }
            carry.swap(count[i]);
            if(i==fill) ++fill;
        }
        for (int i = 1; i < fill; ++i)
                count[i].merge(count[i-1]);
            swap(count[fill-1]);
    }
    template< class Compare >
    void sort( Compare comp ){
        list carry;
        list count[64];
        int fill=1;
        while(!empty())
        {
            carry.splice(carry.begin(),*this,begin());
            int i=0;
            iterator it;
            while(i<fill&&!count[i].empty())
            {
                count[i].merge(carry,comp);
                carry.swap(count[i++]);
            }
            carry.swap(count[i]);
            if(i==fill) ++fill;
        }
        for (int i = 1; i < fill; ++i)
            count[i].merge(count[i-1],comp);
            swap(count[fill-1]);
    }
};
#endif