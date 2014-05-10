#ifndef			__INIT_HPP__
#define			__INIT_HPP__

void analizeProduct(FILE * f) ;
void getFirstSet();
void getFollowSet();
void init() ;

ItemSet closure(ItemSet I) ;
ItemSet _goto(ItemSet I, char X) ;
void buildItemSetClue () ;
void getActionTable() ;

#endif
