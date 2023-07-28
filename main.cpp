#include "SortedArray.h"
#include <cassert>
#include <vector>
#include <iterator>
/**
 * @brief Funtore di confronto tra interi: utilizzato per stabilire un ordine crescente
 * all'interno di un SortedArray.
 * 
 */
struct int_crescent {
  bool operator()(int a, int b) const {
    return a<b;
  }
};

/**
 * @brief Funtore di confronto tra interi: utilizzato per stabilire un ordine decrescente
 * all'interno di un SortedArray.
 * 
 */
struct int_decrescent {
  bool operator()(int a, int b) const {
    return a>b;
  }
};

/**
  @brief Funtore predicato 

  Ritorna true se il valore intero passato è pari 
*/
struct is_even {
  bool operator()(int a) const {
    return (a % 2 ==0);
  }
};


/**
 * @brief Tipo Custom contenente una coppia chiave-valore.
 * Utilizzata per il test su tipi custom.
 * 
 */
struct keyValuePair{

  keyValuePair(int k, char v): key(k), value(v) {};
  keyValuePair(): key(0), value('0'){};

/**
 * @brief Operatore maggiore.
 * Confronta la chiave di due keyValuePair e ritorna true se la chiave di *this è maggiore.
 * 
 * @param other 
 * @return true 
 * @return false 
 */
  bool operator>(keyValuePair &other){
    return key > other.key;
  }

/**
 * @brief Operatore minore.
 * Confronta la chiave di due keyValuePair e ritorna true se la chiave di *this è minore.
 * 
 * @param other 
 * @return true 
 * @return false 
 */
  bool operator<(keyValuePair &other){
    return key < other.key;
  }

/**
 * @brief Operatore uguale.
 * Confronta le variabili key e value di due keyValuePair, e ritorna true
 * se combaciano.
 * 
 * @param other 
 * @return true 
 * @return false 
 */
  bool operator==(keyValuePair other){
    if(key == other.key && value == other.value){
      return true;
    }
    return false;
  }

  public:
    int key;
    char value;
    

};

/**
 * @brief Operatore di stream per keyValuePair.
 * Stampa a video i valori di key e value.
 * 
 * @param os 
 * @param kvp 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const keyValuePair& kvp) {
    os << "Key: " << kvp.key << ", Value: " << kvp.value;
    return os;
}

/**
 * @brief Funtore di confronto tra oggetti di tipo keyValuePair.
 * Effettua il confronto utilizzando l'operatore > della struct.
 * 
 */
struct kv_crescent{
  bool operator()(keyValuePair a, keyValuePair b) const {
    return a > b;
  }
};

void testPush(){
  std::cout << "testPush" << std::endl << std::endl;

  SortedArray<char, int_decrescent> arr;
  arr.push('k');
  arr.push('b');
  arr.push('c');
  arr.push('a');

  std::cout << "Risultato post-push: " << std::endl << arr;

  std::cout << std::endl;
}

void testRemove(){

  std::cout << "testRemove" << std::endl << std::endl;

  SortedArray<int, int_decrescent> arr;
  arr.push(4);
  arr.push(5);
  arr.push(3);
  arr.push(1);
  arr.push(2);

  std::cout << "Stato array prima delle remove degli elementi: " << std::endl;

  arr.remove(4);
  arr.remove(1);
  arr.remove(3);
  arr.remove(9);

  std::cout << "Risultato testRemove: " << std::endl << arr <<std::endl;   
  std::cout << std::endl;
}

/**
 * @brief Test degli iteratori della classe
 * 
 */
void testIteratori(){

  std::cout << "testIteratori" << std::endl << std::endl;
  SortedArray<char, int_decrescent> arr;
  SortedArray<char, int_decrescent>::iterator it, ite;
  arr.push('k');
  arr.push('b');
  arr.push('c');
  arr.push('a');

  std::cout << "Stato array" << std::endl << arr;

  it = arr.begin();
  std::cout << "Operatore[]: " << it[3] << " ";
  *it = 'f';
  arr.sort();
  ite = arr.end();

  std::cout << "Iterazione array: ";
  for(; it != ite; ++it){
      std::cout << *it << "  ";
  }

  it = arr.begin();
  assert((it+=1) == ++it);

  it = arr.begin();
  ite = arr.begin();
  it+=3;
  assert(*it == ite[3]);

  it = ite;
  assert(it == ite);

  it = ite + 1;
  assert(it > ite);
  assert(ite < it);




  std::cout << std::endl;

  std::cout << std::endl;
    
}

