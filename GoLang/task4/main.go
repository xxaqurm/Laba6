package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func calculateTiles(n, m, k int64) int64 {
	return n*m - (n-2*k)*(m-2*k)
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	var n, m, t int64
	var err error

	for {
		fmt.Print("Введите свои n, m, t: ")
		input, _ := reader.ReadString('\n')
		inputs := strings.Fields(input)

		if len(inputs) != 3 {
			fmt.Println("Ошибка: Введите ровно три числа.")
			continue
		}

		n, err = strconv.ParseInt(inputs[0], 10, 64)
		if err != nil {
			fmt.Println("Ошибка: Введите целые числа.")
			continue
		}

		m, err = strconv.ParseInt(inputs[1], 10, 64)
		if err != nil {
			fmt.Println("Ошибка: Введите целые числа.")
			continue
		}

		t, err = strconv.ParseInt(inputs[2], 10, 64)
		if err != nil {
			fmt.Println("Ошибка: Введите целые числа.")
			continue
		}

		break
	}

	var maxWidth int64 = 0
	left := int64(1)
	right := int64(math.Min(float64(n), float64(m))) / 2

	for left <= right {
		mid := left + (right-left)/2
		tilesNeeded := calculateTiles(n, m, mid)

		if tilesNeeded <= t {
			maxWidth = mid
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	fmt.Println(maxWidth)
}