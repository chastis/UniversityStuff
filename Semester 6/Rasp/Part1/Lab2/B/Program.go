package main

import (
	"fmt"
	"time"
)


func Ivanov(value int, input chan int) {
	chanel1 := make(chan int)
	go Petrov(chanel1, input)
	fmt.Println("Ivanov: START")
	time.Sleep(time.Second * 3)
	fmt.Println("Ivanov: END")
	chanel1 <- value + 1
}

func Petrov(c chan int, input chan int) {
	chanel2 := make(chan int)
	fmt.Println("Petrov: WAITING")
	go Necheporchuk(chanel2, input)
	var x = <-c
	fmt.Println("Petrov: START")
	time.Sleep(time.Second * 3)
	fmt.Println("Petrov: END")
	chanel2 <- x + 1
}

func Necheporchuk(c chan int, input chan int) {
	fmt.Println("Necheporchuk: WAITING")
	var x = <-c
	fmt.Println("Necheporchuk: START")
	time.Sleep(time.Second * 3)
	fmt.Println("Necheporchuk: END")
	input <- x + 1
}

func main() {
	var input = make(chan int)
	go Ivanov(10, input)
	fmt.Println(<-input)
}
