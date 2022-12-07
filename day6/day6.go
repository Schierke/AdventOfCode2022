package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	readFile, _ := os.Open("input.txt")

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		text := fileScanner.Text()
		fmt.Println(solver1(text, 4))
		fmt.Println(solver1(text, 14))
	}
}

func solver1(text string, marker int) int {
	mLen := marker
	ok := false

	for !ok && marker < len(text) {
		check := make(map[byte]bool)
		for i := marker - mLen; i < marker; i++ {
			if _, contain := check[text[i]]; !contain {
				check[text[i]] = true
			}
		}
		if len(check) == mLen {
			ok = true
		} else {
			marker++
		}
	}

	return marker
}
