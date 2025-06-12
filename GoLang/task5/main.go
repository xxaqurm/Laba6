package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

const (
	ONE  byte = '1'
	ZERO byte = '0'
)

func generateBoard(n, m int) [][]byte {
	rand.Seed(time.Now().UnixNano())
	board := make([][]byte, n)
	for i := range board {
		board[i] = make([]byte, m)
		for j := range board[i] {
			if rand.Intn(2) == 1 {
				board[i][j] = ONE
			} else {
				board[i][j] = ZERO
			}
		}
	}
	return board
}

func createChessPattern(n, m int, startWithEagle bool) [][]byte {
	pattern := make([][]byte, n)
	var first, second byte = ZERO, ONE
	if startWithEagle {
		first, second = ONE, ZERO
	}

	for i := range pattern {
		pattern[i] = make([]byte, m)
		for j := range pattern[i] {
			if (i+j)%2 == 0 {
				pattern[i][j] = first
			} else {
				pattern[i][j] = second
			}
		}
	}
	return pattern
}

func countDifferences(board, pattern [][]byte) int {
	diff := 0
	for i := range board {
		for j := range board[i] {
			if board[i][j] != pattern[i][j] {
				diff++
			}
		}
	}
	return diff
}

func printBoard(board [][]byte) {
	for _, row := range board {
		for _, c := range row {
			fmt.Printf("%c ", c)
		}
		fmt.Println()
	}
}

func main() {
	var n, m int
	
	for {
		fmt.Print("Введите размеры доски (n, m): ")
		_, err := fmt.Scan(&n, &m)
		if err != nil || n < 1 || m < 1 {
			fmt.Println("Ошибка: неверные размеры доски")
			continue
		}
		break
	}

	board := generateBoard(n, m)

	fmt.Println("Исходная доска:")
	printBoard(board)

	pattern1 := createChessPattern(n, m, true)
	pattern2 := createChessPattern(n, m, false)

	diff1 := countDifferences(board, pattern1)
	diff2 := countDifferences(board, pattern2)

	res := -1
	if diff1%2 == 0 || diff2%2 == 0 {
		min1 := math.MaxInt32
		if diff1%2 == 0 {
			min1 = diff1 / 2
		}
		min2 := math.MaxInt32
		if diff2%2 == 0 {
			min2 = diff2 / 2
		}
		if min1 < min2 {
			res = min1
		} else {
			res = min2
		}
	}

	if res == -1 {
		fmt.Println("Невозможно достичь шахматного узора.")
	} else {
		fmt.Printf("Минимальное количество ходов: %d\n", res)
	}
}