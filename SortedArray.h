#ifndef SortedArray_H
#define SortedArray_H
#include <iostream>
#include <cassert>

/**
 * @brief Classe array dinamico ordinato
 * 
 * La classe implementa un'array dinamico ordinato e generico di oggetti T.
 * Gli oggetti dell'array sono ordinati con l'utilizzo del funtore C,
 * che prende due valori a e b e ritorna true se i valori sono nell'ordine corretto,
 * unito all'algoritmo di ordinamento insertion sort, efficiente per l'ordinamento di 
 * strutture dati già parzialmente ordinate.
 * 
 * 
 * @tparam T Tipo di dato all'interno dell'arrray
 * @tparam C Funtore di ordinamento
 */

template<typename T, typename C>
class SortedArray{

    public:

    typedef int size_type;
    typedef T value_type;
    typedef C comparison;

    /**
     * @brief Costruttore di default:
     * Crea un SortedArray vuoto di dimensione 0, da riempire attraverso la funzione push().
     * 
     */
    SortedArray(){
        _array = new value_type[0];
        _size = 0;

    };

    /**
     * @brief Distruttore 
     * 
     */
    ~SortedArray(){

        delete[] _array;
        _array = nullptr;
        _size = 0;
    }

    /**
     * @brief Copy constructor
     * 
     * @param other SortedArray da copiare
     */
    SortedArray(const SortedArray &other): _array(nullptr), _size(0) {

        try{
            _size = other.size();
            _array = new value_type[_size];
            for(int i = 0; i < _size; ++i){
                _array[i] = other._array[i];
            }

        } catch(...){
            delete[] _array;
            _array = nullptr;
            throw;
        }

    }

    /**
     * @brief Costruttore secondario che crea un SortedArray
     * riempito con gli elementi di un altro SortedArray generico.
     * 
     * @tparam A tipo del SortedArray da copiare   
     * @tparam B funtore di ordinamento del SortedArray da copiare
     * @param other 
     */
    template<typename A, typename B>
    explicit SortedArray(SortedArray<A, B> &other){
        typename SortedArray<A, B>::iterator it,ite;
        it = other.begin();
        ite = other.end();
        assert(ite > it);
        _size = ite - it;
            try{
                _array = new value_type[_size];
                unsigned int i = 0;
                for(; it != ite; ++it){
                    _array[i] = static_cast<value_type>(*it);
                    ++i;
                }
                sort();
            } catch(...){
                delete[] _array;
                _array = nullptr;
                _size = 0;
                throw;
            }
    }

    /**
     * @brief Operatore assegnamento
     * 
     * @param other SortedArray da copiare
     * @return SortedArray& reference all'array this
     */
    SortedArray& operator=(const SortedArray &other){

        if(this != &other){
            SortedArray tmp(other);
            this->toEmpty();
            try{
                for(int i = 0; i < tmp.size(); ++i){
                    this->push(tmp._array[i]);
                } 
            } catch(...){
                delete[] _array;
                _array = nullptr;
                throw;
            }
        }
        return *this;
    }

    /**
     * @brief Costruttore secondario che crea un SortedArray riempito con dati
     * presi da una sequenza di identificata da un iteratore di inizio ed uno di fine.
     * 
     * 
     * @tparam Iter tipo degli iteratori.
     * @param it iteratore di inizio.
     * @param ite iteratore di fine.
     */
    template <typename Iter> 
    explicit SortedArray(Iter it, Iter ite){
        assert(it < ite);
        _size = ite - it;
        try{
            _array = new value_type[_size];
            unsigned int i = 0;
            for(; it != ite; ++it){
                _array[i] = *it;
                ++i;
            }

            sort();

        } catch(...){
            delete[] _array;
            _array = nullptr;
            throw;
        }   
    }
    
    /**
     * @brief Aumenta la capacità dell'array, aggiunge l'elemento dato in input
     * ed infine chiama l'algoritmo di ordinamento sort(), mantenendo l'ordinamento indotto
     * dal funtore di tipo C.
     * 
     * @param element elemento da aggiungere all'array.
     */
    void push(const value_type element){
        try{
            value_type* tmp = new value_type[_size + 1];
            for ( int i = 0; i < _size; ++i){
                tmp[i] = _array[i];
            }

            tmp[_size] = element;
            ++_size;

            delete[] _array;
            _array = tmp;

            sort();
        
        } catch(...) {
                throw;
        }



    }

