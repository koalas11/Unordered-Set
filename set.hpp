/**
  @file set.hpp

  @brief File header della classe set templata

  File di dichiarazioni/definizioni della classe set templata
*/

#ifndef SET_HPP
#define SET_HPP

#include <algorithm> // std::swap
#include <iostream> // std::ostream
#include <cassert> // assert
#include <fstream> // std::ofstream
#include <string> // std::string

#define MAX_RESIZE 200

/**
  @brief classe set ordinata

  La classe implementa un generico set di oggetti T.
*/
template <typename T, typename Equal>
class set {
public:
    /**
        TypeDef del tipo contenuto nel set
    */
    typedef T value_type;
    typedef unsigned int size_type;
private:
    Equal _eql;
    value_type* _array;
    size_type _capacity;
    size_type _size;

    /**
        @brief Funzione di supporto che aumenta/diminuisce 
        la capacità del set con un valore massimo di aumento

        @param size possibile nuova capacità del set

        @post _array != nullptr
        @post _capacity != _capacity
        @post _size != _size

        @throw std::bad_alloc possibile eccezione di allocazione
    */
    void resize(size_type size) {
        assert(size >= 0);
        if (size > _capacity + MAX_RESIZE)
            size = _capacity + MAX_RESIZE;
        if (_size > size)
            size = _size;
        if (size == 0) {
            clear();
            return;
        }

        set tmp(size);

        for (size_type i = 0; i < _size; ++i)
            tmp.add(_array[i]);
        
        this->swap(tmp); 
    }

public:
    /**
        @brief Costruttore di default.

        @post _array == nullptr
        @post _capacity == 0
        @post _size == 0
    */
    set() : _array(nullptr), _capacity(0), _size(0) {}

    /**
        @brief Costruttore secondario.

        @param capacity capacità del set

        @post _array != nullptr
        @post _capacity == capacity
        @post _size == 0

        @throw std::bad_alloc possibile eccezione di allocazione
    */
    explicit set(size_type capacity) : _array(nullptr), _capacity(0), _size(0) {
        assert(capacity >= 0);
        _array = new value_type[capacity];
        _capacity = capacity;
    }

    /**
        @brief Copy constructor.

        @param other set da copiare

        @post _array != nullptr
        @post _capacity == other._capacity
        @post _size == other._size

        @throw std::bad_alloc possibile eccezione di allocazione
    */
    set(const set &other) : _array(nullptr), _capacity(0), _size(0) {
        try {
            value_type* tmp = new value_type[other._capacity];
            _capacity = other._capacity;

            for (size_type i = 0; i < other._size; ++i)
                tmp[i] = other._array[i];

            _array = tmp;
            _size = other._size;
        } catch(...) {
            clear();
            throw;
        }
    }

    /**
        @brief Operatore di assegnamento.

        @param other set da copiare

        @return reference alla set this
        
        @throw std::bad_alloc possibile eccezione di allocazione
    */
    set& operator=(const set &other) {
        if (this != &other) {
            set tmp(other);
            this->swap(tmp); 
        }

        return *this;
    }

    /**
        @brief Costruttore che crea un set riempita con dei dati
        presi da una sequenza identificata da un iteratore di 
        inizio e uno di fine. Gli iteratori possono essere di
        qualunque tipo. 

        @param begin iteratore di inizio sequenza
        @param end iteratore di fine sequenza

        @throw std::bad_alloc possibile eccezione di allocazione
    */
    template <typename Iter>
    set(Iter begin, Iter end) : _array(nullptr), _capacity(0), _size(0) {
        Iter curr = begin;
        try {
            for(; curr!=end; ++curr) 
                add(static_cast<value_type>(*curr));
        } catch(...) {
            clear();
            throw;
        }
    }

    /**
        @brief Distruttore e dealloca la memoria allocata.

        @post _array == nullptr
        @post _capacity == 0
        @post _size == 0
    */
    ~set() {
        clear(); 
    }

    /**
        @brief Funzione che svuota il set e dealloca la memoria allocata.

        @post _array == nullptr
        @post _capacity == 0
        @post _size == 0
    */
    void clear(void) {
        delete[] _array;
        _array = nullptr;
        _capacity = 0;
        _size = 0;
    }

    /**
        @brief Funzione che ritorna quanti elementi può contenere il set.

        @return numero che rappresenta la capacità del set
    */
    size_type capacity(void) const {
        return _capacity;
    }

    /**
        @brief Funzione che ritorna il numero degli elementi del set.

        @return numero degli elementi nel set
    */
    size_type size(void) const {
        return _size;
    }

    /**
        @brief Funzione scambia lo stato tra l'istanza corrente di
        set e quella passata come parametro.

        @param other set con cui scambiare lo stato
    */
    void swap(set &other) {
        std::swap(_array, other._array);
        std::swap(_capacity, other._capacity);
        std::swap(_size, other._size);
        std::swap(_eql, other._eql);
    }

    /**
        @brief Operatore getter di una cella dell'array del set.

        @param index della cella da leggere
        @return reference costante all'elemento da leggere

        @pre index >= 0
        @pre index < _size
    */
    const value_type& operator[](const size_type index) const {
        assert(index >= 0);
        assert(index < _size);
        return _array[index];
    }

