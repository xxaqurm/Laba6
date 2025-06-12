package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Tasks int

const (
	ExitProgram Tasks = iota
	RowNegativeCounter
	MatrixDiagonalSum
	BattleshipCounter
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("Выберите программу:")
	fmt.Println("0. Выход из программы")
	fmt.Println("1. Программа №1")
	fmt.Println("2. Программа №2")
	fmt.Println("3. Программа №3")

	var choice int
	for {
		fmt.Print("Введите номер программы (0-3): ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)

		num, err := strconv.Atoi(input)
		if err != nil || num < 0 || num > 3 {
			fmt.Println(">>> Ошибка: Введите целое число от 0 до 3.")
			continue
		}
		choice = num
		break
	}

	switch Tasks(choice) {
	case ExitProgram:
		return
	case RowNegativeCounter:
		rowNegativeCounter(reader)
	case MatrixDiagonalSum:
		matrixDiagonalSum(reader)
	case BattleshipCounter:
		battleshipCounter()
	}
}
