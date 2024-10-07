Análise:

Adicionei logs para ações das threads.
No caso: Quer ler, lendo, terminou de ler
Quer escrever, escrevendo, terminou de escrever.

Ao analisar a saída do código, sempre que um log do tipo "quer escrever" acontecia, ele sempre vinha seguido de "escrevendo" e "terminou de escrever",sem nenhuma interrupção.
Um exemplo do terminal:

quer ler
lendo...
acabou de ler!
quer ler
lendo...
acabou de ler!
quer ler
lendo...
acabou de ler!
quer escrever!
escrevendo...
acabou de escrever!
quer ler
lendo...
acabou de ler!
quer ler
lendo...
acabou de ler!

Enfim, o problema é que em nenhum momento eu vi um caso em que vários "querem ler" simultanios aparecem, todas as vezes que uma thread pede o lock aparentemente ela consegue, o que é estranho, talvez o motivo seja pois a operação que essas threads fazem é muito rápida? deveria aparecer em algum lugar a sequência:
quer ler
lendo...
quer ler
quer ler
quer ler
acabou de ler!
lendo...
acabou de ler!
lendo...
acabou de ler!
lendo...
acabou de ler!

Ou algo do tipo, mas não localizei em meus vários testes com o log.

Mas tudo parece estar certinho, e a função está corretamente priorizando a escrita.
