package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var array [5]int

type CyclicBarrier struct {
	generation int
	count      int
	parties    int
	trigger    *sync.Cond
}

func (b *CyclicBarrier) nextGeneration() {
	//...
	b.trigger.Broadcast()
	b.count = b.parties
	//...
	b.generation++
}
func (b *CyclicBarrier) Awaiting() {
	b.trigger.L.Lock()
	defer b.trigger.L.Unlock()

	generation := b.generation

	b.count--
	index := b.count
	if index == 0 {
		b.nextGeneration()
	} else {
		for generation == b.generation {
			//...
			b.trigger.Wait()
		}
	}
}
func NewCyclicBarrier(numberOfParties int) *CyclicBarrier {
	b := CyclicBarrier{}
	b.count = numberOfParties
	b.parties = numberOfParties
	b.trigger = sync.NewCond(&sync.Mutex{})
	return &b
}

func dispatch(wgControl *sync.WaitGroup, f func()) {
	wgControl.Add(1)
	go func() {
		f()
		wgControl.Done()
	}()
}

func process(name string, line [4][10]string, cyBarrier *CyclicBarrier) {
	for {

		rndNum := rand.Intn(10)
		rndSym := rand.Intn(4)
		a := 0
		b := 0
		if name == "B" {
			b = 1
		} else if name == "C" {
			b = 2
		} else if name == "D" {
			b = 3
		}
		line[b][rndNum] = string('A' + rndSym)
		for i := 0; i < 10; i++ {
			if line[b][i] == "A" || line[b][i] == "B" {
				a++
			}
		}
		array[b] = a
		time.Sleep(time.Millisecond * 1000)
		fmt.Printf("named:%q in generation is done   line:%q    num:%d\n", name, line[b], a)
		if cyBarrier.count == 1 {
			fmt.Printf("\n------\ngeneration is ready (i.e. cyBarrier is reset):\n\n")

			if (array[0] == array[1] && array[0] == array[2]) || (array[0] == array[1] && array[0] == array[3]) ||
				(array[1] == array[2] && array[1] == array[3]) {
				fmt.Print("DONE")
				break
			}
		}
		cyBarrier.Awaiting()
	}
}


func main() {
	wgControl := &sync.WaitGroup{}
	defer wgControl.Wait()

	parties := 4
	cyBarrier := NewCyclicBarrier(parties)

	lines := [4][10]string{
		{"A","A","A","A","B","B","B","C","C","D"},
		{"A","A","A","B","B","C","C","C","D","D"},
		{"A","A","B","C","C","C","D","D","D","D"},
		{"A","B","B","D","B","C","C","D","D","D"}}

	for i := 0; i < parties; i++ {
		name := string('A' + i)
		dispatch(wgControl, func() {go process(name, lines, cyBarrier) })
	}
	time.Sleep(time.Millisecond * 100000)
}