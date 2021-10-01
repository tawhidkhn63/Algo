"""python3 code to implement the longest common subsequence problem using dynamic programming
#use python3 LCS to compile """

class LCS:
    # Procedure LCS-LENGTH takes two sequences
    # X = [ x1; x2; : : : ; xm] and
    # Y = [ y1;y2;: : : ;yn] as inputs
    # The procedure return two tables(arrays) b and c
    # b[i][j] points to the table entry corresponding to the optimal sub_problem solution chosen when computing c[i][j]
    # c[m][n] contains the length of an LCS of X and Y
    def LCS_LENGTH(self,X,Y):
        # find the length of the two sequences
        m = len(X)
        n = len(Y)

        # declaring b and c arrays(table)
        b = [[None] * (n + 1) for i in range(m + 1)]
        c = [[None] * (n + 1) for i in range(m + 1)]

        # Now fill the arrays
        for i in range(m + 1):
            for j in range(n + 1):
                # in case i=0 or j=0 , c[i,j]=0
                if i == 0 or j == 0:
                    c[i][j] = 0
                # in case i,j>0  and x_i =y_i ,c[i,j] = c[i-1,j-1] + 1
                elif X[i - 1] == Y[j - 1]:
                    c[i][j] = c[i - 1][j - 1] + 1

                # in case i,j>0  and x_i !=y_i ,c[i,j] = max(c[i,j-1], c[i-1,j])
                elif c[i - 1][j] >= c[i][j - 1]:
                    c[i][j] = c[i - 1][j]

                else:
                    c[i][j] = c[i][j - 1]

        print("The length of the LCS is ", c[m][n])
        return c

    """To reconstruct the elements of an LCS, follow the b[i][j]  arrow
       we dont need c array so we can eliminate it from LCS_LENGTH procedure """
    def print_LCS(self, c, x, y, x_len, y_len):
        # if one of the sequence is empty just return
        if not x_len or not y_len:
            return
        # if we find "-" that means we should decrease the column and the row by 1
        if c[x_len][y_len] == c[x_len - 1][y_len - 1] + 1 or x[x_len] == y[y_len]:
            self.print_LCS(c, x, y, x_len-1, y_len-1)
            print(x[x_len - 1])

        # if we find "|" that means we should decrease just the row by 1
        elif c[x_len][y_len] == c[x_len - 1][y_len] :
            self.print_LCS(c, x,y, x_len - 1, y_len)
        # if we find "<-" that means we should decrease just the column by 1
        else:
            self.print_LCS(c, x,y, x_len, y_len - 1)


def main():
    # test
    lcs = LCS()
    x = "ABCBDAB"
    y = "BDCABA"

    c = lcs.LCS_LENGTH(x, y)
    print("LCS is ")
    lcs.print_LCS(c, x,y, len(x), len(y))


if __name__ == '__main__':
    main()
