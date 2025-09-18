package main

import (
	"bufio"
	"fmt"
	"os"
)

var (
	n, m int
	graph [][]int
	emptySpaces [][2] int
	ans int
	dx = []int{ 0, 0, 1, -1 }
	dy = []int{ 1, -1, 0, 0 }
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	fmt.Fscan(reader, &n, &m)

	graph = make([][]int, n)

	for i := 0; i < n; i++ {
		graph[i] = make([]int, m)
		
		for j := 0; j < m; j++ {
			fmt.Fscan(reader, &graph[i][j])
			if graph[i][j] == 0 {
				emptySpaces = append(emptySpaces, [2]int{ i, j })
			}
		}
	}

	buildWall(0, 0)

	fmt.Fprintln(writer, ans)
}

func buildWall(count, start int) {
	if count == 3 {
		calculateAns()
		return
	}

	for i := start; i < len(emptySpaces); i++ {
		x, y := emptySpaces[i][0], emptySpaces[i][1]

		graph[x][y] = 1
		buildWall(count + 1, i + 1)
		graph[x][y] = 0
	}
}

func calculateAns() {
	tempGraph := make([][]int, n)
	virusQueue := [][2]int{}

	for i := 0; i < n; i++ {
		tempGraph[i] = make([]int, m)

		for j := 0; j < m; j++ {
			tempGraph[i][j] = graph[i][j]

			if (tempGraph[i][j] == 2) {
				virusQueue = append(virusQueue, [2]int{ i, j })
			}
		}
	}

	head := 0
	for head < len(virusQueue) {
		cur := virusQueue[head]
		head++

		x, y := cur[0], cur[1]

		for i := 0; i < 4; i++ {
			nx, ny := x + dx[i], y + dy[i]

			if isSafe(nx, ny) && tempGraph[nx][ny] == 0 {
				tempGraph[nx][ny] = 2
				virusQueue = append(virusQueue, [2]int{ nx, ny })
			}
		}
	}

	curAns := 0
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if tempGraph[i][j] == 0 {
				curAns++;
			}
		}
	}

	if curAns > ans {
		ans = curAns
	}
}

func isSafe(y, x int) bool {
	return y >= 0 && y < n && x >= 0 && x < m
}