package main

import (
    "fmt"
	"math"
)


func ehPrimo(n int) bool {
	if n<=1{
		return false
	} 
	if n==2 {
		return true
	}
	if n%2==0 {
		return false
	}
	for i:=3; i< int(math.Sqrt(float64(n)))+1; i+=2{
		if n%i==0 {
			return false
		}
	}
	return true
}

func verificaPrimo(ch chan int, result chan int) {
	for{
		num := <-ch
		if num == -1 {
            close(ch)
            return
        }
        if ehPrimo(num){
            result <- 1
        } else{
			result <- 0
		}
	}
}

func main() {
	var n, m int

    fmt.Print("Digite a quantidade de elementos da lista e o numero de threads: ")
    _, err := fmt.Scan(&n, &m)
    if err != nil {
        fmt.Println("Erro ao ler os números:", err)
        return
    }

	quantidade := 0;

	thread_atual := 0;

	channels := make([]chan int, m)
	result := make(chan int)

	for i := 0; i < m; i++ {
        channels[i] = make(chan int,(n/m) +1)
		go verificaPrimo(channels[i], result)
    }

	for i := 1; i<=n;i++{
		channels[thread_atual] <- i
		thread_atual = (thread_atual + 1) % m
	}
	for i := 0; i<m;i++{
		channels[i] <- -1
	}

	for i:= 0; i< n; i++{
		quantidade += <- result
	} 
	close(result)


	fmt.Println("A quantidade de primos é: ", quantidade)

}