void testAssegnamento(){
  SortedArray<int, int_crescent> arr;
  SortedArray<int, int_crescent> arr2;
  SortedArray<int, int_crescent>::iterator it,ite, it2, ite2;

  std::cout << "testAssegnamento" << std::endl << std::endl;

  arr.push(2);
  arr2.push(3);
  arr2.push(1);
  arr2.push(6);
  arr = arr2;
  it = arr.begin();
  ite = arr.end();
  it2 = arr2.begin();
  ite2 = arr2.end();

  for(; it != ite; ++it){
    assert(*it == *it2);
    ++it2;
  }

  std::cout << std::endl;

}

/**
 * @brief Test del costruttore secondario SortedArray(Iter it, Iter ite) che ha come input un iteratore di inizio(it) ed uno di fine(ite).
 * 
 */
void testCostruttoreIteratori(){

  std::cout << "testCostruttoreIteratori" << std::endl << std::endl;

  std::vector<int> v {4,5,3,2,6,7};

  std::vector<int>::iterator it,ite;
  it = v.begin();
  ite = v.end();

  SortedArray<int,int_crescent> arr(it,ite);

  std::cout << arr;

  std::cout << std::endl;

}

/**
 * @brief Test del costruttore secondario SortedArray(SortedArray<A, B> &other) che prende in input un SortedArray generico.
 * 
 */
void testCostruttoreSecondario(){

  std::cout << "testCostruttoreSecondario" << std::endl << std::endl;

  SortedArray<char, int_crescent> arr;

  arr.push('a');
  arr.push('b');
  arr.push('c');

  std::cout << "Stato dell'array generico: " << std::endl << arr;
  
  std::cout << "Il cast di a: " << static_cast<int>('a') << std::endl;
  std::cout << "Il cast di b: " << static_cast<int>('b') << std::endl;
  std::cout << "Il cast di c: " << static_cast<int>('c') << std::endl;

  SortedArray<int, int_decrescent> arr2(arr);

  std::cout << "Stato dell'array creato con il costruttore secondario: " << std::endl << arr2;

  std::cout << std::endl;

}

/**
 * @brief Test della funzione filter(F parameter),
 *  che rimuove gli elementi dell'array che rispettano la soddisfano parameter.
 * 
 */
void testFilter(){

  std::cout << "testFilter" << std::endl << std::endl;

  SortedArray<int, int_decrescent> arr;
  arr.push(4);
  arr.push(5);
  arr.push(3);
  arr.push(1);
  arr.push(2);
  arr.push(6);
  arr.push(8);
  arr.push(2);
  arr.push(2);
  arr.push(2);
  arr.push(2);

  std::cout << "Stato array prima della funzione: " << std::endl << arr;

  is_even ie;

  arr.filter(ie);  

  std::cout << "testFilter: stato array dopo la funzione (rimozione interi pari): " << std::endl << arr;    

  std::cout << std::endl;

}

/**
 * @brief Test della funzione encountered(const value_type element)
 * 
 */
void testEncountered(){

  std::cout << "testEncountered" << std::endl << std::endl;

  SortedArray<char, int_crescent> arr;
  arr.push('T');
  arr.push('c');
  arr.push('f');
  assert(arr.encountered('T'));
  assert(arr.encountered('c'));
  arr.remove('f');
  assert(!arr.encountered('f'));


}

/**
 * @brief Test delle funzioni sul tipo custom keyValuePair, 
 * una struct contenente una coppia chiave valore.
 * 
 */
void testCustom(){

  std::cout << "testCustom" << std::endl << std::endl;

  keyValuePair p1(1, 'd');
  keyValuePair p2(3, 'c');
  keyValuePair p3(12, 'f');
  keyValuePair p4(6, 's');

  SortedArray<keyValuePair, kv_crescent> arr;
  arr.push(p1);
  arr.push(p2);
  arr.push(p3);
  arr.push(p4);

  assert(arr.encountered(p1));

  std::cout << "Array riempito con push: " << std::endl << arr;

  SortedArray<keyValuePair, kv_crescent> arr2(arr);

  std::cout << "Array creato con copy constructor: " << std::endl << arr2; 

  SortedArray<keyValuePair, kv_crescent> arr3;
  
  arr3 = arr2;

  std::cout << "Array riempito con l'operatore assegnamento: " << std::endl << arr3;

  SortedArray<keyValuePair, kv_crescent>::iterator it, ite;
  it = arr3.begin();
  ite = arr3.end();

  SortedArray<keyValuePair, kv_crescent> arr4(it,ite);

  std::cout << "Array riempito con il costruttore con iteratori: " << std::endl << arr4; 

  arr4.remove(p2);

  std::cout << "Array dopo la remove di un elemento: " << arr4;
  
  arr4.toEmpty();

  std::cout << "Array dopo essere svuotato: " << arr4;

  
  std::cout << std::endl;



}



int main(int argc, char* argv[]){

    testPush();
    testRemove();
    testIteratori();
    testAssegnamento();
    testCostruttoreIteratori();
    testCostruttoreSecondario();
    testFilter();
    testEncountered();
    testCustom();
}