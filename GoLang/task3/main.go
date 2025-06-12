package main

import (
	"fmt"
	"math"
)

const EPS = 0.001

func isConvergent(A [][]float64) bool {
	n := len(A)
	for i := 0; i < n; i++ {
		sum := 0.0
		for j := 0; j < n; j++ {
			if i != j {
				sum += math.Abs(A[i][j])
			}
		}
		if math.Abs(A[i][i]) <= sum {
			return false
		}
	}
	return true
}

func methodSimpleIters(A [][]float64, b []float64) []float64 {
	n := len(A)
	B := make([][]float64, n)
	for i := range B {
		B[i] = make([]float64, n)
	}
	c := make([]float64, n)

	for i := 0; i < n; i++ {
		if math.Abs(A[i][i]) < EPS {
			fmt.Println("Нулевой диагональный элемент, метод невозможен.")
			return nil
		}
		for j := 0; j < n; j++ {
			if i != j {
				B[i][j] = -A[i][j] / A[i][i]
			} else {
				B[i][j] = 0.0
			}
		}
		c[i] = b[i] / A[i][i]
	}

	if !isConvergent(A) {
		fmt.Println("Не выполнено условие сходимости (не диагональное преобладание)")
		return nil
	}

	x := make([]float64, n)
	xNew := make([]float64, n)
	var err float64
	iters := 0

	for {
		err = 0
		for i := 0; i < n; i++ {
			xNew[i] = c[i]
			for j := 0; j < n; j++ {
				xNew[i] += B[i][j] * x[j]
			}
			if math.Abs(xNew[i]-x[i]) > err {
				err = math.Abs(xNew[i] - x[i])
			}
		}

		copy(x, xNew)
		iters++

		fmt.Printf("Итерация %d: ", iters)
		for _, val := range x {
			fmt.Printf("%.4f ", val)
		}
		fmt.Println()

		if err <= EPS || iters >= 1000 {
			break
		}
	}

	return x
}

func methodGauss(A [][]float64, b []float64) []float64 {
	n := len(A)
	for i := 0; i < n; i++ {
		maxRow := i
		for k := i + 1; k < n; k++ {
			if math.Abs(A[k][i]) > math.Abs(A[maxRow][i]) {
				maxRow = k
			}
		}

		A[i], A[maxRow] = A[maxRow], A[i]
		b[i], b[maxRow] = b[maxRow], b[i]

		if math.Abs(A[i][i]) < EPS {
			fmt.Println("Нет уникального решения (нулевой элемент на диагонали).")
			return nil
		}

		for j := i + 1; j < n; j++ {
			factor := A[j][i] / A[i][i]
			for k := i; k < n; k++ {
				A[j][k] -= factor * A[i][k]
			}
			b[j] -= factor * b[i]
		}
	}

	x := make([]float64, n)
	for i := n - 1; i >= 0; i-- {
		x[i] = b[i]
		for j := i + 1; j < n; j++ {
			x[i] -= A[i][j] * x[j]
		}
		x[i] /= A[i][i]
	}

	return x
}

func main() {
	A := [][]float64{
		{0.79, -0.04, 0.21, -18},
		{0.25, -1.23, 0.18, -0.09},
		{-0.21, 0.18, 0.8, -0.13},
		{0.15, -1.31, 0.06, -0.86},
	}
	b := []float64{-1.24, -0.86, 2.56, 0.79}

	result := methodGauss(A, b)

	fmt.Println("Решение по Гауссу:")
	for i := 0; i < len(result); i++ {
		fmt.Printf("x%d = %.4f\n", i+1, result[i])
	}
	fmt.Println()

	result = methodSimpleIters(A, b)

	if result == nil {
		fmt.Println("По методу простых итераций решений не найдено")
		return
	}
	fmt.Println("\nРешение методом простых итераций:")
	for i := 0; i < len(result); i++ {
		fmt.Printf("x%d = %.4f\n", i+1, result[i])
	}
}
