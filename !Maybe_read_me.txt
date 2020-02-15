Pokorně jsem si dovolil pokračovat v odkazu mistra Johnny Leeta, avšak je mi jasné,
že míře jeho génia se nikdy nebudu moci rovnat. Mohu nicméně uctít jedinečný rukopis 
mistra a převzít jeho alergii na dynamické alokace a pointery za svou. Plně souhlasím
s jeho názorem, že pokaždé, když někdo mezi framy použije operator new, Bůh zabije koťátko.

I tedy zkusil jsem postavit jednoduchý, ale stále pomeřně obecný engine záměrně 
s co nejméně alokacemi a zjistit, jak daleko se dá až zajít. Ukázalo se, že docela daleko :) 
std::deque a její garance validity referencí by si jistě s Johnnym okamžitě porozumněla!
Mohl jsem si sice napsat vlastní heap alokátor, ale co by na to řekl mistr! Takto ho 
zklamat nemohu.

