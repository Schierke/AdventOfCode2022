package main

import (
	"bufio"
	"fmt"
	"os"
)

var score map[byte]int

func main() {
	readFile, _ := os.Open("input1.txt")

	score = map[byte]int{
		'A': 1,
		'B': 2,
		'C': 3,
		'X': 1,
		'Y': 2,
		'Z': 3,
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	ret := 0
	ret2 := 0
	for fileScanner.Scan() {
		text := fileScanner.Text()
		ret += checkScore1(text[0], text[2])
		ret2 += checkScore2(text[0], text[2])
	}

	fmt.Println(ret)
	fmt.Println(ret2)
}

func checkScore1(a, b byte) int {
	s1, s2 := score[a], score[b]
	if s1 == s2 {
		return s2 + 3
	}

	if rule1(s1, s2) == true {
		return s2 + 6
	}

	return s2
}

func checkScore2(a, b byte) int {
	s1 := score[a]
	if b == 'X' {
		if (s1+2)%3 == 0 {
			return 3
		}
		return (s1 + 2) % 3
	} else if b == 'Y' {
		return 3 + s1
	} else {
		if (s1+1)%3 == 0 {
			return 9
		}
		return 6 + (s1+1)%3
	}
}

func rule1(a, b int) bool {
	if (a == 1 && b == 2) || (a == 2 && b == 3) || (a == 3 && b == 1) {
		return true
	}

	return false
}