    /**
        @brief Funzione che aggiunge un elemento al set.

        @param value reference costante dell'elemento da aggiungere

        @return true se aggiunto con successo, false altrimenti

        @throw std::bad_alloc possibile eccezione di allocazione
    */
    bool add(const value_type &value) {
        if (!contains(value)) {
            if (_capacity == 0)
                resize(1);
            else if (_capacity == _size)
                resize(_capacity * 2);
            _array[_size++] = value;
            return true;
        }
        return false;
    }

    /**
        @brief Funzione che rimuove un elemento al set.

        @param value reference costante dell'elemento da rimuovere

        @return true se rimosso con successo, false altrimenti

        @throw std::bad_alloc possibile eccezione di allocazione
    */
    bool remove(const value_type &value) {
        for (size_type i = 0; i < _size; ++i) {
            if (_eql(_array[i], value)) {
                std::swap(_array[i], _array[--_size]);

                if (_capacity / 2 >= _size)
                    resize(_capacity * 3 / 4);

                return true;
            }
        }
        return false;
    }

    /**
        @brief Funzione che controlla la presenza di un elemento.

        @param value reference costante dell'elemento da controllare

        @return true se l'elemento è presente nel set, false altrimenti
    */
    bool contains(const value_type &value) const {
        for (size_type i = 0; i < _size; ++i) {
            if (_eql(_array[i], value))
                return true;
        }
        return false;
    }

    /**
        @brief Funzione che controlla se due set sono uguali (contengolo gli stessi elementi).

        @param set reference costante del set da controllare

        @return true se i set contengolo gli stessi elementi, false altrimenti
    */
    bool operator==(const set &other) const {
        if (this->_size != other._size)
            return false;
        
        for (size_type i = 0; i < _size; i++) {
            if (!this->contains(other[i]))
                return false;
        }
        
        return true;
    }

    /**
        TypeDef dell'iteratore Costante
    */
    typedef const value_type* const_iterator;

    /**
        @brief Funzione che ritorna l'iteratore all'inizio della sequenza dati.

        @return iteratore all'inizio della sequenza dati
    */
    const_iterator begin(void) const {
        return _array;
    }

    /**
        @brief Funzione che ritorna l'iteratore alla fine della sequenza dati.

        @return iteratore alla fine della sequenza dati
    */
    const_iterator end(void) const {
        return _array + _size;
    }

    /**
        @brief Funzione GLOBALE che implementa l'operatore di stream.
        La funzione è templata sul set ed è messa
        friend perchè accediamo ai dati privati di set.

        @param os stream di output
        @param ol set da spedire sullo stream

        @return lo stream di output
    */
    friend std::ostream& operator<<(std::ostream &os, const set &ol) {
        os << ol._size;

        for (size_type i = 0; i < ol._size; ++i) {
            os << " (" << ol._array[i] << ")";
        }

        return os;
    }
};

/**
    @brief Funzione GLOBALE che applica ad ogni elemento
    un predicato passato come parametro e restituisce
    il set con gli elementi il cui predicato restituisce true

    @param setToFilter set su cui applicare il predicato
    @param predicate predicato da applicare ad ogni elemento del set

    @return il set con gli elementi che soddisfano il predicato

    @throw std::bad_alloc possibile eccezione di allocazione
    @throw possibile eccezione dal predicato
*/
template<typename T, typename Equal, typename Predicate>
set<T, Equal> filter_out(const set<T, Equal> &setToFilter, const Predicate &predicate) {
    set<T, Equal> tmp;
    typename set<T, Equal>::const_iterator currIter = setToFilter.begin();

    for (; currIter != setToFilter.end(); ++currIter) {
        if (predicate(*currIter))
            tmp.add(*currIter);
    }
    return tmp;
}

/**
    @brief Funzione GLOBALE che ritorna il set con gli elementi
    appartenenti a tutti e due i set (concatenazione dei set)

    @param lhs set di sinistra
    @param rhs set di destra

    @return il set con gli elementi comuni ai due set

    @throw std::bad_alloc possibile eccezione di allocazione
*/
template<typename T, typename Equal>
set<T, Equal> operator+(const set<T, Equal> &lhs, const set<T, Equal> &rhs) {
    set<T, Equal> tmp = lhs;

    typename set<T, Equal>::const_iterator currIter = rhs.begin();
    for (; currIter != rhs.end(); ++currIter)
        tmp.add(*currIter);

    return tmp;
}

/**
    @brief Funzione GLOBALE che ritorna il set con gli elementi
    comuni a tutti e due i set (intersezione dei set)

    @param lhs set di sinistra
    @param rhs set di destra

    @return il set con gli elementi comuni ai due set
    
    @throw std::bad_alloc possibile eccezione di allocazione
*/
template<typename T, typename Equal>
set<T, Equal> operator-(const set<T, Equal> &lhs, const set<T, Equal> &rhs) {
    set<T, Equal> tmp;

    typename set<T, Equal>::const_iterator currIter = rhs.begin();
    for (; currIter != rhs.end(); ++currIter)
        if (lhs.contains(*currIter))
            tmp.add(*currIter);

    return tmp;
}

/**
    @brief Funzione GLOBALE che scrive su un file passato
    come stringa il set passato di tipo string

    @param set set da scrivere su un file
    @param file file su cui scrivere

    @throw possibile eccezione dalla scrittura su file
*/
template<typename Equal>
void save(const set<std::string, Equal> &set, const std::string &file) {
    std::ofstream FILE;
    try {
        FILE.open(file);

        FILE << set;

        FILE.close();
    } catch(...) {
        if (FILE.is_open())
            FILE.close();
        throw;
    }
}

#endif // SET_HPP
