package main

import (
	"fmt"
	"sync"
	"time"
)

func Barber(visitors chan int, done chan int) {
	for {
		fmt.Println("Barber is sleeping")
		<-visitors
		time.Sleep(time.Second)
		fmt.Println("Visitor came, barber woke up and start work")
		time.Sleep(time.Second * 3)
		fmt.Println("Barber finish work")
		done<-0
	}
}

func Visitor(visitors chan int, done chan int, wg *sync.WaitGroup, ind int) {
	time.Sleep(time.Second)
	fmt.Println("Visitor " + string(ind) +" came and stay in queue")
	visitors<-ind
	var i =<-done
	fmt.Println("Visitor " + string(i) + " is serviced and leave barber")
	wg.Done()
}

func main()  {
	var visitors = make(chan int)
	var done = make(chan int)

	var wg sync.WaitGroup
	wg.Add(3)

	go Barber(visitors, done)
	go Visitor(visitors, done, &wg, 1)
	go Visitor(visitors, done, &wg, 2)
	go Visitor(visitors, done, &wg, 3)

	wg.Wait()
}