    /**
     * @brief 
     * Ordina gli elementi del SortedArray attraverso l'algoritmo insertion sort unito al funtore fornito dall'utente.
     * L'algoritmo di Insertion Sort ordina l'array progressivamente, inserendo ogni elemento
     * nella posizione corretta all'interno della parte ordinata dell'array.
     */
    void sort(){
        try {
            for (unsigned int i = 1; i < _size; ++i) {
                value_type aux = _array[i];
                int j = i - 1;
                while (j >= 0 && _cmp(aux, _array[j])) {
                    _array[j + 1] = _array[j];
                    --j;
                }
                _array[j + 1] = aux;
            }
        } catch (...) {
            delete[] _array;
            _array = nullptr;
            _size = 0;
            throw;
        }
    }

    /**
     * @brief Ritorna true se l'oggetto element è presente nell'array
     * 
     * @param element Oggetto di cui verificare la presenza
     * @return true 
     * @return false 
     */

    bool encountered(const value_type element) const {

        for(int i = 0; i < _size ; ++i)
            if(_array[i] == element){
                return true;
            }

        return false;      

    }

    /**
     * @brief Rimuove un elemento di tipo T dell'array. 
     * Se più elementi sono rimuovibili, elimina il primo.
     * 
     * @param element Elemento da rimuovere
     */
    void remove(const value_type element){

        bool encountered = false;

        for(int i = 0; i < _size ; ++i)
            if(_array[i] == element){
                encountered = true;
            }
        
        if(encountered){
            unsigned int slot = 0;
            encountered = false;

            try{
                value_type* tmp = new value_type[_size-1];

                for(int i = 0; i < _size; ++i){

                    if(_array[i] == element && !encountered){
                        encountered = true;
                    } else {
                        tmp[slot] = _array[i];
                        ++slot;
                    }

                }

                delete[] _array;
                _array = tmp;
                --_size;

            }catch(...) {
                throw;
            }
        } else return;

    }

    /**
     * @brief Svuota il SortedArray e riporta a 0 la sua dimensione.
     * 
     */
    void toEmpty(){
        value_type *tmp = new value_type[0];
        delete[] _array;
        _size = 0;
        _array = tmp;
    }

    /**
     * @brief Getter della capienza dell'array
     * 
     * @return size_type Capienza dell'array
     */
    size_type size() const{
        return _size;
    }

    /**
     * @brief Iteratore di tipo random access che itera gli elementi dell'array in ordine.
     * 
     */

	class iterator {
		//	
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef T*                       pointer;
		typedef T&                       reference;

	
		iterator() {
			ptr = nullptr;
		}
		
		iterator(const iterator &other) {
			ptr = other.ptr;
		}

		iterator& operator=(const iterator &other) {
			ptr = other.ptr;
            return *this;
		}

		~iterator(){}

		/**
		 * @brief Ritorna il dato riferito dall'iteratore (dereferenziamento).
         * Se il dato viene modificato, è necessario lanciare sort() per ripristinare l'ordinamento dell'array.
		 * 
		 * @return reference  Dato riferito dall'iteratore
		 */
		reference operator*() const {
			return *ptr;
		}

		/**
		 * @brief Ritorna il puntatore al dato riferito dall'iteratore
		 * 
		 * @return pointer puntatore al dato riferito dall'iteratore
		 */
		pointer operator->() const {
			return ptr;
		}

		/**
		 * @brief Operatore di accesso random.
         * Se il dato viene modificato, è necessario lanciare una sort() per ripristinare l'ordinamento dell'array.
		 * 
		 * @param index indice dell'elemento da ritornare
		 * @return reference
		 */
		reference operator[](const int index) {
			return ptr[index];
            
		}
		
		/**
		 * @brief Operatore di iterazione post-incremento.
		 * 
		 * @return iterator iteratore prima dell'incremento
		 */
		iterator operator++(int) {
		    iterator old(*this);
            ++ptr;
            return old;
		}

		/**
		 * @brief Operatore di iterazione pre-incremento.
		 * 
		 * @return iterator& iteratore incrementato
		 */
		iterator &operator++() {
			++ptr;
            return *this;
		}

		/**
		 * @brief Operatore di iterazione post-decremento.
		 * 
		 * @return iterator iteratore prima del decremento
		 */
		iterator operator--(int) {
			iterator old(*this);
            --ptr;
            return old;
		}

		/**
		 * @brief Operatore di iterazione pre-decremento.
		 * 
		 * @return iterator& iteratore decrementato
		 */
		iterator &operator--() {
			--ptr;
            return *this;
		}

