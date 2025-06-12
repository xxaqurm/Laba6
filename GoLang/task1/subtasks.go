package main

import (
    "bufio"
    "fmt"
    "math/rand"
    "strconv"
    "strings"
    "time"
)


func rowNegativeCounter(reader *bufio.Reader) {
	var m, n int
	for {
		fmt.Print("Введите свои m и n (m > 7, n > 5): ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		parts := strings.Fields(input)
		if len(parts) != 2 {
			fmt.Println(">>> Ошибка: Введите два целых числа.")
			continue
		}
		m1, err1 := strconv.Atoi(parts[0])
		n1, err2 := strconv.Atoi(parts[1])
		if err1 != nil || err2 != nil || m1 < 8 || n1 < 6 {
			fmt.Println(">>> Ошибка: m должно быть > 7, n > 5.")
			continue
		}
		m, n = m1, n1
		break
	}

	rand.Seed(time.Now().UnixNano())
	matrix := make([][]int, m)
	for i := 0; i < m; i++ {
		matrix[i] = make([]int, n)
		for j := 0; j < n; j++ {
			matrix[i][j] = rand.Intn(19) - 9
		}
	}

	fmt.Println("Матрица:")
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%2d ", val)
		}
		fmt.Println()
	}

	bestRow := 0
	maxNeg := 0
	for i := 0; i < m; i++ {
		neg := 0
		for j := 0; j < n; j++ {
			if matrix[i][j] < 0 {
				neg++
			}
		}
		if neg > maxNeg {
			maxNeg = neg
			bestRow = i
		}
	}

	fmt.Printf("Номер найденной строки: %d\n", bestRow+1)
	fmt.Print("Найденная строка: ")
	for _, val := range matrix[bestRow] {
		fmt.Printf("%d ", val)
	}
	fmt.Println()
}

func changeNum(num int) int {
	digits := []int{}
	for num > 0 {
		digits = append(digits, num%10)
		num /= 10
	}

	// Сортировка по убыванию
	for i := 0; i < len(digits)-1; i++ {
		for j := i + 1; j < len(digits); j++ {
			if digits[j] > digits[i] {
				digits[i], digits[j] = digits[j], digits[i]
			}
		}
	}

	res := 0
	for _, d := range digits {
		res = res*10 + d
	}
	return res
}

func matrixDiagonalSum(reader *bufio.Reader) {
	var m int
	for {
		fmt.Print("Введите своё m (m > 5): ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		num, err := strconv.Atoi(input)
		if err != nil || num < 6 {
			fmt.Println(">>> Ошибка: Введите целое число больше 5.")
			continue
		}
		m = num
		break
	}

	rand.Seed(time.Now().UnixNano())
	matrix := make([][]int, m)
	for i := 0; i < m; i++ {
		matrix[i] = make([]int, m)
		for j := 0; j < m; j++ {
			matrix[i][j] = rand.Intn(91) + 10
		}
	}

	fmt.Println("Матрица:")
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%3d ", val)
		}
		fmt.Println()
	}

	mainDiag := []int{}
	secDiag := []int{}
	for i := 0; i < m; i++ {
		mainDiag = append(mainDiag, matrix[i][i])
		secDiag = append(secDiag, matrix[i][m-i-1])
	}

	fmt.Print("\nMain diagonal: ")
	for _, v := range mainDiag {
		fmt.Printf("%d ", v)
	}
	fmt.Println()

	fmt.Print("Secondary diagonal: ")
	for _, v := range secDiag {
		fmt.Printf("%d ", v)
	}
	fmt.Println()

	sumMain, sumSec := 0, 0
	for i := 0; i < m; i++ {
		sumMain += changeNum(mainDiag[i])
		sumSec += changeNum(secDiag[i])
	}

	fmt.Printf("Sum main diagonal: %d\n", sumMain)
	fmt.Printf("Sum secondary diagonal: %d\n", sumSec)

	if sumMain > sumSec {
		fmt.Println("Сумма основной диагонали больше!")
	} else if sumMain < sumSec {
		fmt.Println("Сумма побочной диагонали больше!")
	} else {
		fmt.Println("Суммы совпадают!")
	}
}

func battleshipCounter() {
	m, n := 4, 4
	field := [][]rune{
		{'.', '.', 'X', 'X'},
		{'X', 'X', '.', '.'},
		{'.', '.', '.', 'X'},
		{'.', 'X', '.', 'X'},
	}

	fmt.Println("Игровое поле:")
	for _, row := range field {
		for _, cell := range row {
			fmt.Printf("%c ", cell)
		}
		fmt.Println()
	}

	cntShips := 0

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if field[i][j] == 'X' {
				isStart := true

				if i > 0 && field[i-1][j] == 'X' {
					isStart = false
				}
				if j > 0 && field[i][j-1] == 'X' {
					isStart = false
				}

				if (i > 0 && field[i-1][j] == 'X') && (j > 0 && field[i][j-1] == 'X') {
					fmt.Println("ERROR")
					return
				}

				if isStart {
					cntShips++
				}
			}
		}
	}

	fmt.Printf("Количество кораблей: %d\n", cntShips)
}
