//introduz canais na aplicação Go
package main

import (
	"fmt"
)

func tarefa(str chan string) {
	var msg = " "
	msg = <- str
	fmt.Println(msg)
	//escreve no canal
	str <- "Oi main, Bom dia, tudo bem?"
	msg = <- str
	fmt.Println(msg)
	str <- "Certo, entendido!"
	msg = <- str
	fmt.Println(msg)
	str <- "Finalizando"
}

func main() {
	var msg = "" //string vazia
	
	//cria um canal de comunicacao nao-bufferizado
	str := make(chan string)

	//cria um goroutine que executará a função 'tarefa'
	go tarefa(str)

	str <- "Olá Goroutina, bom dia!"

	//lê do canal
	msg = <-str

	fmt.Println(msg)

	str <- "Tudo bem! Vou finalizar agora tá?"

	msg = <-str

	fmt.Println(msg)

	str <- "Finalizando"
	msg = <- str
	fmt.Println(msg)
	
}