		/**
		 * @brief Spostamento in avanti della posizione.
		 * 
		 * @param offset numero di posizioni di cui spostare l'iteratore
		 * @return iterator 
		 */
		iterator operator+(int offset) {
			return iterator(ptr + offset);
		}

		/**
		 * @brief Spostamento all'indietro della posizione.
		 * 
		 * @param offset numero di posizioni di cui spostare l'iteratore
		 * @return iterator 
		 */
		iterator operator-(int offset) {
			return iterator(ptr - offset);
		}
		
		/**
		 * @brief Spostamento in avanti della posizione.
		 * 
		 * @param offset numero di posizioni di cui spostare l'iteratore
		 * @return iterator& 
		 */
		iterator& operator+=(int offset) {
			ptr+=offset;
            return *this;
		}

		/**
		 * @brief Spostamento all'indietro della posizione.
		 * 
		 * @param offset numero di posizioni di cui spostare l'iteratore
		 * @return iterator& 
		 */
		iterator& operator-=(int offset) {
			ptr-=offset;
            return *this;
		}

		/**
		 * @brief Numero di elementi tra due iteratori.
		 * 
		 * @param other
		 * @return difference_type 
		 */
		difference_type operator-(const iterator &other) {
			return ptr-other.ptr;
		}
	
		/**
		 * @brief Operatore Uguaglianza.
		 * 
		 * @param other iteratore da confrontare 
		 * @return true 
		 * @return false 
		 */
		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		/**
		 * @brief Operatore diversità.
		 * 
		 * @param other iteratore da confrontare
		 * @return true 
		 * @return false 
		 */
		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}

		/**
		 * @brief Operatore maggiore.
		 * 
		 * @param other iteratore da confrontare
		 * @return true 
		 * @return false 
		 */
		bool operator>(const iterator &other) const {
			return ptr > other.ptr;
		}

        
		/**
		 * @brief Operatore maggiore uguale.
		 * 
		 * @param other iteratore da confrontare
		 * @return true 
		 * @return false 
		 */
		bool operator>=(const iterator &other) const {
			return ptr >= other.ptr;
		}


		/**
		 * @brief Operatore minore.
		 * 
		 * @param other iteratore da confrontare
		 * @return true 
		 * @return false 
		 */
		bool operator<(const iterator &other) const {
			return ptr < other.ptr;
		}
		
		

		/**
		 * @brief Operatore minore uguale.
		 * 
		 * @param other iteratore da confrontare
		 * @return true 
		 * @return false 
		 */
		bool operator<=(const iterator &other) const {
			return ptr <= other.ptr;
		}


	
	private:

		friend class SortedArray;
        value_type *ptr;

    /**
     * @brief  Costruttore privato di inizializzazione usato dalla classe container
     * 	       utilizzato tipicamente nei metodi begin e end.
     * 
     * @param array 
     */
		iterator(value_type *array) { 
            ptr = array;
		}
		
	};
	
    /**
     * @brief Ritorna un iteratore che punta all'inizio del SortedArray
     * 
     * @return iterator 
     */
	iterator begin() {
		return iterator(_array);
	}
	
	/**
	 * @brief Ritoran un iteratore che punta alla fine del SortedArray
	 * 
	 * @return iterator 
	 */
	iterator end() {
		return iterator(_array + _size);
	}

    /**
     * @brief Rimuove gli elementi dell'array che soddisfano la condizione F data in input come funtore.
     * 
     * 
     * @tparam F 
     * @param parameter 
     */

    template<typename F>
    void filter(F parameter){

        SortedArray<value_type, comparison> aux;
        for(unsigned int i = 0; i < _size; ++i){
            if(parameter(_array[i])){
                aux.push(_array[i]);
            }
        }
        for(unsigned int i = 0; i <aux.size(); ++i){
            remove(aux._array[i]);
        }
    }

    /**
     * @brief Operatore di stream per SortedArray.
     * Stampa a video gli elementi dell'array secondo l'ordine definito dall'utente e la capacità attuale. 
     * 
     * @param os 
     * @param arr 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream &os, const SortedArray<value_type, comparison> &arr) {
        os << "Capacità: " <<  arr.size() << std::endl;
        os << "Elementi in ordine: ";
        for(int i = 0; i < arr.size(); ++i){
            std::cout << arr._array[i] << " ";
        }
        std::cout << std::endl;
        return os;
    }


    private:


    value_type *_array;
    size_type _size;
    comparison _cmp;

};

#endif