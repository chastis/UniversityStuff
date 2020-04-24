package main

import (
	"fmt"
	"math/rand"
	"os"
	"strings"
	"sync"
	"time"
)

func gardener(garden [][]string, m *sync.RWMutex) {
	for {
		m.RLock()
		for i := 0; i < 5; i++ {
			for j := 0; j < 5; j++ {
				if garden[i][j] == "1" {
					garden[i][j] = "0"
				}
			}
		}
		m.RUnlock()
		time.Sleep(2100 * time.Millisecond)
	}
}

func nature(garden [][]string, m *sync.RWMutex) {
	rand.Seed(time.Now().UTC().UnixNano())
	for {
		m.Lock()
		for i := 0; i < 2; i++ {
			for j := 0; j < 2; j++ {
				var number= rand.Intn(5)
				garden[number][rand.Intn(5)] = "1"
			}

		}
		m.Unlock()
		time.Sleep(1000 * time.Millisecond)
	}
}

func monitor1(garden [][]string, m *sync.RWMutex) {
	file, err := os.Create("hello.txt")

	if err != nil{
		fmt.Println("Unable to create file:", err)
		os.Exit(1)
	}
	defer file.Close()

	for {
		m.RLock()
		for i := 0; i < 5; i++ {
			line := strings.Join(garden[i][:],"")
			file.WriteString(line+"\n")
		}
		m.RUnlock()
		file.WriteString("\n\n\n")
		time.Sleep(1000 * time.Millisecond)
	}
}

func monitor2(garden [][]string, m *sync.RWMutex) {
	for {
		m.RLock()
		for _, element := range garden {
			for _, element1 := range element {
				print(element1)
			}
			println()
		}
		m.RUnlock()
		println()
		time.Sleep(2000 * time.Millisecond)
	}
}
func main() {
	var garden [][]string
	var wg sync.WaitGroup
	var m sync.RWMutex

	for j := 0; j < 5; j++ {
		var row []string
		for i := 0; i < 5; i++ {
			row = append(row, "0")
		}
		garden = append(garden, row)
	}
	wg.Add(4)
	go monitor1(garden, &m)
	go monitor2(garden, &m)
	go nature(garden, &m)
	go gardener(garden, &m)
	wg.Wait()
}
