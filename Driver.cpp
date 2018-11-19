// File: test5.cpp
//
// Tests copy constructor, destructor and assignment operator
//
// Should test this with valgrind
//

#include <iostream>
using namespace std ;

#include "LazyBST.h"

int main() {

  LazyBST T1 ;

  T1.insert(14) ;

  T1.insert( 7) ;
  T1.insert(25) ;

  T1.insert( 3) ; T1.insert(32) ; 
  T1.insert( 9) ; T1.insert(18) ; 

  T1.insert( 1) ; T1.insert(44) ;
  T1.insert(12) ; T1.insert(15) ; 
  T1.insert( 4) ; T1.insert(29) ; 
  T1.insert(10) ; T1.insert(21) ;

  cout << "Original T1:         " ;
  T1.inorder() ; cout << endl ;

  // Use copy constructor
  LazyBST *Tptr = new LazyBST(T1) ;

  cout << "Copied T1:           " ;
  Tptr->inorder() ; cout << endl; 
   
  LazyBST T2 ;

  T2.insert(50) ;
  T2.insert(25) ; T2.insert(75) ;
  // T2.inorder() ; cout << endl ;

  T2 = *Tptr ;
  cout << "Second copy:         " ;
  T2.inorder() ; cout << endl ; 

  cout << "Delete first copy...\n" ;
  delete Tptr ;

  cout << "Recheck original:    " ;
  T1.inorder() ; cout << endl ;
  cout << "Recheck second copy: " ;
  T2.inorder() ; cout << endl ; 

  LazyBST T ;

  T.insert(14) ;

  T.insert(7) ;
  T.insert(25) ;

  T.insert(3) ; T.insert(32) ; 
  T.insert(9) ; T.insert(18) ; 

  T.insert(1) ; T.insert(44) ;
  T.insert(12) ; T.insert(15) ; 
  T.insert(4) ; T.insert(29) ; 
  T.insert(10) ; T.insert(21) ;

  T.inorder() ; cout << endl ;

  cout << "removing ..." << endl; 
  //   T.dump() ;

  int n ;

  n = 44 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 29 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 12 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 10 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  


  T.insert(70) ;
  T.inorder() ; cout << endl ;

  T.insert(30) ;
  T.inorder() ; cout << endl ;

  T.insert(110) ;

  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 40 *****\n" ;
  T.insert(40) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 20 *****\n" ;
  T.insert(20) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 41 *****\n" ;
  T.insert(41) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 31 *****\n" ;
  T.insert(31) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 32 *****\n" ;
  T.insert(32) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 33 *****\n" ;
  T.insert(33) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 19 *****\n" ;
  T.insert(19) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 34 *****\n" ;
  T.insert(34) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 15 *****\n" ;
  T.insert(15) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 14 *****\n" ;
  T.insert(14) ;
  T.inorder() ; cout << endl ;

  cout << "Check out locate() function: " << endl;

  int key = 9999 ;
  bool ans ;
  const char *str ;

  ans = T1.locate(str="", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T1.locate(str="LL", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T1.locate(str="LLR", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T1.locate(str="RLLR", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  cout << "Check out find() function: " << endl;
  

  n = 3  ;
  cout << "Find " << n << endl ;
  if ( T1.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;

  n = 13  ;
  cout << "Find " << n << endl ;
  if ( T1.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;

  n = -100 ;
  cout << "Find " << n << endl ;
  if ( T1.find(-100) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;
  

  return 0;
}
