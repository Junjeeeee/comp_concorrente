Respostas:

Atividade 1, pt2: A main finalizou antes das outras Goroutinas darem oi, isso ocorreu pois a main não esperou as outras Goroutinas terminarem, nem esperou um tempo determinado, como 1 segundo, por exemplo.

Atividade 2: pt2: Pois a main esperou chegar uma mensagem no canal antes de prosseguir.
pt3: A main finalizou sem receber a mensagem da Goroutina,e,muitas vezes, sem nem deixar a Goroutina terminar. Isto ocorre devido a pt2, sem a main ter que esperar uma mensagem chegar, ela continua em frente até finalizar.

Atividade 3: pt2: A finalidade do canal Jobs é guardar os jobs que a goroutina deve realizar, e o canal done é indicar se todos os trabalhos foram finalizados.
pt3: A main irá finalizar sem deixar nenhum job finalizar.

Atividade 4: Alterei essa linha dentro do comando select:     case <-time.After(3 * time.Second):
Antes ele esperava 2 segundos, agora espera 3, o que é mais que suficiente pro primeiro resultado aparecer (ele demora 2s pra colocar result1 no c1).
