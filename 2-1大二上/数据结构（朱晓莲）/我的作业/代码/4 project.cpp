//4.3
void Transfer(int *A, int *B) {
	int n = 100;   //此处设n=100
	int C[100][100+1];
	for (int i = 0; i < n; i++) {   //从第一行到第n行赋值
		for (int j = 0; j <= i; j++) {  //将A数组的第i行元素赋到C数组的第i行
			C[i][j] = A[i][j];
		}
		for (int k = i + 1; k < n; k++) {  //将B数组的第i行元素赋到C数组的第i行
			C[i][k] = B[k - 1][i];
		}
	}
}


//4.12
int SaddlePoint(int A[][], int m, int n) {   //传入数组A[m][n]
	for (int i = 0; i < m; i++) {   //按行循环一次，逐行查找鞍点
		int temp = A[i][0];   //保存临时“鞍点”值
		int min = 0;    //记录当前行最小元素列号
		for (int j = 1; j < n; j++) {    //查找i行的最小元素并记录该元素列号
			if (A[i][j] < temp) {
				temp = A[i][j];
				min = j;
			}
		}
		for (int k = 0; k < m; k++) {    //判断i行最小元素是否min列最大元素
			if (k == i) continue;     //不与自身作比较
			if (A[k][min] > temp) break;   //只要min列有一个元素比A[i][min]大，就跳出循环继续查找第i+1行
			if (k == m - 1)     //如果程序能执行到这一步说明min列没有比A[i][min]大的元素，则A[i][min]即为鞍点
				cout << "Find:A[" << i << "][" << min << "]=" << A[i][min] << endl;    //输出该鞍点
		}
	}
}
