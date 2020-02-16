Pokorně jsem si dovolil pokračovat v odkazu mistra Johnny Leeta, avšak je mi jasné,
že míře jeho génia se nikdy nebudu moci rovnat. Mohu nicméně uctít jedinečný rukopis 
mistra a převzít jeho alergii na dynamické alokace a pointery za svou. Plně souhlasím
s jeho názorem, že pokaždé, když někdo mezi framy použije operator new, Bůh zabije koťátko.

I tedy zkusil jsem postavit jednoduchý, ale stále pomeřně obecný engine záměrně 
s co nejméně alokacemi a zjistit, jak daleko se dá až zajít. Ukázalo se, že docela daleko :) 
std::deque a její garance validity referencí by si jistě s Johnnym okamžitě porozumněla!
Mohl jsem si sice napsat vlastní heap alokátor, ale co by na to řekl mistr! Nemohu ho
takto zklamat.

Pro Q&A playtest jsem musel použít svého kocoura jelikož publisher tlačil na termín. Grafici
stávkovali po posledním crunchi a zvukař se ještě nevrátil z poslední trance párty, takže
pro vývoj bylo potřeba se spokojit s existujícími assety i pro zvukové efekty. Cinematics
mám slíbené jakmile vyvolám location scouting fotky, ale středeční orkán ohnul na hvězdárně
dalekohled. Prostě standardní vývoj.

° Ondřej Dobiáš

PS: Commitoval jsem vše od začátku do gitu, takže timeframe vývoje můžete rekonstruovat
zde: https://github.com/DeirhX/SpaceInvador. 3 večery, v pátek v průběhu C++ Committee, 
pak dva dny víkendu. Repo pak udělám zas private, ať nikomu nenapovídá.
 

